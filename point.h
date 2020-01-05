#pragma once
#include <iostream>

template <class T>
struct point {
    T x, y;
    point (T a,T b) { x = a, y = b;};
    point() = default;
};

template <class T>
std::istream& operator >> (std::istream& npt,point <T>& p ) {
    return  npt >> p.x >> p.y;
}

template <class T>
std::ostream& operator << (std::ostream& out,const point <T>& p) {
    return out << p.x << ' ' << p.y << '\n';
}
