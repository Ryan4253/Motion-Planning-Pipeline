#include "DiscretePath.hpp"

DiscretePath::DiscretePath(const std::initializer_list<Point>& iPath) : path(iPath){
    length = 0 * okapi::meter;
    for(int i = 0; i < path.size()-1; i++){
        length += path[i].distTo(path[i+1]);
    }
}

DiscretePath::DiscretePath(const std::vector<Point>& iPath) : path(iPath){
    length = 0 * okapi::meter;
    for(int i = 0; i < path.size()-1; i++){
        length += path[i].distTo(path[i+1]);
    }
}

std::vector<Point>::iterator DiscretePath::begin(){
    return path.begin();
}

std::vector<Point>::iterator DiscretePath::end(){
    return path.end();
}

Point& DiscretePath::operator[](int iIndex){

    return path[std::max(std::min(iIndex, (int)path.size()), 0)];
}

Point DiscretePath::getPoint(int iIndex) const{
    return path[std::max(std::min(iIndex, (int)path.size()), 0)];
}

okapi::QLength DiscretePath::getLength() const{
    return length;
}

int DiscretePath::size() const{
    return path.size();
}