#pragma once
#include "okapi/api/odometry/odomState.hpp"
#include "Point.hpp"

struct Pose{
    Pose(const okapi::OdomState& iState);

    Point point;
    Rotation rotation;
};