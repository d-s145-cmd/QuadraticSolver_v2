@echo off
title Quadratic Solver - Build

echo ============================================
echo    Quadratic Solver - Build
echo ============================================
echo.

:: Check g++
echo [CHECK] Looking for g++...
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] g++ not found!
    echo.
    echo How to fix:
    echo   1. Download MinGW from: https://winlibs.com/
    echo   2. Extract to C:\mingw64
    echo   3. Add C:\mingw64\bin to PATH
    echo.
    pause
    exit /b 1
)

echo [OK] g++ found
g++ --version 2>nul | findstr "g++"
echo.

:: Check source files
echo [CHECK] Checking source files...
set MISSING=0

for %%f in (main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp) do (
    if exist %%f (
        echo   [OK] %%f
    ) else (
        echo   [MISSING] %%f
        set MISSING=1
    )
)

if %MISSING%==1 (
    echo.
    echo [ERROR] Some source files are missing!
    echo Make sure build.bat is in the same folder as .cpp files.
    echo.
    echo Current folder: %CD%
    echo Files found:
    dir /b *.cpp 2>nul || echo   (none)
    echo.
    pause
    exit /b 1
)

echo.

:: Build
set SOURCES=main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp
set OUTPUT=QuadraticSolver.exe
set FLAGS=-std=c++17 -O2 -Wall -Wextra

echo [BUILD] Compiling...
echo   g++ %FLAGS% -o %OUTPUT% %SOURCES%
echo.

g++ %FLAGS% -o %OUTPUT% %SOURCES% 2>&1

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build failed! (code: %errorlevel%)
    echo.
    pause
    exit /b 1
)

echo.
echo ============================================
echo [SUCCESS] Build complete!
echo [INFO] Output: %CD%\%OUTPUT%
echo ============================================
echo.

if exist %OUTPUT% (
    echo [OK] File created successfully.
    echo.
    echo To run:
    echo   %OUTPUT%
    echo.
) else (
    echo [WARN] Output file not found!
)

pause
