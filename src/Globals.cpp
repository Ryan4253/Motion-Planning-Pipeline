#include "Globals.hpp"

// CONTROLLERS
Controller master(ControllerId::master);

// MOTORS
std::shared_ptr<Motor> topLeft = std::make_shared<Motor>(8);
std::shared_ptr<Motor> topRight = std::make_shared<Motor>(-9);
std::shared_ptr<Motor> bottomLeft = std::make_shared<Motor>(1);
std::shared_ptr<Motor> bottomRight = std::make_shared<Motor>(-2);

// SENSORS
std::shared_ptr<ADIEncoder> leftTracker = std::make_shared<ADIEncoder>('A', 'B', true);
std::shared_ptr<ADIEncoder> midTracker = std::make_shared<ADIEncoder>('C', 'D');
std::shared_ptr<ADIEncoder> rightTracker = std::make_shared<ADIEncoder>('E', 'F');
std::shared_ptr<IMU> imu = std::make_shared<IMU>(12);

// CHASSIS
std::shared_ptr<ThreeEncoderXDriveModel> chassis = std::make_shared<ThreeEncoderXDriveModel>(
    topLeft, topRight, bottomRight, bottomLeft,
    leftTracker, rightTracker, midTracker,
    200, 12000
);

// ODOMETRY
std::shared_ptr<lib::IteratingThreeEncoderOdometry> odom = std::make_shared<lib::IteratingThreeEncoderOdometry>(
    TimeUtilFactory::createDefault(),
    chassis,
    ChassisScales({7.003_cm, 31.279_cm, 15.387_cm, 7.003_cm}, 360)
);

// PID
ConfigurableTimeUtilFactory timer(1, 1, 100_ms);
std::shared_ptr<IterativePosPIDController> distPID = std::make_shared<IterativePosPIDController>(0.03, 0, 0, 0, timer.create());
std::shared_ptr<IterativePosPIDController> turnPID = std::make_shared<IterativePosPIDController>(0.01, 0, 0, 0, timer.create());

// PURE PURSUIT
std::shared_ptr<lib::PurePursuitController> PPTenshi = std::make_shared<lib::PurePursuitController>(
    chassis, odom, distPID, turnPID, 6_in
);




