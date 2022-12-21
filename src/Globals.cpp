#include "Globals.hpp"

// CONTROLLERS
Controller master(ControllerId::master);

// MOTORS
Motor topLeft(8);
Motor topRight(-9);
Motor bottomLeft(1);
Motor bottomRight(-2);

// SENSORS
std::shared_ptr<ADIEncoder> leftTracker = std::make_shared<ADIEncoder>('A', 'B', true);
std::shared_ptr<ADIEncoder> midTracker = std::make_shared<ADIEncoder>('C', 'D', true);
std::shared_ptr<ADIEncoder> rightTracker = std::make_shared<ADIEncoder>('E', 'F');
std::shared_ptr<IMU> imu = std::make_shared<IMU>(12);

// CHASSIS
std::shared_ptr<XDriveModel> chassis = std::make_shared<XDriveModel>(
    std::make_shared<Motor>(8),
    std::make_shared<Motor>(-9),
    std::make_shared<Motor>(-2),
    std::make_shared<Motor>(1),
    nullptr, nullptr, 200, 12000
);

// ODOMETRY
std::shared_ptr<lib::IteratingThreeEncoderOdometry> odom = std::make_shared<lib::IteratingThreeEncoderOdometry>(
    TimeUtilFactory::createDefault(),
    std::make_shared<ThreeEncoderSkidSteerModel>(
        nullptr, nullptr,
        leftTracker,
        rightTracker,
        midTracker,
        0, 0
    ),
    ChassisScales({2.75_in, 12.283_in, 6.042_in, 2.75_in}, 360)
);