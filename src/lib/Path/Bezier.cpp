#include "Bezier.hpp"

namespace lib{

CubicBezier::Knot::Knot(okapi::QLength iX, okapi::QLength iY, okapi::QAngle iAngle, okapi::QLength iMagnitude){
    x = iX, y = iY, angle = iAngle, magnitude = iMagnitude;
}

CubicBezier::CubicBezier(const std::vector<Knot>& iWaypoint){
    for(int i = 0; i < iWaypoint.size()-1; i++){
        Point point1(iWaypoint[i].x, iWaypoint[i].y);
        Point point2(iWaypoint[i+1].x, iWaypoint[i+1].y);
        p1.push_back(point1);
        p2.push_back(point2);
        c1.push_back(point1 + Point(iWaypoint[i].magnitude, Rotation(iWaypoint[i].angle)));
        c2.push_back(point2 + Point(iWaypoint[i+1].magnitude, Rotation(iWaypoint[i+1].angle - M_PI * okapi::radian)));
    }
}   

Point CubicBezier::getPoint(double iT) const{
    iT = std::max(std::min(iT, 1.0), 0.0);

    int index = int(iT * p1.size());
    double t = iT * p1.size() - index;

    if(iT == 1){
        index = p1.size() - 1;
        t = 1;
    }

    return p1[index] * (1-t) * (1-t) * (1-t) + 
           c1[index] * 3 * (1-t) * (1-t) * t + 
           c2[index] * 3 * (1-t) * t * t + 
           p2[index] * t * t * t;
}

DiscretePath CubicBezier::generate(int iStep, bool iEnd) const{
    std::vector<Point> ret;
    double inc = 1.0 / iStep;

    for(int i = 0; i < iStep; i++){
        double t = i * inc;
        ret.push_back(getPoint(t));
    }

    if(iEnd){
        ret.push_back(getPoint(1));
    }

    return DiscretePath(ret);
}

DiscretePath CubicBezier::generate(okapi::QLength iStep, bool iEnd) const{
    std::vector<Point> ret;
    okapi::QLength totalDist = 0 * okapi::meter;

    for(double t = 0; t < 1; t += 0.01){
        totalDist += getPoint(t).distTo(getPoint(t + 0.01));
    }

    okapi::QLength distPerSegment = totalDist / ceil((totalDist / iStep).convert(okapi::number));
    okapi::QLength traversed = 0 * okapi::meter;
    ret.push_back(getPoint(0));
    for(double t = 0; t < 1; t += 0.001){
        traversed += getPoint(t).distTo(getPoint(t + 0.001));
        if(traversed >= distPerSegment){
            traversed = 0 * okapi::meter;
            ret.push_back(getPoint(t));
        }
    }

    if(ret.back().distTo(getPoint(1)) < distPerSegment / 2){
        ret.pop_back();    
    }

    if(iEnd){
        ret.push_back(getPoint(1));
    }

    return DiscretePath(ret);
}

}