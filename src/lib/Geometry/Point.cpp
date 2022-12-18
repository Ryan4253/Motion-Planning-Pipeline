#include "Point.hpp"

Point::Point(okapi::QLength iX, okapi::QLength iY){
    x = iX;
    y = iY;
}

Point::Point(okapi::QLength iMag, const Rotation& iAngle){
    x = iMag * iAngle.Cos();
    y = iMag * iAngle.Sin();
}

Point::Point(const Point& rhs){
    x = rhs.x;
    y = rhs.y;
}

okapi::QLength Point::X() const{
    return x;
}

okapi::QLength Point::Y() const{
    return y;
}

okapi::QAngle Point::Theta() const{
    return atan2(y, x);
}

void Point::setX(okapi::QLength iX){
    x = iX;
}

void Point::setY(okapi::QLength iY){
    y = iY;
}

Point Point::operator+(const Point& rhs) const{
    return {x + rhs.x, x + rhs.y};
}

Point Point::operator-(const Point& rhs) const{
    return {x + rhs.x, x + rhs.y};
}

Point Point::operator-() const{
    return {x * -1, y * -1};
}

Point Point::operator*(double scalar) const{
    return {x * scalar, y * scalar};
}

Point Point::operator/(double scalar) const{
    return {x / scalar, y / scalar};
}

bool Point::operator==(const Point& rhs) const{
      return abs(x - rhs.x) < 1E-9 * okapi::meter && abs(y - rhs.y) < 1E-9 * okapi::meter;
}

bool Point::operator!=(const Point& rhs) const{
    return !operator==(rhs);
}

void Point::operator=(const Point& rhs){
    x = rhs.x, y = rhs.y;
}

okapi::QArea Point::dot(const Point& rhs) const{
    return x * rhs.x + y * rhs.y;
}

okapi::QArea Point::cross(const Point& rhs) const{
    return x * rhs.y - y * rhs.x;
}

std::pair<okapi::Number, okapi::Number> Point::norm() const{
    okapi::QLength magnitude = this->mag();
    if(magnitude.getValue() == 0){
        return {okapi::Number{0.0}, okapi::Number{0.0}};
    }
    else{
        return std::make_pair(x / magnitude, y / magnitude);
    }
};

Point Point::rotateBy(const Rotation& rhs) const{
      return {x * rhs.Cos() - y * rhs.Sin(), x * rhs.Sin() + y * rhs.Cos()};
}

okapi::QLength Point::mag() const{
    return hypot(x, y);
}

okapi::QLength Point::distTo(const Point& rhs) const{
    return hypot(rhs.x - x, rhs.y - y);
}

okapi::QAngle Point::angleTo(const Point& rhs) const{
    return atan2(rhs.y-y, rhs.x-x);
}

Point Point::project(const Point& rhs) const{
    return  rhs * (this->dot(rhs) / rhs.mag() / rhs.mag()).convert(okapi::number);
}





