#pragma once
#include "okapi/api/odometry/odomState.hpp"
#include "Point.hpp"

namespace lib{

struct Pose{
    Pose(const okapi::OdomState& iState);

    Point point;
    Rotation rotation;
};

}