#include "SearchSpace.hpp"

SearchSpace::SearchSpace(okapi::QLength iX, okapi::QLength iY, 
                std::vector<std::shared_ptr<Polygon>> iObstacleList, 
                okapi::QLength iRadius){
    x = iX;
    y = iY;
    obstacleList = iObstacleList;
    radius = iRadius;   

    const auto p1 = Point(radius, radius);
    const auto p2 = Point(radius, y-radius);
    const auto p3 = Point(x-radius, y-radius);
    const auto p4 = Point(x-radius, radius);
    edgeList = {Line(p1, p2), Line(p2, p3), Line(p3, p4), Line(p4, p1)};
}

Point SearchSpace::randomPoint() const{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return Point(x * distribution(generator), y * distribution(generator));
}

Point SearchSpace::randomLegalPoint() const{
    while(true){
        const auto point = randomPoint();
        if(!checkPointCollision(point)){
            return point;
        }
    }
}

bool SearchSpace::checkLineCollision(const Line& iLine) const{
    for(const auto& obstacle : obstacleList){
        if(obstacle->lineIntersect(iLine, radius)){
            return true;
        }
    }

    for(const auto& edge : edgeList){
        if(edge.intersects(iLine)){
            return true;
        }
    }
    
    return false;
}

bool SearchSpace::checkPointCollision(const Point& iPoint) const{
    for(const auto& obstacle : obstacleList){
        if(obstacle->pointIntersect(iPoint, radius)){
            return true;
        }
    }

    const auto ptX = iPoint.X();
    const auto ptY = iPoint.Y();
    if(ptX < radius || ptX > x-radius || ptY < radius || ptY > y-radius){
        return true;
    }

    return false;
}