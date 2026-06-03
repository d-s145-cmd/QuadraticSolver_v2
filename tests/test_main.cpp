#include <iostream>
#include <string>
#include "UnsignedArith.h"
#include "BigDecimal.h"
#include "ComplexBigDecimal.h"
#include "QuadSolver.h"

int testsPassed = 0;
int testsFailed = 0;

void check(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << "\n";
        testsPassed++;
    }
    else {
        std::cout << "[FAIL] " << testName << "\n";
        testsFailed++;
    }
}

void testUnsignedArith() {
    std::cout << "\n=== UnsignedArith Tests ===\n";
    check(compareStrings("123", "123") == 0, "Compare equal");
    check(compareStrings("123", "45") == 1, "Compare greater");
    check(compareStrings("45", "123") == -1, "Compare less");
    check(compareStrings("00123", "123") == 0, "Compare with leading zeros");
    check(add("123", "456") == "579", "Add simple");
    check(add("999", "1") == "1000", "Add with carry");
    check(add("0", "0") == "0", "Add zeros");
    check(sub("456", "123") == "333", "Sub simple");
    check(sub("1000", "1") == "999", "Sub with borrow");
    check(mul("12", "12") == "144", "Mul simple");
    check(mul("123", "0") == "0", "Mul by zero");
    check(mul("999", "999") == "998001", "Mul large");
    auto r1 = divmod("100", "3");
    check(r1.first == "33" && r1.second == "1", "Divmod 100/3");
    auto r2 = divmod("17", "5");
    check(r2.first == "3" && r2.second == "2", "Divmod 17/5");
}

void testBigDecimal() {
    std::cout << "\n=== BigDecimal Tests ===\n";
    BigDecimal bd1;
    check(bd1.fromString("123") && bd1.toString() == "123", "Parse integer");
    BigDecimal bd2;
    check(bd2.fromString("123.456") && bd2.toString() == "123.456", "Parse decimal");
    BigDecimal bd3;
    check(bd3.fromString("1.23e+10") && bd3.toString() == "12300000000", "Parse scientific e");
    BigDecimal bd4;
    check(bd4.fromString("1.23E+10") && bd4.toString() == "12300000000", "Parse scientific E");
    BigDecimal bd5;
    check(bd5.fromString("1.23e-5") && bd5.toString() == "0.0000123", "Parse negative exp");
    BigDecimal bd6;
    check(bd6.fromString("-456") && bd6.toString() == "-456", "Parse negative");
    BigDecimal bd7;
    check(!bd7.fromString("abc"), "Reject invalid abc");
    BigDecimal bd8;
    check(!bd8.fromString("12.34.56"), "Reject double dot");

    BigDecimal a, b;
    a.fromString("1.5"); b.fromString("2.5");
    check(addBigDecimal(a, b).toString() == "4", "Add 1.5 + 2.5");

    BigDecimal d, e;
    d.fromString("5"); e.fromString("3");
    check(subBigDecimal(d, e).toString() == "2", "Sub 5 - 3");

    BigDecimal g, h;
    g.fromString("2.5"); h.fromString("4");
    check(mulBigDecimal(g, h).toString() == "10", "Mul 2.5 * 4");

    BigDecimal j, k;
    j.fromString("10"); k.fromString("3");
    check(divBigDecimal(j, k, 10).toString() == "3.3333333333", "Div 10/3");

    BigDecimal m;
    m.fromString("2");
    check(sqrtBigDecimal(m, 10).toString() == "1.4142135623", "Sqrt 2");

    BigDecimal zero;
    check(zero.isZero(), "Zero is zero");
}

void testQuadSolver() {
    std::cout << "\n=== QuadSolver Tests ===\n";
    QuadSolver solver;

    auto r1 = solver.solve("1", "-5", "6");
    check(r1.status == QuadResult::Status::OK && r1.rootCount == 2, "Two real roots");

    auto r2 = solver.solve("1", "-2", "1");
    check(r2.status == QuadResult::Status::OK && r2.rootCount == 1, "One real root");

    auto r3 = solver.solve("1", "0", "1");
    check(r3.status == QuadResult::Status::NO_SOLUTION && r3.hasComplexRoots, "Complex roots");

    auto r4 = solver.solve("0", "2", "-4");
    check(r4.status == QuadResult::Status::OK && r4.rootCount == 1, "Linear equation");

    auto r5 = solver.solve("0", "0", "0");
    check(r5.status == QuadResult::Status::INF, "Infinite solutions");

    auto r6 = solver.solve("0", "0", "5");
    check(r6.status == QuadResult::Status::NO_SOLUTION, "No solution");

    auto r7 = solver.solve("abc", "1", "2");
    check(r7.status == QuadResult::Status::WRONG, "Wrong input");

    auto r8 = solver.solve("1", "-6.626E-34", "1");
    check(r8.status == QuadResult::Status::NO_SOLUTION && r8.hasComplexRoots, "Scientific notation");

    auto r9 = solver.solve("1", "-1", "-1");
    check(r9.status == QuadResult::Status::OK && r9.rootCount == 2, "Golden ratio");

    auto r10 = solver.solve("1E+100", "0", "-1E+100");
    check(r10.status == QuadResult::Status::OK && r10.rootCount == 2, "Large numbers");

    auto r11 = solver.solve("1E-100", "0", "-1E-100");
    check(r11.status == QuadResult::Status::OK && r11.rootCount == 2, "Small numbers");
}

void testPrecision() {
    std::cout << "\n=== Precision Tests ===\n";
    BigDecimal a;
    a.fromString("2");
    BigDecimal root = sqrtBigDecimal(a, 1000);
    std::string result = root.toString(50);
    check(result.substr(0, 52) == "1.41421356237309504880168872420969807856967187537694",
        "Sqrt(2) 50 digits precision");
    std::cout << "  Sqrt(2) = " << result.substr(0, 60) << "...\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "  QuadSolver Test Suite\n";
    std::cout << "========================================\n";

    testUnsignedArith();
    testBigDecimal();
    testQuadSolver();
    testPrecision();

    std::cout << "\n========================================\n";
    std::cout << "  Results: " << testsPassed << " passed, " << testsFailed << " failed\n";
    std::cout << "========================================\n";

    return testsFailed > 0 ? 1 : 0;
}
