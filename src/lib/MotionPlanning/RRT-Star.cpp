#include "RRT-Star.hpp"

RRT_Star::RRT_Star(const SearchSpace& iField, 
         double iGoalSampleRate, 
         okapi::QLength iStepSize, 
         okapi::QLength iSearchRadius, 
         int iOptimizationIteration, 
         int iMaxIteration):RRT(iField, iGoalSampleRate, iStepSize, iMaxIteration){
    searchRadius = iSearchRadius;
    optimizationIteration = iOptimizationIteration;
}
    
DiscretePath RRT_Star::generatePath(const Point& iStart, const Point& iEnd){
    if(field.checkPointCollision(iStart) || field.checkPointCollision(iEnd)){
        return DiscretePath({});
    }

    start = std::make_shared<Node>(iStart);
    goal = std::make_shared<Node>(iEnd);
    vertices.clear();
    vertices.push_back(start);
    int optiIter = 0;

    for(int i = 1; i <= maxIteration; i++){
        Point sample = getRandomPoint();
        auto nearNode = nearestNode(sample);
        auto newNode = makeNewNode(nearNode, sample);

        if(!newNode || field.checkLineCollision(Line(nearNode->point, newNode->point))){
            continue;
        }
        
        auto neighbor = getNeighbor(newNode);
        chooseParent(newNode, neighbor);
        rewire(newNode, neighbor);
        vertices.push_back(newNode);

        if(!goal->parent.expired()){
            optiIter += 1;
        }

        if(goal->parent.expired() && newNode->distTo(goal->point) <= stepSize && 
           !field.checkLineCollision(Line(newNode->point, goal->point))){
            goal->parent = newNode;
            vertices.push_back(goal);
        }

        if(optiIter >= optimizationIteration){
            return retrace();
        }
    }

    return retrace();
}

std::vector<std::shared_ptr<Node>> RRT_Star::getNeighbor(const std::shared_ptr<Node>& iNode) const{
    const auto predicate = [this, &iNode](const std::shared_ptr<Node>& vertex){
        return vertex->distTo(iNode->point) < searchRadius && !field.checkLineCollision(Line(iNode->point, vertex->point));
    };

    std::vector<std::shared_ptr<Node>> ret;
    std::copy_if(vertices.begin(), vertices.end(), std::back_inserter(ret), predicate);
    return ret;
}

void RRT_Star::rewire(const std::shared_ptr<Node>& iNode, const std::vector<std::shared_ptr<Node>>& iNeighbor){
    for(auto node : iNeighbor){
        if(!node->parent.expired() && node->cost() > iNode->cost() + node->distTo(iNode->point)){
            node->parent = iNode;
        }
    }
}

void RRT_Star::chooseParent(const std::shared_ptr<Node>& iNode, const std::vector<std::shared_ptr<Node>>& iNeighbor){
    std::shared_ptr<Node> parent = iNode->parent.lock();
    for(auto node : iNeighbor){
        if(iNode->distTo(parent->point) > iNode->distTo(node->point)){
            parent = node;
        }
    }

    iNode->parent = parent;
}