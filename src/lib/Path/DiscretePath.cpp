#include "DiscretePath.hpp"

namespace lib{

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

std::vector<Point>::const_iterator DiscretePath::cbegin() const{
    return path.cbegin();
}

std::vector<Point>::const_iterator DiscretePath::cend() const{
    return path.cend();
}

const Point& DiscretePath::front() const{
    return path.front();
}

const Point& DiscretePath::back() const{
    return path.back();
}

Point& DiscretePath::operator[](int iIndex){
    return path[std::clamp(iIndex, 0, (int)path.size())];
}

Point DiscretePath::getPoint(int iIndex) const{
    return path[std::clamp(iIndex, 0, (int)path.size())];
}

okapi::QLength DiscretePath::getLength() const{
    return length;
}

int DiscretePath::size() const{
    return path.size();
}

std::string DiscretePath::str() const{
    std::string ret = "";
    for(auto pt : path){
        ret += std::to_string(pt.X().convert(okapi::foot)) + ' ' + std::to_string(pt.Y().convert(okapi::foot)) + '\n';
    }

    return ret;
}
}