#include <algorithm>
#include <iostream>
#include "point.h"
#include "pentagon.h"
#include "list.h"

int main()
{
    std::string i;
    size_t j;
    containers::list<pentagon<double>> l;
    while (true) {
        std::cout << "1- insert by index\n2 - delete by index\n3 - count if(Количество фигур с площадью больше вводимого значения)\n4 - print by index\n5 - print all\n6 - quit\n";
        std::cin >> i;
        if (i == "1") {
            std::cout << "Enter coordinates:\n";
            pentagon <double> p(std::cin);
            std::cout << "Enter index:\n";
            std::cin >> j;
            try {
                l.insert_by_number(j, p);
            } catch (std::logic_error &err) {
                l.delete_by_number(j);
                std::cout << err.what() << "\n";
                break;
            }

        }
        if (i == "2") {
            std::cout << "Enter index:\n";
            std::cin >> j;
            if (j == (l.length()-1)){
                l.pop_back();
            }else {
                try {
                    l.delete_by_number(j);
                } catch (std::logic_error &err) {
                    std::cout << err.what() << std::endl;
                    break;
                }
            }
        }
        if (i == "3") {
            std::cout << "Enter the value:\n";
            double val;
            std::cin >> val;
            std::cout << std::count_if(l.begin(), l.end(), [val](pentagon<double> el) {return el.area() > val; }) << " pentagons\n";
        }

        if (i == "4") {
            std::cout << "Enter index:\n";
            std::cin >> j;
            l[j].print(std::cout);
        }
        if (i == "5") {
            for (auto elem : l) {
                elem.print(std::cout);
            }
        }
        if (i == "6") {
            break;
        }
    }
}
