# QuadraticSolver_v2

Решает квадратное уравнение **ax² + bx + c = 0** с произвольной точностью. Длинная арифметика реализована с нуля — сторонние библиотеки не используются.

Поддерживает:
- действительные и **комплексные** корни
- числа в научной нотации (`1.5e10`, `-3.7e-42`)
- вычисление **экспоненты**

---


## Структура проекта

- `main.cpp` — точка входа
- `QuadSolver.cpp/.h` — решение уравнения
- `BigDecimal.cpp/.h` — длинная арифметика
- `ComplexBigDecimal.cpp/.h` — комплексная арифметика
- `UnsignedArith.cpp/.h` — беззнаковые операции
- `README.md`

## Сборка

### Windows (MinGW)

Установите [MinGW-w64](https://winlibs.com/), добавьте `C:\mingw64\bin` в PATH.

Затем в папке с проектом:
```cmd
build.bat
Или вручную:
cmd
g++ -std=c++17 -O2 -o QuadraticSolver.exe main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp
Linux / macOS
bash
chmod +x build.sh
./build.sh
Или вручную:
bash
g++ -std=c++17 -O2 -o QuadraticSolver main.cpp QuadSolver.cpp BigDecimal.cpp UnsignedArith.cpp ComplexBigDecimal.cpp

Использование
Интерактивный режим:
bash
./QuadraticSolver          # Linux/macOS
QuadraticSolver.exe        # Windows

Введите три коэффициента:
plain
Enter a b c (or 'exit' to quit): 1 -3 2
Или перенаправьте ввод из файла:
bash
./QuadraticSolver < tests.txt

Формат выходных данных
Table
Статус	Значение
OK	есть решения, далее — количество и сами корни
INF	бесконечно много решений
NO SOLUTION	решений нет
WRONG	неверный ввод
Комплексные корни выводятся как a + bi или a - bi. Если мнимая часть равна 0, выводится только действительное число.
Примеры
Два действительных корня:
plain
Enter a b c: 1 -3 2
OK
2
1
2
Комплексные корни:
plain
Enter a b c: 1 0 1
OK
2
i
-i
Комплексные с действительной частью:
plain
Enter a b c: 1 2 5
OK
2
-1 + 2i
-1 - 2i
Линейное уравнение:
plain
Enter a b c: 0 2 -6
OK
1
3
Бесконечно много решений:
plain
Enter a b c: 0 0 0
INF
Нет решений:
plain
Enter a b c: 0 0 5
NO SOLUTION
