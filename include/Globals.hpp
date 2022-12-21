#pragma once
#include "main.h"
#include "lib/api.hpp"
using namespace okapi;

// CONSTANTS
const double DEADBAND = 0.05;

// CONTROLLER
extern Controller master;

// MOTORS
extern Motor topLeft;
extern Motor topRight;
extern Motor bottomLeft;
extern Motor bottomRight;

// SENSORS
extern std::shared_ptr<ADIEncoder> leftTracker;
extern std::shared_ptr<ADIEncoder> midTracker;
extern std::shared_ptr<ADIEncoder> rightTracker;
extern std::shared_ptr<IMU> imu;

// CHASSIS
extern std::shared_ptr<XDriveModel> chassis;

// ODOMETRY
extern std::shared_ptr<lib::IteratingThreeEncoderOdometry> odom;
