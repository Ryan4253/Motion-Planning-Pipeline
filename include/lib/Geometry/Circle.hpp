#pragma once
#include "Polygon.hpp"

class Circle : public Polygon{
    public:
    Circle(const Point& iCenter, okapi::QLength iRadius);

    bool lineIntersect(const Line& iLine, okapi::QLength iDist) const override;

    bool pointIntersect(const Point& iPoint, okapi::QLength iDist) const override;
 
    private:
    Point center;
    okapi::QLength radius;
};