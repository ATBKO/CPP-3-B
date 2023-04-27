#include "Fraction.hpp"
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <iostream>

namespace ariel {

    Fraction::Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        int gcd = std::gcd(numerator, denominator);
        this->numerator = numerator / gcd;
        this->denominator = denominator / gcd;
    }

    Fraction::Fraction(float value) {
        int multiplier = 1000; // Use 1000 to preserve 3 decimal points
        int numerator = std::round(value * multiplier);
        int denominator = multiplier;
        int gcd = std::gcd(numerator, denominator);
        this->numerator = numerator / gcd;
        this->denominator = denominator / gcd;
    }

    int Fraction::getNumerator() const {
        return numerator;
    }

    int Fraction::getDenominator() const {
        return denominator;
    }

    Fraction Fraction::operator+(const Fraction& other) const {
        int common_denominator = std::lcm(denominator, other.denominator);
        int new_numerator = numerator * (common_denominator / denominator) + other.numerator * (common_denominator / other.denominator);
        return Fraction(new_numerator, common_denominator);
    }

    Fraction Fraction::operator-(const Fraction& other) const {
        int common_denominator = std::lcm(denominator, other.denominator);
        int new_numerator = numerator * (common_denominator / denominator) - other.numerator * (common_denominator / other.denominator);
        return Fraction(new_numerator, common_denominator);
    }

    Fraction Fraction::operator*(const Fraction& other) const {
        int new_numerator = numerator * other.numerator;
        int new_denominator = denominator * other.denominator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        int new_numerator = numerator * other.denominator;
        int new_denominator = denominator * other.numerator;
        return Fraction(new_numerator, new_denominator);
    }

    bool Fraction::operator<(const Fraction& other) const {
        return (double)numerator / denominator < (double)other.numerator / other.denominator;
    }

    bool Fraction::operator<=(const Fraction& other) const {
        return (double)numerator / denominator <= (double)other.numerator / other.denominator;
    }

    bool Fraction::operator>(const Fraction& other) const {
        return (double)numerator / denominator > (double)other.numerator / other.denominator;
    }

    bool Fraction::operator>=(const Fraction& other) const {
        return (double)numerator / denominator >= (double)other.numerator / other.denominator;
    }

    bool Fraction::operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    Fraction& Fraction::operator++() {
        numerator += denominator;
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        numerator += denominator;
        return temp;
    }

    Fraction& Fraction::operator--() {
        numerator -= denominator;
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        numerator -= denominator;
        return temp;
    }


    Fraction& Fraction::operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& Fraction::operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& Fraction::operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& Fraction::operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
        os << fraction.getNumerator() << "/" << fraction.getDenominator();
        return os;
    }

    std::istream& operator>>(std::istream& is, Fraction& fraction) {
        int numerator, denominator;
        char slash; // Used to consume the '/' character in the input
        is >> numerator >> slash >> denominator;
        if (is && slash == '/') {
            fraction = Fraction(numerator, denominator);
        } else {
            is.setstate(std::ios::failbit);
        }
        return is;
    }
} // end namespace ariel
