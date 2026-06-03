#pragma once
#include "BigDecimal.h"
#include <string>

struct ComplexBigDecimal {
    BigDecimal re;
    BigDecimal im;

    ComplexBigDecimal();
    ComplexBigDecimal(const BigDecimal& real);
    ComplexBigDecimal(const BigDecimal& real, const BigDecimal& imag);

    bool isZero() const;
    bool isReal() const;
    std::string toString() const;
    std::string toString(int precision) const;
};

ComplexBigDecimal addComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b);
ComplexBigDecimal subComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b);
ComplexBigDecimal mulComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b);
ComplexBigDecimal divComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b, int precision = 1000);
ComplexBigDecimal conjComplex(const ComplexBigDecimal& a);
ComplexBigDecimal absComplex(const ComplexBigDecimal& a, int precision = 1000);
ComplexBigDecimal sqrtComplex(const ComplexBigDecimal& a, int precision = 1000);
ComplexBigDecimal powComplex(const ComplexBigDecimal& base, int exp, int precision = 1000);
