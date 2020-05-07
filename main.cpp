#include <iostream>
#include <vector>

class IsDivide {
public:
    bool operator() (int x) {
        return x % 3 == 0;
    }
};

class Point {
private:
    double x_, y_;

public:
    Point(const double& x, const double& y) {
        x_ = x;
        y_ = y;
    }

    double getX() const {
        return x_;
    }
    double getY() const {
        return y_;
    }

    bool operator== (const Point& p) const {
        return (x_ == p.getX()) && (y_ == p.getY());
    }
};

class ComparatorPoint {
public:
    bool operator()(Point p) {
        return p == Point(0, 0);
    }
};

template <class T>
bool is_equals(T x, T y) {
    return x == y;
}


bool is_equalsPoints(Point p1, Point p2) {
    return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}
// =========================================================
template<class T, class Predicate>
bool any_of(T obj, Predicate p) {
    typename T::const_iterator it = obj.begin();
    while (it != obj.end()) {
        if (p(*it))
            return true;
        ++it;
    }

    return false;
}

template<class T, class Predicate>
bool is_partitioned(T obj, Predicate p) {
    typename T::const_iterator it = obj.begin();
    char changed = 0;
    char parted = -1;
    while (it != obj.end()) {
        bool cur = p(*it++);
        if (cur && parted == -1)
            parted = 1;
        else if (!cur && parted == -1)
            parted = 0;
        else if (!cur && !parted && changed)
            return false;
        else if (cur && parted && changed)
            return false;

        if (!changed) {
            if (cur && !parted)
                changed = 1;
            else if (!cur && parted)
                changed = 1;
        }
    }
    return true;
}


template<class T, class P, class U>
P find_not(T obj, P p, bool (*compare)(U o1, U o2)) {
    typename T::const_iterator it = obj.begin();

    while (it < obj.end() - 1) {
        if (!compare(p, *it)) {
            return *it;
        }
        ++it;
    }


}

int main() {

    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(4);

    std::cout << "Is and op v1 divided by 3 is " << ((any_of(v1, IsDivide())) ? "true" : "false") << "\n";
    std::cout << "One op v1 is 3 is " << (is_partitioned(v1,IsDivide()) ? "true" : "false") << "\n";
    int a = find_not(v1, 1, is_equals<int>);
    std::cout << "first elem that is not equal to 1 is " << a << "\n";

    std::cout << "\n";


    std::vector<Point> pV;
    pV.push_back(Point(0, 0));
    pV.push_back(Point(0, 1));
    pV.push_back(Point(0, 2));

    Point p1(0, 0);

    std::cout << "Is any of pV is Point(0, 0) is " <<  (any_of(pV, ComparatorPoint()) ? "true" : "false") << "\n";
    std::cout << "Only one of v1 is Point(0, 0) is " << (is_partitioned(pV, ComparatorPoint()) ? "true" : "false") << "\n";
    Point p = find_not(pV, p1, is_equalsPoints);
    std::cout << "first point that is not equal to Point(0, 0) is (" << p.getX() << ", " << p.getY() << ")\n";

    return 0;
}