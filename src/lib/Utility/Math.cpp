#include "Math.hpp"

namespace lib{

double deadband(double iValue, double iDeadband){
    if(std::abs(iValue) < iDeadband){
        return 0;
    }

    return iValue;
}

double rescale180(double iAngle){
    return iAngle - 360.0 * std::floor((iAngle + 180.0) * (1.0 / 360.0));
}

okapi::QAngle rescale180(okapi::QAngle iAngle){
    return rescale180(iAngle.convert(okapi::degree)) * okapi::degree;
}

}