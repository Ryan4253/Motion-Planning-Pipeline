#include "Rectangle.hpp"

Rectangle::Rectangle(const Point& iBottomLeft, const Point& iTopRight){
    bottomLeft = iBottomLeft;
    topRight = iTopRight;
    bottomRight = Point(topRight.X(), bottomLeft.Y());
    topLeft = Point(bottomLeft.X(), topRight.Y());
}

bool Rectangle::lineIntersect(const Line& iLine, okapi::QLength iDist) const{
    auto p1 = Point(topLeft.X()-iDist, topLeft.Y()+iDist);
    auto p2 = Point(topRight.X()+iDist, topRight.Y()+iDist);
    auto p3 = Point(bottomRight.X()+iDist, bottomRight.Y()-iDist);
    auto p4 = Point(bottomLeft.X()-iDist, bottomLeft.Y()-iDist);

    auto l1 = Line(p1, p2);
    auto l2 = Line(p2, p3);
    auto l3 = Line(p3, p4);
    auto l4 = Line(p4, p1);

    return (iLine.intersects(l1) || iLine.intersects(l2) || iLine.intersects(l3) || iLine.intersects(l4));
}   

bool Rectangle::pointIntersect(const Point& iPoint, okapi::QLength iDist) const{
    auto xStart = topLeft.X() - iDist;
    auto xEnd = bottomRight.X() + iDist;
    auto yStart = bottomRight.Y() - iDist;
    auto yEnd = topLeft.Y() + iDist;

    return xStart <= iPoint.X() && iPoint.X() <= xEnd && yStart <= iPoint.Y() && iPoint.Y() <= yEnd;
}