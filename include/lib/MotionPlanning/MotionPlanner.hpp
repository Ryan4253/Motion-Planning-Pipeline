#pragma once
#include "SearchSpace.hpp"
#include "lib/Path/DiscretePath.hpp"

class MotionPlanner{
    public:
    MotionPlanner(const SearchSpace& iField);

    virtual DiscretePath generatePath(const Point& iStart, const Point& iEnd) = 0;

    protected:
    SearchSpace field;

};