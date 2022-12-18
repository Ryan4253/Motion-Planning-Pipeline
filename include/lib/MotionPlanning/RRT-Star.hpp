#pragma once
#include "RRT.hpp"

class RRT_Star : public RRT{
    public:
    RRT_Star(const SearchSpace& iField, 
             double iGoalSampleRate, 
             okapi::QLength iStepSize, 
             okapi::QLength iSearchRadius, 
             int iOptimizationIteration, 
             int iMaxIteration);
    
    virtual DiscretePath generatePath(const Point& iStart, const Point& iEnd) override;

    std::vector<std::shared_ptr<Node>> getNeighbor(const std::shared_ptr<Node>& iNode) const;

    void rewire(const std::shared_ptr<Node>& iNode, const std::vector<std::shared_ptr<Node>>& iNeighbor);

    void chooseParent(const std::shared_ptr<Node>& iNode, const std::vector<std::shared_ptr<Node>>& iNeighbor);

    protected:
    okapi::QLength searchRadius;
    int optimizationIteration;
};