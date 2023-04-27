#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

namespace ariel {
    class Fraction {
    private:
        int numerator;
        int denominator;

    public:
        Fraction(int numerator, int denominator);
        Fraction(float value);

        int getNumerator() const;
        int getDenominator() const;

        // Arithmetic operators
        Fraction operator+(const Fraction& other) const;
        Fraction operator-(const Fraction& other) const;
        Fraction operator*(const Fraction& other) const;
        Fraction operator/(const Fraction& other) const;

        // Comparison operators
        bool operator<(const Fraction& other) const;
        bool operator<=(const Fraction& other) const;
        bool operator>(const Fraction& other) const;
        bool operator>=(const Fraction& other) const;
        bool operator==(const Fraction& other) const;

        // Increment and decrement operators
        Fraction& operator++(); // Prefix
        Fraction operator++(int); // Postfix
        Fraction& operator--(); // Prefix
        Fraction operator--(int); // Postfix

        // Stream operators
        friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
        friend std::istream& operator>>(std::istream& is, Fraction& f);
    };
}

#endif // FRACTION_HPP
