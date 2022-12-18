#pragma once
#include "Polygon.hpp"

class Rectangle : public Polygon{
    public:
    Rectangle(const Point& iBottomLeft, const Point& iTopRight);

    bool lineIntersect(const Line& iLine, okapi::QLength iDist) const override;

    bool pointIntersect(const Point& iPoint, okapi::QLength iDist) const override;

    private:
    Point topLeft;
    Point topRight;
    Point bottomLeft;
    Point bottomRight;
};
