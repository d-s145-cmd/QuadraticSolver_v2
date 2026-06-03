#include "QuadSolver.h"
#include <iostream>

static void fixNegativeZero(BigDecimal& x) {
    if (x.isZero()) x.isNegative = false;
}

QuadResult QuadSolver::solveLinear(const BigDecimal& b, const BigDecimal& c) const {
    QuadResult res;
    res.equationType = QuadResult::EquationType::LINEAR;

    if (b.isZero()) {
        if (c.isZero()) {
            res.status = QuadResult::Status::INF;
        }
        else {
            res.status = QuadResult::Status::NO_SOLUTION;
        }
        res.rootCount = 0;
        return res;
    }

    BigDecimal x = divBigDecimal(c, b, PRECISION);
    x.isNegative = !x.isNegative;
    fixNegativeZero(x);

    res.status = QuadResult::Status::OK;
    res.rootCount = 1;
    res.root1 = ComplexBigDecimal(x);
    res.hasComplexRoots = false;
    return res;
}

QuadResult QuadSolver::solve(const std::string& sa,
    const std::string& sb,
    const std::string& sc) const {
    QuadResult res;
    BigDecimal a, b, c;

    if (!a.fromString(sa) || !b.fromString(sb) || !c.fromString(sc)) {
        res.status = QuadResult::Status::WRONG;
        res.rootCount = 0;
        return res;
    }

    if (a.isZero()) {
        return solveLinear(b, c);
    }

    res.equationType = QuadResult::EquationType::QUADRATIC;

    BigDecimal four;
    four.fromString("4");
    BigDecimal D = subBigDecimal(mulBigDecimal(b, b),
        mulBigDecimal(four, mulBigDecimal(a, c)));

    int dSign = D.isZero() ? 0 : (D.isNegative ? -1 : 1);

    BigDecimal two;
    two.fromString("2");
    BigDecimal twoA = mulBigDecimal(two, a);

    BigDecimal negB = b;
    if (!negB.isZero()) negB.isNegative = !negB.isNegative;

    if (dSign < 0) {
        res.status = QuadResult::Status::NO_SOLUTION;
        res.hasComplexRoots = true;
        res.rootCount = 2;

        BigDecimal absD = D;
        absD.isNegative = false;
        BigDecimal sqrtAbsD = sqrtBigDecimal(absD, PRECISION);

        ComplexBigDecimal sqrtD;
        sqrtD.im = sqrtAbsD;

        ComplexBigDecimal negBComplex(negB);
        ComplexBigDecimal x1 = divComplex(addComplex(negBComplex, sqrtD), ComplexBigDecimal(twoA), PRECISION);
        ComplexBigDecimal x2 = divComplex(subComplex(negBComplex, sqrtD), ComplexBigDecimal(twoA), PRECISION);

        res.root1 = x1;
        res.root2 = x2;
        return res;
    }

    if (dSign == 0) {
        BigDecimal x = divBigDecimal(negB, twoA, PRECISION);
        fixNegativeZero(x);

        res.status = QuadResult::Status::OK;
        res.rootCount = 1;
        res.root1 = ComplexBigDecimal(x);
        res.hasComplexRoots = false;
        return res;
    }

    BigDecimal sqrtD = sqrtBigDecimal(D, PRECISION);

    BigDecimal x1 = divBigDecimal(addBigDecimal(negB, sqrtD), twoA, PRECISION);
    BigDecimal x2 = divBigDecimal(subBigDecimal(negB, sqrtD), twoA, PRECISION);

    fixNegativeZero(x1);
    fixNegativeZero(x2);

    {
        BigDecimal diff = subBigDecimal(x1, x2);
        if (!diff.isZero() && !diff.isNegative) {
            std::swap(x1, x2);
        }
    }

    res.status = QuadResult::Status::OK;
    res.rootCount = 2;
    res.root1 = ComplexBigDecimal(x1);
    res.root2 = ComplexBigDecimal(x2);
    res.hasComplexRoots = false;
    return res;
}
