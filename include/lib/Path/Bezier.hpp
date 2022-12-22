#include "DiscretePath.hpp"
#include<iostream>

namespace lib{

class CubicBezier{
    public:
    struct Knot{
        Knot(okapi::QLength iX, okapi::QLength iY, okapi::QAngle iAngle, okapi::QLength iMagnitude);

        okapi::QLength x;
        okapi::QLength y;
        okapi::QAngle angle;
        okapi::QLength magnitude;
    };

    CubicBezier(const std::vector<Knot>& iWaypoint);

    Point getPoint(double iT) const;

    DiscretePath generate(int iStep, bool iEnd = true) const;

    DiscretePath generate(okapi::QLength iStep, bool iEnd = true) const;

    private:
    std::vector<Point> p1;
    std::vector<Point> p2;
    std::vector<Point> c1;
    std::vector<Point> c2;
};

}