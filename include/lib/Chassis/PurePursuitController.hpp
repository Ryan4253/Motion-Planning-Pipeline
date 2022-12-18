#pragma once
#include "lib/Geometry/Pose.hpp"
#include "okapi/api/control/iterative/iterativePositionController.hpp"
#include "okapi/api/control/iterative/iterativePosPidController.hpp"
#include "okapi/api/chassis/model/xDriveModel.hpp"
#include "okapi/api/odometry/odometry.hpp"
#include "lib/Path/DiscretePath.hpp"
#include "lib/Utility/Math.hpp"
#include <memory>

class PurePursuitController{
    public:
    PurePursuitController(const std::shared_ptr<okapi::XDriveModel>& iChassis,
                          const std::shared_ptr<okapi::Odometry>& iOdometry,
                          const std::shared_ptr<okapi::IterativePositionController<double, double>>& iDistController,
                          const std::shared_ptr<okapi::IterativePositionController<double, double>>& iTurnController,
                          okapi::QLength iLookAheadDistance);

    void moveToPoint(const Point& iPoint);

    void followPath(const DiscretePath& iPath);

    Point getLookAheadPoint(const DiscretePath& iPath, const Point& iPos);

    double findIntersection(const Point& iStart,  const Point& iEnd, const Point& iPos) const;

    Point closestPoint(const DiscretePath& iPath, const Point& iPos) const;

    protected:
    std::shared_ptr<okapi::XDriveModel> chassis;
    std::shared_ptr<okapi::Odometry> odometry;
    std::shared_ptr<okapi::IterativePositionController<double, double>> distController;
    std::shared_ptr<okapi::IterativePositionController<double, double>> turnController;
    okapi::QLength lookAheadDistance;
    int prevIndex = 0;
    double prevT = 0;
};