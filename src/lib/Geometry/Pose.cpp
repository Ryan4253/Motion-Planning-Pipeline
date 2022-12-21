#include "Pose.hpp"

namespace lib{

Pose::Pose(const okapi::OdomState& iState){
    point = Point(iState.y, -1 * iState.x);
    rotation = Rotation(rescale180(-1 * iState.theta));
}

std::string Pose::str() const{
    return "Pose(X: " + std::to_string(point.X().convert(okapi::inch)) + "_in, " + 
           "Y: " + std::to_string(point.Y().convert(okapi::inch)) + "_in, "
           "Theta: " + std::to_string(rotation.Theta().convert(okapi::degree)) + "_deg)";
}

}