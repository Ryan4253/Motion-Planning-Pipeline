#include "Globals.hpp"

// CONSTANTS
const double DEADBAND = 0.05;

// CONTROLLERS
Controller master(ControllerId::master);

// MOTORS
Motor topLeft(8);
Motor topRight(-9);
Motor bottomLeft(1);
Motor bottomRight(-2);

// SENSORS
ADIEncoder leftTracker('A', 'B');
ADIEncoder midTracker('C', 'D');
ADIEncoder rightTracker('E', 'F');
IMU imu(12);

// CHASSIS
std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors(topLeft, topRight, bottomRight, bottomLeft)
    .withSensors(leftTracker, rightTracker, midTracker)
    .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 15_in}, imev5GreenTPR})
    .withOdometry({{2.75_in, 13_in, 6.5_in, 2.75_in}, quadEncoderTPR})
    .buildOdometry();

std::shared_ptr<XDriveModel> model = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());
