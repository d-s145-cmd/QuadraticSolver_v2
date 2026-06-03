#pragma once
#include <string>

struct BigDecimal {
    std::string digits;
    std::string exponent10;
    bool isNegative;

    BigDecimal();
    bool isZero() const;
    void normalize();
    bool fromString(const std::string& s);
    std::string toString() const;
    std::string toString(int maxDigits) const;
    std::string toScientific() const;
    std::string toScientific(int precision) const;
};

std::string normalizeString(std::string x);
int compareSignedStrings(std::string x, std::string y);
std::string addSignedStrings(std::string x, std::string y);
std::string subSignedStrings(std::string x, std::string y);

BigDecimal addBigDecimal(const BigDecimal& a, const BigDecimal& b);
BigDecimal subBigDecimal(const BigDecimal& a, const BigDecimal& b);
BigDecimal mulBigDecimal(const BigDecimal& a, const BigDecimal& b);
BigDecimal divBigDecimal(const BigDecimal& a, const BigDecimal& b, int precision = 1000);
BigDecimal sqrtBigDecimal(const BigDecimal& a, int precision = 1000);
BigDecimal absBigDecimal(const BigDecimal& a);
