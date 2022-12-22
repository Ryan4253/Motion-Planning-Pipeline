#pragma once
#include "main.h"
#include "lib/api.hpp"
using namespace okapi;

// CONSTANTS
const double DEADBAND = 0.05;

// CONTROLLER
extern Controller master;

// MOTORS
extern std::shared_ptr<Motor> topLeft;
extern std::shared_ptr<Motor> topRight;
extern std::shared_ptr<Motor> bottomLeft;
extern std::shared_ptr<Motor> bottomRight;

// SENSORS
extern std::shared_ptr<ADIEncoder> leftTracker;
extern std::shared_ptr<ADIEncoder> midTracker;
extern std::shared_ptr<ADIEncoder> rightTracker;
extern std::shared_ptr<IMU> imu;

// CHASSIS
extern std::shared_ptr<ThreeEncoderXDriveModel> chassis;

// ODOMETRY
extern std::shared_ptr<lib::IteratingThreeEncoderOdometry> odom;

// PID
extern std::shared_ptr<IterativePosPIDController> distPID;
extern std::shared_ptr<IterativePosPIDController> turnPID;

// PURE PURSUIT
extern std::shared_ptr<lib::PurePursuitController> PPTenshi;
