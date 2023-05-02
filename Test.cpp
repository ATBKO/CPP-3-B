//
// Created by koazg on 4/28/2023.
//
#include "doctest.h"
#include <stdexcept>
#include "sources/Fraction.hpp"
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <sstream>
using namespace ariel;
using namespace std;


TEST_CASE("initialization & Getters return expected values") {
    Fraction c(2, 3);
    CHECK(((c.getNumerator() == 2) && (c.getDenominator() == 3)));
    Fraction d(0.6667);
    CHECK(((d.getNumerator() == 667) && (d.getDenominator() == 1000)));
}

TEST_CASE("Fraction addition test") {
    Fraction a(1, 3), b(1, 2);
    Fraction c = a + b; // 1/3 + 1/2 = 5/6
    CHECK(((c.getNumerator() == 5) && (c.getDenominator() == 6)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
}

TEST_CASE("Fraction subtraction test") {
    Fraction a(1, 2), b(1, 4);
    Fraction c = b - a; // 1/4 - 1/2 = -1/4
    CHECK(((c.getNumerator() == -1) && (c.getDenominator() == 4)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
}

TEST_CASE("Fraction multiplication test") {
    Fraction a(1, 2), b(2, 3);
    Fraction c = a * b; // 1/2 * 2/3 = 1/3
    CHECK(((c.getNumerator() == 1) && (c.getDenominator() == 3)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
}

TEST_CASE("Fraction division test") {
    Fraction a(1, 2), b(2, 3);
    Fraction c = a / b; // 1/2 / 2/3 = 1/2 * 3/2 = 3/4
    CHECK(((c.getNumerator() == 3) && (c.getDenominator() == 4)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
}

TEST_CASE("comparison tests") {
    Fraction a(1, 2);
    Fraction b(2, 3);

    CHECK(b > a);
    CHECK_FALSE(b <= a);
    CHECK(b >= a);
    CHECK_FALSE(b < a);
    CHECK_FALSE(b == a);
}

TEST_CASE("increment and decrement operators tests") {
    Fraction a(3, 4);

    // Prefix increment
    Fraction b = ++a;
    CHECK(a.getNumerator() == 7);
    CHECK(a.getDenominator() == 4);
    CHECK(b.getNumerator() == 7);
    CHECK(b.getDenominator() == 4);

    a = Fraction(3, 4); // Reset

    // Postfix decrement
    Fraction c = a--;
    CHECK(a.getNumerator() == -1);
    CHECK(a.getDenominator() == 4);
    CHECK(c.getNumerator() == 3);
    CHECK(c.getDenominator() == 4);
}


TEST_CASE("Fraction object initialization with negative values") {
    Fraction a(-1, 2);
    CHECK(((a.getNumerator() == -1) && (a.getDenominator() == 2)));

    Fraction b(1, -2);
    CHECK(((b.getNumerator() == -1) && (b.getDenominator() == 2)));

    Fraction c(-1, -2);
    CHECK(((c.getNumerator() == 1) && (c.getDenominator() == 2)));

    CHECK_THROWS(Fraction(-1,0));
}


TEST_CASE("Fraction != comparison operator") {
    Fraction a(1, 2);
    Fraction b(1, 4);
    Fraction c(2, 4);
    Fraction d(1, 4);

    CHECK(a != b);
    CHECK_FALSE(a != c);
    CHECK_FALSE(b != d);
}


TEST_CASE("negative fractions") {
    CHECK_NOTHROW(Fraction f(-2, 3););
    CHECK(Fraction(-2, 3) == Fraction(-2,3));
    CHECK_NOTHROW(Fraction f(2, -3););
    CHECK(Fraction(2, -3) == Fraction(-2,3));
    CHECK_NOTHROW(Fraction f(-2, -3););
    CHECK(Fraction(-2, -3) == Fraction(2,3));
    CHECK_NOTHROW(Fraction f(-0.5););
    CHECK(Fraction(-0.5) == Fraction(-5,10));
}


TEST_CASE("Division by zero") {
    Fraction a(5, 6);
    CHECK_THROWS(a / 0);
}

TEST_CASE("Prefix and postfix") {
    Fraction a(8, 7);
    Fraction b = ++a;
    CHECK(a.getNumerator() == 10);
    CHECK(a.getDenominator() == 7);
    CHECK(b.getNumerator() == 10);
    CHECK(b.getDenominator() == 7);

    a = Fraction(1, 2);
    Fraction c = a++;
    CHECK(a.getNumerator() == 3);
    CHECK(a.getDenominator() == 2);
    CHECK(c.getNumerator() == 1);
    CHECK(c.getDenominator() == 2);
}

TEST_CASE("Output stream") {
    std::stringstream temp;

    Fraction a{3, 4};
    temp << a;
    CHECK(temp.str() == "3/4");

    temp.str("");
    Fraction b{-7, 9};
    temp << b;
    CHECK(temp.str() == "-7/9");

    temp.str("");
    Fraction c{3, -4};
    temp << c;
    CHECK(temp.str() == "-3/4");

    temp.str("");
    Fraction d{30, 60};
    temp << d;
    CHECK(temp.str() == "1/2");
}





