#include "main.h"

void initialize(){
	pros::lcd::initialize();
	imu->calibrate();
	pros::delay(2500);
}

void disabled(){}

void competition_initialize(){}

void autonomous(){}

void opcontrol(){
	odom->startTask();
	while (true) {
		chassis->fieldOrientedXArcade(master.getAnalog(ControllerAnalog::leftY),
					   				  master.getAnalog(ControllerAnalog::leftX),
					   				  master.getAnalog(ControllerAnalog::rightX),
									  imu->get() * okapi::degree,
					   				  0.05);

		std::cout << lib::Pose(odom->getState(StateMode::CARTESIAN)).str() << std::endl;
		//pros::lcd::set_text(0, std::to_string((std::abs(leftTracker.get()) + std::abs(rightTracker.get()))/2));
		//pros::lcd::set_text(1, std::to_string(std::abs(midTracker.get())));
		pros::delay(10);
	}
}
