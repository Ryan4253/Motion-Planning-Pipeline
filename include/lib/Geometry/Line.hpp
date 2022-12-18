#pragma once
#include "Point.hpp"

class Line{
    public:
    Line(const Point& iStart, const Point& iEnd);

    Point interpolate(double t) const;

    okapi::QLength length() const;

    Point Start() const;

    Point End() const;

    Point project(const Point& iPoint) const;

    Point closestPointTo(const Point& iPoint) const;

    bool isBetween(const Point& iPoint) const;

    bool intersects(const Line& iLine) const;

    private:
    Point start;
    Point end;
};