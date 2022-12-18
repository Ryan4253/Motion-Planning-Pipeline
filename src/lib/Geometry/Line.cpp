#include "Line.hpp"

Line::Line(const Point& iStart, const Point& iEnd){
    start = iStart;
    end = iEnd;
}

Point Line::Start() const{
    return start;
}

Point Line::End() const{
    return end;
}

Point Line::interpolate(double t) const{
    if(t <= 0){
        return start;
    }
        
    if(t >= 1){
        return end;
    }
         
    return start + (end - start)*t;
}

okapi::QLength Line::length() const{
    return start.distTo(end);
}

Point Line::project(const Point& iPoint) const{
    Point v1 = iPoint - start;
    Point v2 = end - start;
    return start + v1.project(v2);
}

Point Line::closestPointTo(const Point& iPoint) const{
    Point closestPt = project(iPoint);

    if(isBetween(closestPt)){
        return closestPt;
    }

    if(start.distTo(iPoint) < end.distTo(iPoint)){
        return start;
    }

    return end;
}

bool Line::isBetween(const Point& iPoint) const{
    Point v = start - iPoint;
    Point w = end - iPoint;

    return abs(v.cross(w)) < 0.00001 * okapi::meter2 and v.dot(w) < 0 * okapi::meter2;
}

bool Line::intersects(const Line& iLine) const{
    auto x1 = start.X();
    auto y1 = start.Y();
    auto x2 = end.X();
    auto y2 = end.Y();
    auto x3 = iLine.Start().X();
    auto y3 = iLine.Start().Y();
    auto x4 = iLine.End().X();
    auto y4 = iLine.End().Y();

    auto denom = (y4-y3)*(x2-x1) - (x4-x3)*(y2-y1);
    if(denom == 0 * okapi::meter2){
        return false;
    }
    
    auto ua = (((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / denom).convert(okapi::number);
    if(ua < 0 || ua > 1){
        return false;
    }

    auto ub = (((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / denom).convert(okapi::number);
    if(ub < 0 || ub > 1){
        return false;
    }
       
    return true;
}