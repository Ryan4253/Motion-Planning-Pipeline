#include "Pose.hpp"

namespace lib{

Pose::Pose(const okapi::OdomState& iState){
    point = Point(iState.x, iState.y);
    rotation = Rotation(rescale180(-1 * iState.theta));
}

std::string Pose::str() const{
    return "Pose(X: " + std::to_string(point.X().convert(okapi::foot)) + "_ft, " + 
           "Y: " + std::to_string(point.Y().convert(okapi::foot)) + "_ft, "
           "Theta: " + std::to_string(rotation.Theta().convert(okapi::degree)) + "_deg)";
}

}