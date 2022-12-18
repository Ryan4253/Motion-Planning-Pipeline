#pragma once
#include "lib/Geometry/Point.hpp"
#include<vector>
#include<cmath>

class DiscretePath{
    public:
    DiscretePath(const std::initializer_list<Point>& iPath);

    DiscretePath(const std::vector<Point>& iPath);

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();

    Point& operator[](int iIndex);

    Point getPoint(int iIndex) const;

    okapi::QLength getLength() const;

    int size() const;

    private:
    std::vector<Point> path;
    okapi::QLength length;
};