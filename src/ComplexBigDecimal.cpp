#include "ComplexBigDecimal.h"
#include "UnsignedArith.h"

ComplexBigDecimal::ComplexBigDecimal() {}

ComplexBigDecimal::ComplexBigDecimal(const BigDecimal& real) : re(real), im() {}

ComplexBigDecimal::ComplexBigDecimal(const BigDecimal& real, const BigDecimal& imag) : re(real), im(imag) {}

bool ComplexBigDecimal::isZero() const {
    return re.isZero() && im.isZero();
}

bool ComplexBigDecimal::isReal() const {
    return im.isZero();
}

static std::string padToPrecision(std::string s, int precision) {
    std::size_t dotPos = s.find('.');

    if (dotPos == std::string::npos) {
        s += "." + std::string(precision, '0');
        return s;
    }

    int fracLen = (int)(s.size() - dotPos - 1);
    if (fracLen < precision) {
        s += std::string(precision - fracLen, '0');
    }
    else if (fracLen > precision) {
        s = s.substr(0, dotPos + 1 + precision);
    }

    return s;
}

std::string ComplexBigDecimal::toString() const {
    return toString(1000);
}

std::string ComplexBigDecimal::toString(int precision) const {
    // ========== НОВАЯ ЛОГИКА ВЫВОДА ==========

    // Чисто действительное число (мнимая часть == 0)
    if (im.isZero()) {
        std::string reStr = re.toString(precision);
        return padToPrecision(reStr, precision);
    }

    // Чисто мнимое число (действительная часть == 0)
    if (re.isZero()) {
        std::string imStr = im.toString(precision);
        imStr = padToPrecision(imStr, precision);

        // Убираем ведущий минус, знак обработаем отдельно
        if (im.isNegative && !imStr.empty() && imStr[0] == '-') {
            imStr = imStr.substr(1);
        }

        return (im.isNegative ? "-" : "") + imStr + "i";
    }

    // Обе части ненулевые
    std::string reStr = re.toString(precision);
    std::string imStr = im.toString(precision);

    reStr = padToPrecision(reStr, precision);
    imStr = padToPrecision(imStr, precision);

    // Убираем ведущий минус у мнимой части (знак через " + " / " - ")
    if (im.isNegative && !imStr.empty() && imStr[0] == '-') {
        imStr = imStr.substr(1);
    }

    std::string sign = im.isNegative ? " - " : " + ";
    return reStr + sign + imStr + "i";
}

ComplexBigDecimal addComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b) {
    ComplexBigDecimal result;
    result.re = addBigDecimal(a.re, b.re);
    result.im = addBigDecimal(a.im, b.im);
    return result;
}

ComplexBigDecimal subComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b) {
    ComplexBigDecimal result;
    result.re = subBigDecimal(a.re, b.re);
    result.im = subBigDecimal(a.im, b.im);
    return result;
}

ComplexBigDecimal mulComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b) {
    ComplexBigDecimal result;
    BigDecimal ac = mulBigDecimal(a.re, b.re);
    BigDecimal bd = mulBigDecimal(a.im, b.im);
    BigDecimal ad = mulBigDecimal(a.re, b.im);
    BigDecimal bc = mulBigDecimal(a.im, b.re);

    result.re = subBigDecimal(ac, bd);
    result.im = addBigDecimal(ad, bc);
    return result;
}

ComplexBigDecimal divComplex(const ComplexBigDecimal& a, const ComplexBigDecimal& b, int precision) {
    ComplexBigDecimal result;
    if (b.isZero()) return result;

    ComplexBigDecimal conjB = conjComplex(b);
    ComplexBigDecimal numerator = mulComplex(a, conjB);

    BigDecimal c2 = mulBigDecimal(b.re, b.re);
    BigDecimal d2 = mulBigDecimal(b.im, b.im);
    BigDecimal denom = addBigDecimal(c2, d2);

    result.re = divBigDecimal(numerator.re, denom, precision);
    result.im = divBigDecimal(numerator.im, denom, precision);
    return result;
}

ComplexBigDecimal conjComplex(const ComplexBigDecimal& a) {
    ComplexBigDecimal result = a;
    result.im.isNegative = !result.im.isNegative;
    if (result.im.isZero()) result.im.isNegative = false;
    return result;
}

ComplexBigDecimal absComplex(const ComplexBigDecimal& a, int precision) {
    BigDecimal a2 = mulBigDecimal(a.re, a.re);
    BigDecimal b2 = mulBigDecimal(a.im, a.im);
    BigDecimal sum = addBigDecimal(a2, b2);
    ComplexBigDecimal result;
    result.re = sqrtBigDecimal(sum, precision);
    return result;
}

ComplexBigDecimal sqrtComplex(const ComplexBigDecimal& a, int precision) {
    ComplexBigDecimal result;
    if (a.isZero()) return result;

    if (a.im.isZero()) {
        if (!a.re.isNegative) {
            result.re = sqrtBigDecimal(a.re, precision);
            return result;
        }
        BigDecimal absRe = a.re;
        absRe.isNegative = false;
        result.im = sqrtBigDecimal(absRe, precision);
        return result;
    }

    ComplexBigDecimal mod = absComplex(a, precision);
    BigDecimal sum = addBigDecimal(mod.re, a.re);
    BigDecimal diff = subBigDecimal(mod.re, a.re);

    BigDecimal two;
    two.fromString("2");

    BigDecimal halfSum = divBigDecimal(sum, two, precision);
    BigDecimal halfDiff = divBigDecimal(diff, two, precision);

    result.re = sqrtBigDecimal(halfSum, precision);
    result.im = sqrtBigDecimal(halfDiff, precision);

    if (a.im.isNegative) {
        result.im.isNegative = !result.im.isNegative;
    }

    return result;
}

ComplexBigDecimal powComplex(const ComplexBigDecimal& base, int exp, int precision) {
    if (exp == 0) {
        ComplexBigDecimal one;
        one.re.fromString("1");
        return one;
    }
    if (exp == 1) return base;

    ComplexBigDecimal half = powComplex(base, exp / 2, precision);
    ComplexBigDecimal result = mulComplex(half, half);
    if (exp % 2 == 1) result = mulComplex(result, base);
    return result;
}
