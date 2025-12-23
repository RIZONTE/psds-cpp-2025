#include <cmath>
#include <numbers>

namespace {
    constexpr double eps_ = 1e-6;
    constexpr double pi_ = std::numbers::pi;
}

struct ExpTag {};
struct DegTag {};
struct AlgTag {};


class Phasor {
public:
    Phasor() = default;
    Phasor(double mag, double phase);
    Phasor(double mag, double phase, ExpTag) : Phasor(mag, phase) {};
    Phasor(double mag, double phase, DegTag);
    Phasor(double re, double im, AlgTag);

    void SetPolar(double mag, double phase);
    void SetCartesian(double re, double im);
    double Magnitude() const;
    double Phase() const;
    double PhaseDeg() const;
    double Abs() const;
    double Angle() const;
    double AngleDeg() const;
    double Real() const;
    double Imag() const;

    Phasor Conj();
    Phasor Inv();


private:
    double mag_{0.0};
    double phase_{0.0};

    // Методы для поддержания инварианта класса
    void PhaseNormalize();
};

void Phasor::PhaseNormalize(){
    phase_ -= mag_ >= 0 ? 0 : pi_;
    phase_ = phase_ - 2 * pi_ * floor((phase_ + pi_) / (2 * pi_));
}

Phasor::Phasor(double mag, double phase) : mag_(mag), phase_(phase) {
    PhaseNormalize();
}

Phasor::Phasor(double mag, double phase, DegTag) : mag_(mag), phase_((pi_ / 180.0) * phase){
    PhaseNormalize();
}

Phasor::Phasor(double re, double im, AlgTag) {
    mag_ = sqrt(re * re + im * im);
    phase_ = atan2(im, re);
    PhaseNormalize();
}

void Phasor::SetPolar(double mag, double phase){
    mag_ = mag;
    phase_ = phase;
    PhaseNormalize();
}

void Phasor::SetCartesian(double re, double im){
    mag_ = sqrt(re * re + im * im);
    phase_ = atan2(im, re);
    PhaseNormalize();
}
double Phasor::Magnitude() const {
    return abs(mag_);
}

double Phasor::Phase() const {
    return phase_;
}

double Phasor::PhaseDeg() const {
    return (180.0 / pi_) * phase_;
}

double Phasor::Abs() const {
    return Magnitude();
}

double Phasor::Angle() const {
    return Phase(); 
}

double Phasor::AngleDeg() const { 
    return PhaseDeg(); 
}

double Phasor::Real() const {
    return abs(mag_) * cos(phase_);
}

double Phasor::Imag() const {
    return abs(mag_) * sin(phase_);
}

bool operator==(const Phasor& lhs, const Phasor& rhs){
    return (abs(lhs.Magnitude() - rhs.Magnitude()) < eps_) && 
           (abs(lhs.Phase() - rhs.Phase()) < eps_);
}

bool operator!=(const Phasor& lhs, const Phasor& rhs){
    return !(lhs == rhs);
}

Phasor operator+(const Phasor& lhs, const Phasor& rhs){
    rhs.Abs();
    return lhs; //!!!!!!!!!!!!!!!!!!!!!!!!
}
Phasor operator-(const Phasor& lhs, const Phasor& rhs){
    rhs.Abs();
    return lhs; //!!!!!!!!!!!!!!!!!!!!!!!!
}
Phasor operator*(const Phasor& lhs, const Phasor& rhs){
    rhs.Abs();
    return lhs; //!!!!!!!!!!!!!!!!!!!!!!!!
}
Phasor operator/(const Phasor& lhs, const Phasor& rhs){
    rhs.Abs();
    return lhs; //!!!!!!!!!!!!!!!!!!!!!!!!
}