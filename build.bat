@echo off
title Quadratic Solver - Build

echo ============================================
echo    Quadratic Solver - Build
echo ============================================
echo.

echo [CHECK] Looking for g++...
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] g++ not found!
    echo.
    echo Install MinGW from: https://winlibs.com/
    echo Then add C:\mingw64\bin to PATH
    echo.
    pause
    exit /b 1
)

echo [OK] g++ found
echo.

echo [CHECK] Checking files...
for %%f in (main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp) do (
    if exist %%f (
        echo   [OK] %%f
    ) else (
        echo   [MISSING] %%f
        goto :error_files
    )
)
echo.

set SOURCES=main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp
set OUTPUT=QuadraticSolver.exe

echo [BUILD] Compiling...
g++ -std=c++17 -O2 -o %OUTPUT% %SOURCES%

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build failed!
    pause
    exit /b 1
)

echo.
echo ============================================
echo [SUCCESS] Build complete!
echo Output: %CD%\%OUTPUT%
echo ============================================
echo.
pause
exit /b 0

:error_files
echo.
echo [ERROR] Missing source files!
echo Current folder: %CD%
echo.
pause
exit /b 1
