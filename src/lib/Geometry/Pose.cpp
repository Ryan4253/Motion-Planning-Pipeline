#include "Pose.hpp"

Pose::Pose(const okapi::OdomState& iState){
    point = Point(iState.x, -1 * iState.y);
    rotation = Rotation(iState.theta);
}