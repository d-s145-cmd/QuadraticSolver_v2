@echo off
chcp 65001 >nul
title Quadratic Solver - Build

echo ============================================
echo    Quadratic Solver - Сборка проекта
echo ============================================
echo.


where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ОШИБКА] Компилятор g++ не найден!
    echo Убедитесь, что MinGW установлен и добавлен в PATH.
    echo.
    pause
    exit /b 1
)


set SOURCES=main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp
set OUTPUT=QuadraticSolver.exe
set FLAGS=-std=c++17 -O2 -Wall -Wextra

echo [INFO] Компилятор: g++
echo [INFO] Флаги: %FLAGS%
echo [INFO] Исходники: %SOURCES%
echo [INFO] Выходной файл: %OUTPUT%
echo.


echo [BUILD] Компиляция...
g++ %FLAGS% -o %OUTPUT% %SOURCES%

if %errorlevel% neq 0 (
    echo.
    echo [ОШИБКА] Сборка завершилась с ошибками!
    pause
    exit /b 1
)

echo.
echo ============================================
echo [УСПЕХ] Сборка завершена!
echo [INFO] Исполняемый файл: %OUTPUT%
echo ============================================
echo.
echo Запуск: %OUTPUT%
echo.

pause
