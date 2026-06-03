#pragma once
#include "BigDecimal.h"
#include "ComplexBigDecimal.h"
#include <string>

struct QuadResult {
    enum class Status {
        OK,
        INF,
        WRONG,
        NO_SOLUTION
    };

    enum class EquationType {
        QUADRATIC,
        LINEAR
    };

    Status status;
    EquationType equationType;
    int rootCount;
    ComplexBigDecimal root1;
    ComplexBigDecimal root2;
    bool hasComplexRoots;
};

class QuadSolver {
public:
    QuadResult solve(const std::string& sa,
        const std::string& sb,
        const std::string& sc) const;

private:
    static constexpr int PRECISION = 1000;

    QuadResult solveLinear(const BigDecimal& b, const BigDecimal& c) const;
};
