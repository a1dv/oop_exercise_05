#pragma once
template <class T>
struct pentagon
{
    point <T> a1,a2,a3,a4,a5;
    pentagon (point <T> x1, point <T> x2, point <T> x3, point <T> x4, point <T> x5) {
        a1 = x1; a2 = x2; a3 = x3; a4 = x4; a5 = x5;
    }
    pentagon() = default;
    point <T> center() const {
        T x,y;
        x = (a1.x + a2.x + a3.x + a4.x + a5.x) / 5;
        y = (a1.y + a2.y + a3.y + a4.y + a5.y) / 5;
        point <T> p(x,y);
        return p;
    }

    void print(std::ostream& out) {
        out << "Coordinates are:\n"<<"{\n"<< a1 << a2 << a3 << a4 << a5 << "}\n";
    }
    T area() const {
        return (0.5) * std::abs((a1.x*a2.y + a2.x*a3.y + a3.x*a4.y + a4.x*a5.y + a5.x*a1.y) - ( a1.y*a2.x + a2.y*a3.x + a3.y*a4.x + a4.y*a5.x + a5.y*a1.x ));
    }
    pentagon(std::istream& is) {
        is >> a1 >> a2 >> a3 >> a4 >> a5;
    }
};
