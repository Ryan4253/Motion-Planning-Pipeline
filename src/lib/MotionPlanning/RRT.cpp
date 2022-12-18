#include "RRT.hpp"
     
namespace lib{

RRT::RRT(const SearchSpace& iField, double iGoalSampleRate, okapi::QLength iStepSize, int iMaxIteration) 
    : MotionPlanner(iField){
    goalSampleRate = iGoalSampleRate;
    stepSize = iStepSize;
    maxIteration = iMaxIteration;
}

DiscretePath RRT::generatePath(const Point& iStart, const Point& iEnd){
    if(field.checkPointCollision(iStart) || field.checkPointCollision(iEnd)){
        return DiscretePath({});
    }

    start = std::make_shared<Node>(iStart);
    goal = std::make_shared<Node>(iEnd);
    vertices.clear();
    vertices.push_back(start);

    for(int i = 1; i <= maxIteration; i++){
        Point sample = getRandomPoint();
        auto nearNode = nearestNode(sample);
        auto newNode = makeNewNode(nearNode, sample);

        if(!newNode || field.checkLineCollision(Line(nearNode->point, newNode->point))){
            continue;
        }

        vertices.push_back(newNode);

        if(goal->parent.expired() && 
           newNode->distTo(goal->point) <= stepSize && 
           !field.checkLineCollision(Line(newNode->point, goal->point))){
            goal->parent = newNode;
            return retrace();
        } 
    }

    return DiscretePath({});
}

Point RRT::getRandomPoint() const{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    if(distribution(generator) < goalSampleRate){
        return goal->point;
    }
 
    return field.randomPoint();
}

std::shared_ptr<Node> RRT::makeNewNode(const std::shared_ptr<Node>& iParent, const Point& iPoint) const{
    if(iPoint == iParent->point){
        return nullptr;
    }
            
    if(iParent->distTo(iPoint) < stepSize){
        return std::make_shared<Node>(iPoint, iParent);
    }

    auto normPt = (iPoint-iParent->point).norm();
    return std::make_shared<Node>(iParent->point + Point(normPt.first * stepSize, normPt.second * stepSize), iParent);
}

std::shared_ptr<Node> RRT::nearestNode(const Point& iPoint) const{
    return *std::min_element(vertices.begin(), vertices.end(), [&iPoint](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b){
        return a->distTo(iPoint) < b->distTo(iPoint);
    });
}

DiscretePath RRT::retrace() const{
    if(goal->parent.expired()){
        return DiscretePath({});
    }

    std::vector<Point> path;
    path.push_back(goal->point);
    auto parent = goal->parent;

    while(!parent.expired()){
        auto node = parent.lock();
        path.push_back(node->point);
        parent = node->parent;
    }

    reverse(path.begin(), path.end());
    return DiscretePath(path);
}

}