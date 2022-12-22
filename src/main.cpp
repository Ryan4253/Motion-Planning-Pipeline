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
	using namespace lib;
	odom->startTask();
	odom->setState(OdomState{0_ft, 0_ft, 0_deg});

	std::vector<std::shared_ptr<Polygon>> obstacles = {
		std::make_shared<Rectangle>(lib::Point(95_in, 23_in), lib::Point(97_in, 49_in)),
		std::make_shared<Rectangle>(lib::Point(95_in, 47_in), lib::Point(121_in, 49_in)),
		std::make_shared<Rectangle>(lib::Point(23_in, 95_in), lib::Point(49_in, 97_in)),
		std::make_shared<Rectangle>(lib::Point(47_in, 95_in), lib::Point(49_in, 116_in)),
		std::make_shared<Circle>(lib::Point(6_ft, 6_ft), 7.865_in)
	};
	SearchSpace field(12_ft, 12_ft, obstacles, 8.66_in);
	RRT_Star rrtStar(field, 0.1, 0.5_ft, 2_ft, 300, 5000);
	//auto path = rrtStar.generatePath(lib::Point(2_ft, 2_ft), lib::Point(6_ft, 8_ft));

	// std::cout << path.str() << std::endl;
	auto path = lib::CubicBezier({lib::CubicBezier::Knot(0_ft, 0_ft, 90_deg, 2_ft), lib::CubicBezier::Knot(2_ft, 4_ft, 90_deg, 2_ft)}).generate(3_in);

	PPTenshi->followPath(path);

	while (true) {
		chassis->fieldOrientedXArcade(master.getAnalog(ControllerAnalog::leftY),
					   				  master.getAnalog(ControllerAnalog::leftX),
					   				  master.getAnalog(ControllerAnalog::rightX),
									  imu->get() * okapi::degree,
					   				  0.05);

		//std::cout << lib::Pose(odom->getState()).str() << std::endl;
		pros::lcd::set_text(0, std::to_string((std::abs(leftTracker->get()) + std::abs(rightTracker->get()))/2));
		pros::lcd::set_text(1, std::to_string(midTracker->get()));
		pros::delay(10);
	}
}
