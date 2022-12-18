#pragma once
#include "lib/Geometry/Point.hpp"
#include<memory>

struct Node{
    Node(const Point& iPoint, const std::weak_ptr<Node>& iParent = std::weak_ptr<Node>());

    okapi::QLength distTo(const Node& iNode) const;

    okapi::QLength distTo(const Point& iPoint) const;

    okapi::QLength cost() const;

    bool isRoot() const;

    Point point;
    
    std::weak_ptr<Node> parent;
};

