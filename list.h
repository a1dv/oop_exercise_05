#pragma once
#include <iterator>
#include <memory>
#include "pentagon.h"

namespace containers {


    template<class T>
    class list {
    private:
        struct element;
        unsigned int size = 0;
    public:
        list() = default;

        class forward_iterator {
        public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            explicit forward_iterator(element* ptr);
            T& operator*();
            forward_iterator& operator++();
            forward_iterator operator++(int);
            bool operator== (const forward_iterator& other) const;
            bool operator!= (const forward_iterator& other) const;

        private:
            element* it_ptr;
            friend list;

        };
        forward_iterator begin();
        forward_iterator end();
        void pop_back();
        void pop_front();
        size_t length();
        void delete_by_it(forward_iterator d_it);
        void delete_by_number(size_t N);
        void insert_by_it(forward_iterator ins_it, T& value);
        void insert_by_number(size_t N, T& value);
        T& operator[](size_t index) ;
        list& operator=(list&& other);

    private:
        struct element {
            T value;
            std::shared_ptr<element> next_element = nullptr;
            std::shared_ptr<element> prev_element = nullptr;
            forward_iterator next();
        };
        static std::shared_ptr<element> push_impl(std::shared_ptr<element> cur);
        static std::shared_ptr<element> pop_impl(std::shared_ptr<element> cur);
        std::shared_ptr<element> first = nullptr;
    };

    template<class T>
    typename list<T>::forward_iterator list<T>::begin() {
        return forward_iterator(first.get());
    }

    template<class T>
    typename list<T>::forward_iterator list<T>::end() {
        return forward_iterator(nullptr);
    }
    template<class T>
    size_t list<T>::length() {
        return size;
    }
    template<class T>
    std::shared_ptr<typename list<T>::element> list<T>::push_impl(std::shared_ptr<element> cur) {
        if (cur -> next_element != nullptr) {
            return push_impl(cur->next_element);
        }
        return cur;
    }
    template<class T>
    void list<T>::pop_front() {
        if (size == 0) {
            throw std::logic_error ("stack is empty");
        }

        first = first->next_element;
        first->prev_element = nullptr;
        size--;
    }
    template<class T>
    void list<T>::pop_back() {
        if (size == 0) {
            throw std::logic_error("can`t pop from empty list");
        }
        first = pop_impl(first);
        size--;
    }
    template<class T>
    std::shared_ptr<typename list<T>::element> list<T>::pop_impl(std::shared_ptr<element> cur) {
        if (cur->next_element != nullptr) {
            cur->next_element = pop_impl(cur->next_element);
            return cur;
        }
        return nullptr;
    }
    template<class T>
    void list<T>::delete_by_it(containers::list<T>::forward_iterator d_it) {
        if (d_it.it_ptr == nullptr) {
            throw std::logic_error("попытка доступа к несуществующему элементу");
        }
        if (d_it == this->begin()) {
            this->pop_front();
            size --;
            return;
        }
        if (d_it == this->end()) {
            this->pop_back();
            size --;
            return;
        }
        d_it.it_ptr->prev_element->next_element = d_it.it_ptr->next_element;
        d_it.it_ptr->next_element->prev_element = d_it.it_ptr->prev_element;

        size--;
    }
    template<class T>
    void list<T>::delete_by_number(size_t N) {
        forward_iterator it = this->begin();
        for (size_t i = 1; i <= N; ++i) {
            ++it;
        }
        this->delete_by_it(it);
    }

    template<class T>
    void list<T>::insert_by_it(containers::list<T>::forward_iterator ins_it, T& value) {
        if (first != nullptr) {
            if (ins_it == this->begin()) {
                std::shared_ptr<element> tmp = std::shared_ptr<element>(new element{ value });
                tmp->next_element = first;
                first->prev_element = tmp;
                first = tmp;
                if (tmp->value.area() > tmp->next_element->value.area()) {
                    throw std::logic_error("Area is too big");
                }
                size++;
                return;
            }else {
                if (ins_it.it_ptr == nullptr) {
                    std::shared_ptr<element> tmp = std::shared_ptr<element>(new element{value});

                    tmp->prev_element = push_impl(first);
                    push_impl(first)->next_element = std::shared_ptr<element>(tmp);
                    if (tmp->value.area() < tmp->prev_element->value.area()) {
                        throw std::logic_error("Area is too low");
                    }
                    size++;
                    return;
                } else {
                    std::shared_ptr<element> tmp = std::shared_ptr<element>(new element{value});
                    tmp->prev_element = ins_it.it_ptr->prev_element;
                    tmp->next_element = ins_it.it_ptr->prev_element->next_element;
                    ins_it.it_ptr->prev_element = tmp;
                    tmp->prev_element->next_element = tmp;

                    if (tmp->value.area() > tmp->next_element->value.area()) {
                        throw std::logic_error("Area is too big");
                    }
                    if (tmp->value.area() < tmp->prev_element->value.area()) {
                        throw std::logic_error("Area is too low");
                    }
                }
            }
        } else first=std::shared_ptr<element>(new element{value});

        size++;
    }

    template<class T>
    void list<T>::insert_by_number(size_t N, T& value) {
        forward_iterator it = this->begin();
        for (size_t i = 0; i < N; ++i) {
            ++it;
        }
        this->insert_by_it(it, value);
    }
    template<class T>
    typename list<T>::forward_iterator list<T>::element::next() {
        return forward_iterator(this->next_element.get());
    }

    template<class T>
    list<T>::forward_iterator::forward_iterator(containers::list<T>::element *ptr) {
        it_ptr = ptr;
    }

    template<class T>
    T& list<T>::forward_iterator::operator*() {
        return this->it_ptr->value;
    }

    template<class T>
    typename list<T>::forward_iterator& list<T>::forward_iterator::operator++() {
        if (it_ptr == nullptr) throw std::logic_error ("out of list borders");
        *this = it_ptr->next();
        return *this;
    }

    template<class T>
    typename list<T>::forward_iterator list<T>::forward_iterator::operator++(int) {
        forward_iterator old = *this;
        ++*this;
        return old;
    }

    template<class T>
    bool list<T>::forward_iterator::operator==(const forward_iterator& other) const {
        return it_ptr == other.it_ptr;
    }
    template<class T>
    list<T>& list<T>::operator=(list<T>&& other){
        size = other.size;
        first = std::move(other.first);
    }

    template<class T>
    bool list<T>::forward_iterator::operator!=(const forward_iterator& other) const {
        return it_ptr != other.it_ptr;
    }

    template<class T>
    T& list<T>::operator[](size_t index)  {
        if (index < 0 || index >= size) {
            throw std::out_of_range("out of list's borders");
        }
        forward_iterator it = this->begin();
        for (size_t i = 0; i < index; i++) {
            it++;
        }
        return *it;
    }
}
