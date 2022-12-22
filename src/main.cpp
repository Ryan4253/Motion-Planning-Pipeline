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
	//odom->startTask();

	//PPTenshi->moveToPoint(lib::Point(1_ft, 2_ft));
	using lib::CubicBezier;
	using lib::Point;
	auto bez = CubicBezier({CubicBezier::Knot(0_ft, 0_ft, 90_deg, 2_ft), CubicBezier::Knot(2_ft, 4_ft, 90_deg, 2_ft)});
	auto path = bez.generate(3_in);

	std::cout << path.str() << std::endl;

	while (true) {
		chassis->fieldOrientedXArcade(master.getAnalog(ControllerAnalog::leftY),
					   				  master.getAnalog(ControllerAnalog::leftX),
					   				  master.getAnalog(ControllerAnalog::rightX),
									  imu->get() * okapi::degree,
					   				  0.05);

		//std::cout << lib::Pose(odom->getState(StateMode::CARTESIAN)).str() << std::endl;
		pros::delay(10);
	}
}
