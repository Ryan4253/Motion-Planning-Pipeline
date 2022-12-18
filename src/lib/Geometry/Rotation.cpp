#include "lib/Geometry/Rotation.hpp"

Rotation::Rotation(okapi::QAngle iTheta){
    theta = iTheta;
    sine = (sin(iTheta)).convert(okapi::number);
    cosine = (cos(iTheta)).convert(okapi::number);
}

Rotation::Rotation(okapi::QLength iX, okapi::QLength iY){
    const auto magnitude = hypot(iX, iY);
    if (magnitude > 1e-6 * okapi::meter) {
        sine = (iY / magnitude).convert(okapi::number);
        cosine = (iX / magnitude).convert(okapi::number);
    } else {
        sine = 0.0;
        cosine = 1.0;
    }
    theta = std::atan2(sine, cosine) * okapi::radian;
}

Rotation::Rotation(double iX, double iY){
    Rotation(iX * okapi::meter, iY * okapi::meter);
}

okapi::QAngle Rotation::Theta() const{
    return theta;
}

double Rotation::Sin() const{
    return sine;
}

double Rotation::Cos() const{
    return cosine;
}

double Rotation::Tan() const{
    return sine / cosine;
}

Rotation Rotation::operator+(const Rotation& rhs) const{
     return rotateBy(rhs); 
}

Rotation Rotation::operator-(const Rotation& rhs) const{
    return *this + -rhs;
}

Rotation Rotation::operator-() const{
    return Rotation(theta * -1);
}   

Rotation Rotation::operator*(double scalar) const{
    return Rotation(theta * scalar);
}

Rotation Rotation::operator/(double scalar) const{
    return Rotation(theta / scalar);
}

bool Rotation::operator==(const Rotation& rhs) const{
    return std::hypot(cosine - rhs.cosine, sine - rhs.sine) < 1E-9;
}

bool Rotation::operator!=(const Rotation& rhs) const{
    return !(operator==(rhs));
}

void Rotation::operator=(const Rotation& rhs){
    theta = rhs.theta;
    sine = rhs.sine;
    cosine = rhs.cosine;

}

Rotation Rotation::rotateBy(const Rotation& rhs) const{
    return {(cosine * rhs.cosine - sine * rhs.sine) * okapi::meter, (cosine * rhs.sine + sine * rhs.cosine) * okapi::meter};
}
