#pragma once
#include "lib/Geometry/Point.hpp"
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>

namespace lib{

class DiscretePath{
    public:
    DiscretePath(const std::initializer_list<Point>& iPath);

    DiscretePath(const std::vector<Point>& iPath);

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();

    std::vector<Point>::const_iterator cbegin() const;

    std::vector<Point>::const_iterator cend() const;

    const Point& front() const;

    const Point& back() const;

    Point& operator[](int iIndex);

    Point getPoint(int iIndex) const;

    okapi::QLength getLength() const;

    int size() const;

    std::string str() const;

    private:
    std::vector<Point> path;
    okapi::QLength length;
};

}