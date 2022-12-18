#include "Circle.hpp"

Circle::Circle(const Point& iCenter, okapi::QLength iRadius){
    center = iCenter;
    radius = iRadius;
}

bool Circle::lineIntersect(const Line& iLine, okapi::QLength iDist) const{
    auto pt = iLine.closestPointTo(center);
    return center.distTo(pt) <= (iDist + radius);
}

bool Circle::pointIntersect(const Point& iPoint, okapi::QLength iDist) const{
    return iPoint.distTo(center) <= (iDist + radius);
}