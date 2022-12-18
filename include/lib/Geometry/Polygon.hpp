#pragma once
#include "Point.hpp"
#include "Line.hpp"

namespace lib{

class Polygon{
    public:
    virtual bool lineIntersect(const Line& iLine, okapi::QLength iDist) const = 0;

    virtual bool pointIntersect(const Point& iPoint, okapi::QLength iDist) const = 0;
};

}