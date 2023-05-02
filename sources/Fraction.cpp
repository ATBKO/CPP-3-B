//
// Created by koazg on 4/28/2023.
//
#include "Fraction.hpp"
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <iostream>

namespace ariel {

    // Fraction default constructor: Initializes fraction as 0/1
    Fraction::Fraction() : numerator(0), denominator(1) {}

    // Fraction constructor: Initializes fraction with given numerator and denominator
    // Throws invalid_argument if denominator is zero
    Fraction::Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        // Find the greatest common divisor (gcd) to simplify the fraction
        int gcd = std::gcd(numerator, denominator);
        this->numerator = numerator / gcd;
        this->denominator = denominator / gcd;
        simplify(); // Simplify the fraction further if possible
    }

    // Fraction constructor: Initializes fraction with given floating point number
    Fraction::Fraction(float f) {
        // Convert float to fraction by shifting decimal point to the right
        // until we get an integer numerator
        int i = 0;
        for (; i < 3 && f != round(f); i++) {
            f *= 10;
        }
        this->numerator = round(f);
        this->denominator = pow(10, i);
        simplify(); // Simplify the fraction if possible
    }

    // Getter for numerator
    int Fraction::getNumerator() const {
        return this->numerator;
    }

    // Getter for denominator
    int Fraction::getDenominator() const {
        return this->denominator;
    }

    // Addition operator: Adds two fractions
    // Throws overflow_error if resulting fraction would overflow int range
    Fraction Fraction::operator+(const Fraction &other) const {
        // Find least common multiple (lcm) of denominators to add fractions
        int common_denominator = std::lcm(denominator, other.denominator);
        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();
        // Check for overflow before performing addition
        // This checks whether the new numerator would be too large or too small for an int
        // by multiplying the current numerator and denominator by the respective factors
        // If the new values would be out of the int range, throws overflow_error
        if (common_denominator != 0 &&
            ((std::abs(numerator) > max_int / std::abs(common_denominator / denominator)) ||
             (std::abs(other.numerator) > max_int / std::abs(common_denominator / other.denominator)))) {
            throw std::overflow_error("Fraction overflow");
        }
        int term1 = numerator * (common_denominator / denominator);
        int term2 = other.numerator * (common_denominator / other.denominator);
        // Check for overflow during addition
        if ((term1 > 0 && term2 > max_int - term1) || (term1 < 0 && term2 < min_int - term1)) {
            throw std::overflow_error("Fraction overflow");
        }
        // Return resulting fraction after addition
        return Fraction(term1 + term2, common_denominator);
    }

    Fraction Fraction::operator-(const Fraction &other) const {
        int common_denominator = std::lcm(denominator, other.denominator);
        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();
        if (common_denominator != 0 &&
            ((std::abs(numerator) > max_int / std::abs(common_denominator / denominator)) ||
             (std::abs(other.numerator) > max_int / std::abs(common_denominator / other.denominator)))) {
            throw std::overflow_error("Fraction overflow");
        }
        int term1 = numerator * (common_denominator / denominator);
        int term2 = other.numerator * (common_denominator / other.denominator);
        if ((term1 > 0 && term2 < term1 - max_int) || (term1 < 0 && term2 > term1 - min_int)) {
            throw std::overflow_error("Fraction overflow");
        }
        return Fraction(term1 - term2, common_denominator);
    }

    // Multiplication operator: Multiplies two fractions
    // Throws overflow_error if resulting fraction would overflow int range
    Fraction Fraction::operator*(const Fraction &other) const {
        if (numerator == 0 || other.numerator == 0) {
            return Fraction(0, 1);  // If either fraction is 0, return 0
        }
        // Check for overflow before performing multiplication
        // If the new numerator or denominator would be too large for an int, throw overflow_error
        if (std::abs(other.numerator) > std::numeric_limits<int>::max() / std::abs(numerator) ||
            std::abs(other.denominator) > std::numeric_limits<int>::max() / std::abs(denominator)) {
            throw std::overflow_error("Fraction overflow");
        }
        // Perform multiplication and return the resulting fraction
        int new_numerator = numerator * other.numerator;
        int new_denominator = denominator * other.denominator;
        return Fraction(new_numerator, new_denominator);
    }


    // Division operator: Divides one fraction by another
    // Throws runtime_error if dividing by zero
    // Throws overflow_error if resulting fraction would overflow int range
    Fraction Fraction::operator/(const Fraction &other) const {
        if (other.numerator == 0) {
            throw std::runtime_error("Division by zero");
        }
        // Check for overflow before performing division
        if (other.numerator != other.denominator && other.numerator != 0 &&
            (other.denominator > std::numeric_limits<int>::max() / std::abs(other.numerator) ||
             other.denominator < std::numeric_limits<int>::min() / std::abs(other.numerator))) {
            throw std::overflow_error("Fraction overflow");
        }
        // Perform division and return the resulting fraction
        int new_numerator = numerator * other.denominator;
        int new_denominator = denominator * other.numerator;
        return Fraction(new_numerator, new_denominator);
    }


    // Comparison operators: Compares two fractions
    // The less than (<), less than or equal to (<=), greater than (>),
    // greater than or equal to (>=), and equality (==) operators
    // all compare two Fraction objects. They convert each fraction to
    // a floating point number and then perform the comparison.

    bool Fraction::operator<(const Fraction &other) const {
        return (float) numerator / denominator < (float) other.numerator / other.denominator;
    }

    bool Fraction::operator<=(const Fraction &other) const {
        return (float) numerator / denominator <= (float) other.numerator / other.denominator;
    }

    bool Fraction::operator>(const Fraction &other) const {
        return (float) numerator / denominator > (float) other.numerator / other.denominator;
    }

    bool Fraction::operator>=(const Fraction &other) const {
        // Compares two fractions. If the calling fraction is greater than or equal to the other fraction, returns true.
        // Otherwise, returns false.
        return (float) numerator / denominator >= (float) other.numerator / other.denominator;
    }

    bool Fraction::operator==(const Fraction &other) const {
        // Compares two fractions. If the calling fraction is equal to the other fraction, returns true.
        // Otherwise, returns false.
        Fraction temp = other;
        temp.simplify();
        return ((this->numerator * 1000) / this->denominator) == ((other.numerator * 1000) / other.denominator);
    }


    bool operator==(float lhs, const Fraction &rhs) {
        // Compares a float (lhs) and a fraction (rhs). If they are equal, returns true. Otherwise, returns false.
        return Fraction(lhs) == rhs;
    }

    bool operator<(float lhs, const Fraction &rhs) {
        // Compares a float (lhs) and a fraction (rhs). If the float is less than the fraction,
        // returns true. Otherwise, returns false.
        return Fraction(lhs) < rhs;
    }

    bool operator>(float lhs, const Fraction &rhs) {
        // Compares a float (lhs) and a fraction (rhs). If the float is greater than the fraction,
        // returns true. Otherwise, returns false.
        return rhs < lhs;
    }

    bool operator<=(float lhs, const Fraction &rhs) {
        // Compares a float (lhs) and a fraction (rhs). If the float is less than or equal to the fraction,
        // returns true. Otherwise, returns false.
        return !(lhs > rhs);
    }

    bool operator>=(float lhs, const Fraction &rhs) {
        // Compares a float (lhs) and a fraction (rhs). If the float is greater than or equal to the fraction,
        // returns true. Otherwise, returns false.
        return !(lhs < rhs);
    }


    Fraction &Fraction::operator++() {
        // Prefix increment operator. Adds the denominator to the numerator and returns the updated fraction.
        this->numerator += this->denominator;
        return *this;
    }

    Fraction Fraction::operator++(int) {
        // Postfix increment operator. Creates a copy of the fraction, then adds the denominator to the
        // numerator of the original fraction.
        // Returns the copy.
        Fraction temp = *this;
        this->numerator += this->denominator;
        return temp;
    }

    Fraction &Fraction::operator--() {
        // Prefix decrement operator. Subtracts the denominator from the numerator and returns the updated fraction.
        this->numerator -= this->denominator;
        return *this;
    }

    Fraction Fraction::operator--(int) {
        // Postfix decrement operator. Creates a copy of the fraction, then subtracts the denominator from the numerator of the original fraction.
        // Returns the copy.
        Fraction temp = *this;
        this->numerator -= this->denominator;
        return temp;
    }

    void Fraction::simplify() {
        // The purpose of this function is to simplify the fraction to its simplest form.
        // std::gcd(numerator, denominator) computes the greatest common divisor (GCD) of the numerator and denominator.
        // The GCD of two integers is the largest positive integer that divides both numbers without leaving a remainder.
        int g = std::gcd(numerator, denominator);
        // The numerator and denominator are both divided by their GCD.
        // This effectively reduces the fraction to its simplest form.
        numerator /= g;
        denominator /= g;
        // If the denominator is less than 0 (negative), the signs of both the numerator and denominator are flipped.
        // This is a convention in mathematics to always have the denominator as positive.
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }


    // Arithmetic operators involving floats and Fractions
    // These operators allow calculations between floats and Fractions.
    // Addition operator for float and Fraction
    Fraction operator+(float lhs, const Fraction &rhs) {
        // Convert the float to a Fraction
        Fraction lhs_fraction(lhs);
        // Perform the addition using the + operator for two Fractions.
        // Note that this operator is a friend function and not a member function.
        Fraction result = rhs + lhs_fraction;
        return result;
    }

    // Subtraction operator for float and Fraction
    Fraction operator-(float lhs, const Fraction &rhs) {
        // Convert the float to a Fraction
        Fraction lhs_fraction(lhs);
        // Perform the subtraction using the - operator for two Fractions.
        Fraction result = lhs_fraction - rhs;
        return result;
    }

    // Multiplication operator for float and Fraction
    Fraction operator*(float lhs, const Fraction &rhs) {
        // The multiplication is commutative, so we can use the * operator for two Fractions.
        return rhs * lhs;
    }

    // Division operator for float and Fraction
    Fraction operator/(float lhs, const Fraction &rhs) {
        // Check if the denominator is zero (Fraction is zero), if so, throw an exception.
        if (rhs == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }
        // Convert the float to a Fraction and then perform the division using the / operator for two Fractions.
        return Fraction(lhs) / rhs;
    }

    // Stream operators for output and input
    // Output stream operator (<<)
    std::ostream &operator<<(std::ostream &stream, const Fraction &fraction) {
        // Write the fraction to the stream in the format numerator/denominator.
        // getNumerator() and getDenominator() are used to access the private data members of the Fraction.
        stream << fraction.getNumerator() << "/" << fraction.getDenominator();
        return stream;
    }

    // Input stream operator (>>)
    std::istream &operator>>(std::istream &stream, Fraction &fraction) {
        // Read the fraction from the stream.
        // The fraction is expected to be in the format numerator denominator.
        int numerator, denominator;
        if (stream >> numerator >> denominator) {
            // If the input is valid and the denominator is not zero, construct a Fraction with the input values.
            if (denominator == 0) {
                throw std::runtime_error("Division by Zero");
            }
            fraction = Fraction(numerator, denominator);
        } else {
            // If the input is not valid, throw an exception.
            throw std::runtime_error("Invalid input");
        }
        return stream;
    }
}
