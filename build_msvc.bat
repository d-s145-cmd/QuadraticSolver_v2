@echo off
chcp 65001 >nul
title Quadratic Solver - Build (MSVC)

echo ============================================
echo    Quadratic Solver - Сборка (MSVC)
echo ============================================
echo.


where cl >nul 2>nul
if %errorlevel% neq 0 (
    echo [ОШИБКА] Компилятор cl.exe не найден!
    echo Запустите из "Developer Command Prompt for VS".
    pause
    exit /b 1
)

set SOURCES=main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp
set OUTPUT=QuadraticSolver.exe
set FLAGS=/std:c++17 /O2 /W4 /EHsc

echo [INFO] Компилятор: MSVC (cl.exe)
echo [INFO] Флаги: %FLAGS%
echo.

cl %FLAGS% /Fe:%OUTPUT% %SOURCES%

if %errorlevel% neq 0 (
    echo [ОШИБКА] Сборка завершилась с ошибками!
    pause
    exit /b 1
)

echo.
echo [УСПЕХ] Сборка завершена: %OUTPUT%
pause
