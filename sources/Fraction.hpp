//
// Created by koazg on 4/28/2023.
//

#ifndef FRACTION_B_FRACTION_HPP
#define FRACTION_B_FRACTION_HPP

#include <iostream>

namespace ariel {
    class Fraction {
    private:
        int numerator;   // Stores the numerator of the fraction
        int denominator; // Stores the denominator of the fraction

    public:
        // Default constructor, creates a fraction with numerator 0 and denominator 1
        Fraction();

        // Constructor to initialize fraction with specific numerator and denominator
        Fraction(int numerator, int denominator);

        // Constructor to create a fraction from a floating point number
        Fraction(float value);

        // Returns the numerator of the fraction
        int getNumerator() const;

        // Returns the denominator of the fraction
        int getDenominator() const;

        // Reduces the fraction to its simplest form
        void simplify();

        // Arithmetic operators
        Fraction operator+(const Fraction& other) const; // Addition operator
        Fraction operator-(const Fraction& other) const; // Subtraction operator
        Fraction operator*(const Fraction& other) const; // Multiplication operator
        Fraction operator/(const Fraction& other) const; // Division operator

        // Operator overloads to perform arithmetic with float on the left hand side
        friend Fraction operator+(float lhs, const Fraction& rhs);
        friend Fraction operator-(float lhs, const Fraction& rhs);
        friend Fraction operator*(float lhs, const Fraction& rhs);
        friend Fraction operator/(float lhs, const Fraction& rhs);

        // Comparison operators
        bool operator<(const Fraction& other) const;  // Less than operator
        bool operator<=(const Fraction& other) const; // Less than or equal to operator
        bool operator>(const Fraction& other) const;  // Greater than operator
        bool operator>=(const Fraction& other) const; // Greater than or equal to operator
        bool operator==(const Fraction& other) const; // Equality operator

        // Operator overloads to perform comparison with float on the left hand side
        friend bool operator==(float lhs, const Fraction& rhs);
        friend bool operator<(float lhs, const Fraction& rhs);
        friend bool operator>(float lhs, const Fraction& rhs);
        friend bool operator<=(float lhs, const Fraction& rhs);
        friend bool operator>=(float lhs, const Fraction& rhs);

        // Increment and decrement operators
        Fraction& operator++();    // Prefix increment operator
        Fraction operator++(int);  // Postfix increment operator
        Fraction& operator--();    // Prefix decrement operator
        Fraction operator--(int);  // Postfix decrement operator

        // Stream operators
        friend std::ostream& operator<<(std::ostream& stream, const Fraction& frac); // Output stream operator
        friend std::istream& operator>>(std::istream& stream, Fraction& frac); // Input stream operator
    };
}

#endif //FRACTION_B_FRACTION_HPP

