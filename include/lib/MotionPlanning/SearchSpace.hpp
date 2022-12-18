#pragma once
#include "lib/Geometry/Polygon.hpp"
#include <memory>
#include <vector>
#include <random>

class SearchSpace{
    public:
    SearchSpace(okapi::QLength iX, okapi::QLength iY, 
                std::vector<std::shared_ptr<Polygon>> iObstacleList, 
                okapi::QLength iRadius = 0 * okapi::meter);

    Point randomPoint() const;

    Point randomLegalPoint() const;

    bool checkLineCollision(const Line& iLine) const;

    bool checkPointCollision(const Point& iPoint) const;

    private:
    okapi::QLength x;
    okapi::QLength y;
    okapi::QLength radius;
    std::vector<std::shared_ptr<Polygon>> obstacleList;
    std::vector<Line> edgeList;
};