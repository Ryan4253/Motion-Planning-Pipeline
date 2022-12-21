#pragma once
#include "okapi/api/odometry/odomState.hpp"
#include "Point.hpp"
#include "lib/Utility/Math.hpp"

namespace lib{

struct Pose{
    Pose(const okapi::OdomState& iState);

    std::string str() const;

    Point point;
    Rotation rotation;
};

}