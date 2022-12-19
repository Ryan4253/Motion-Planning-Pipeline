#include "IteratingThreeEncoderOdometry.hpp"

namespace lib{

IteratingThreeEncoderOdometry::IteratingThreeEncoderOdometry(const okapi::TimeUtil& iTimeUtil,
                            const std::shared_ptr<okapi::ReadOnlyChassisModel>& iModel,
                            const okapi::ChassisScales& iChassisScales,
                            const std::shared_ptr<okapi::Logger>& iLogger):
    okapi::ThreeEncoderOdometry(iTimeUtil, iModel, iChassisScales, iLogger){}

void IteratingThreeEncoderOdometry::loop(){
    while(true){
        pros::delay(10);
        step();
    }
}

}