#pragma once
#include "okapi/api/odometry/threeEncoderOdometry.hpp"
#include "lib/Utility/TaskWrapper.hpp"

namespace lib{

class IteratingThreeEncoderOdometry : public okapi::ThreeEncoderOdometry, public TaskWrapper{
    IteratingThreeEncoderOdometry(const okapi::TimeUtil& iTimeUtil,
                                  const std::shared_ptr<okapi::ReadOnlyChassisModel>& iModel,
                                  const okapi::ChassisScales& iChassisScales,
                                  const std::shared_ptr<okapi::Logger>& iLogger = okapi::Logger::getDefaultLogger());

    void loop() override;
};

}