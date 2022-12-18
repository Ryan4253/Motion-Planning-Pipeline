#pragma once
#include "MotionPlanner.hpp"
#include "Node.hpp"
#include <memory>

namespace lib{

class RRT : public MotionPlanner{
    public:
    RRT(const SearchSpace& iField, double iGoalSampleRate, okapi::QLength iStepSize, int iMaxIteration);

    virtual DiscretePath generatePath(const Point& iStart, const Point& iEnd) override;

    Point getRandomPoint() const;

    std::shared_ptr<Node> makeNewNode(const std::shared_ptr<Node>& iParent, const Point& iPoint) const;

    std::shared_ptr<Node> nearestNode(const Point& iPoint) const;

    DiscretePath retrace() const;

    protected:
    double goalSampleRate;
    okapi::QLength stepSize;
    double maxIteration;
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> goal;
    std::vector<std::shared_ptr<Node>> vertices;
};

}