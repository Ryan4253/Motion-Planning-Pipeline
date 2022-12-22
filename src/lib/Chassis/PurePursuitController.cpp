#include "PurePursuitController.hpp"

namespace lib{

PurePursuitController::PurePursuitController(
    const std::shared_ptr<okapi::XDriveModel>& iChassis,
    const std::shared_ptr<okapi::Odometry>& iOdometry,
    const std::shared_ptr<okapi::IterativePositionController<double, double>>& iDistController,
    const std::shared_ptr<okapi::IterativePositionController<double, double>>& iTurnController,
    okapi::QLength iLookAheadDistance
){
    chassis = iChassis;
    odometry = iOdometry;
    distController = iDistController;
    turnController = iTurnController;
    lookAheadDistance = iLookAheadDistance;
}           

void PurePursuitController::moveToPoint(const Point& iPoint){
    okapi::QAngle targetAngle = odometry->getState().theta;
    distController->reset();
    turnController->reset();
    
    do{
        Pose pos = Pose(odometry->getState());

        double distOutput = distController->step(-pos.point.distTo(iPoint).convert(okapi::inch));
        double turnOutput = turnController->step(-rescale180(targetAngle - pos.rotation.Theta()).convert(okapi::degree)); 
        double xOutput = distOutput * cos(pos.point.angleTo(iPoint).convert(okapi::radian));
        double yOutput = distOutput * sin(pos.point.angleTo(iPoint).convert(okapi::radian));
        chassis->fieldOrientedXArcade(xOutput, -yOutput, -turnOutput, pos.rotation.Theta());
        pros::delay(10);
    }while(true);
    

    chassis->fieldOrientedXArcade(0, 0, 0, targetAngle);
}

void PurePursuitController::followPath(const DiscretePath& iPath){
    okapi::QAngle targetAngle = -1 * odometry->getState().theta;
    distController->reset();
    turnController->reset();
    prevT = 0;
    prevIndex = 0;
    
    do{
        Pose pos = Pose(odometry->getState());
        Point target = getLookAheadPoint(iPath, pos.point);
        pros::lcd::set_text(0, pos.str());
        pros::lcd::set_text(1, std::to_string(target.X().convert(okapi::foot)) + " " + std::to_string(target.Y().convert(okapi::foot)));
        pros::lcd::set_text(2, std::to_string(prevIndex));
        pros::lcd::set_text(3, std::to_string(prevT));
        double distOutput = distController->step(-pos.point.distTo(target).convert(okapi::inch));
        double turnOutput = turnController->step(-rescale180(targetAngle - pos.rotation.Theta()).convert(okapi::degree)); 
        double xOutput = distOutput * cos(pos.point.angleTo(target).convert(okapi::radian));
        double yOutput = distOutput * sin(pos.point.angleTo(target).convert(okapi::radian));
        chassis->fieldOrientedXArcade(xOutput, -yOutput, -turnOutput, pos.rotation.Theta());
        pros::delay(10);
    }while(true);

    chassis->fieldOrientedXArcade(0, 0, 0, targetAngle);
}

Point PurePursuitController::getLookAheadPoint(const DiscretePath& iPath, const Point& iPos){
    if(iPos.distTo(iPath.back()) < lookAheadDistance){
        return iPath.back();
    }

    for(int i = prevIndex; i < iPath.size()-1; i++){
        Point start = iPath.getPoint(i);
        Point end = iPath.getPoint(i+1);
        auto t = findIntersection(start, end, iPos);

        if(t != -1 && i+t >= prevT){
            prevIndex = i;
            prevT = i+t;
            return start + (end - start) * t;
        }
    }

    return closestPoint(iPath, iPos);
}

double PurePursuitController::findIntersection(const Point& iStart,  const Point& iEnd, const Point& iPos) const{
    Point d = iEnd - iStart;
    Point f = iStart - iPos;

    auto a = d.dot(d);
    auto b = 2 * (f.dot(d));
    auto c = f.dot(f) - lookAheadDistance * lookAheadDistance;
    auto discriminant = b * b - 4 * a * c;

    if(discriminant.getValue() < 0){
        return -1;
    }

    auto dis = sqrt(discriminant);
    auto t1 = ((-b - dis) / (2 * a)).convert(okapi::number);
    auto t2 = ((-b + dis) / (2 * a)).convert(okapi::number);

    if (t2 >= 0 && t2 <= 1){
        return t2;
    }
    else if(t1 >= 0 && t1 <= 1){
        return t1;
    }

    return -1;
}

Point PurePursuitController::closestPoint(const DiscretePath& iPath, const Point& iPos) const{
    return *std::min_element(iPath.cbegin(), iPath.cend(), [&iPos](Point a, Point b){
        return a.distTo(iPos) < b.distTo(iPos);
    });
}

}