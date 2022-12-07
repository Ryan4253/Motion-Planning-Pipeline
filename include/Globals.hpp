#pragma once
#include "main.h"
using namespace okapi;

extern Controller master;

extern Motor topLeft;
extern Motor topRight;
extern Motor bottomLeft;
extern Motor bottomRight;

extern IMU imu;

extern std::shared_ptr<OdomChassisController> chassis;
extern std::shared_ptr<XDriveModel> model;