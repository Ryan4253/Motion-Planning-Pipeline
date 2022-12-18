#pragma once
#include "okapi/api/units/QAngle.hpp"

double deadband(double iValue, double iDeadband);

double rescale180(double iAngle);

okapi::QAngle rescale180(okapi::QAngle iAngle);

