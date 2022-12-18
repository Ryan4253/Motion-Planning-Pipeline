#pragma once
#include "Rotation.hpp"
#include "okapi/api/units/QArea.hpp"
#include <algorithm>
namespace lib{

class Point{
    public:
    constexpr Point() = default;

    Point(okapi::QLength iX, okapi::QLength iY);

    Point(okapi::QLength iMag, const Rotation& iAngle);

    Point(const Point& rhs);

    ~Point() = default;

    okapi::QLength X() const;

    okapi::QLength Y() const;

    okapi::QAngle Theta() const;

    void setX(okapi::QLength iX);

    void setY(okapi::QLength iY);

    Point operator+(const Point& rhs) const;

    Point operator-(const Point& rhs) const;

    Point operator-() const;

    Point operator*(double scalar) const;

    Point operator/(double scalar) const;

    bool operator==(const Point& rhs) const;

    bool operator!=(const Point& rhs) const;

    void operator=(const Point& rhs);

    okapi::QArea dot(const Point& rhs) const;

    okapi::QArea cross(const Point& rhs) const;

    std::pair<okapi::Number, okapi::Number> norm() const;

    okapi::QLength distTo(const Point& rhs) const;

    okapi::QAngle angleTo(const Point& rhs) const;

    okapi::QLength mag() const;

    Point rotateBy(const Rotation& rhs) const;

    Point project(const Point& rhs) const;
    
    private:
    okapi::QLength x = 0 * okapi::meter;
    okapi::QLength y = 0 * okapi::meter;
};

}