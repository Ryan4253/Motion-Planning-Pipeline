#include "Node.hpp"

namespace lib{

Node::Node(const Point& iPoint, const std::weak_ptr<Node>& iParent) : point(iPoint){
    parent = iParent;
} 

okapi::QLength Node::distTo(const Node& iNode) const{
    return point.distTo(iNode.point);
}

okapi::QLength Node::distTo(const Point& iPoint) const{
    return point.distTo(iPoint);
}

okapi::QLength Node::cost() const{
    if(isRoot()){
        return 0 * okapi::meter;
    }

    return distTo(parent.lock()->point) + parent.lock()->cost();
}

bool Node::isRoot() const{
    return parent.expired();
}

}