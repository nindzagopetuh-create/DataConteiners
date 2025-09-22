#include<iostream>
using namespace std;

void elevator(int floor);
int Factorial(int n);
double Power(double base, int exponent); 
void Fibonacci(int limit, int a = 0, int b = 1); 

void main()
{
    setlocale(LC_ALL, "");

    // Тестирование Factorial
    int n;
    cout << "Введите число для вычисления факториала: "; cin >> n;
    cout << "Факториал " << n << " = " << Factorial(n) << endl;

    // Тестирование Power
    double base;
    int exponent;
    cout << "Введите основание: "; cin >> base;
    cout << "Введите показатель степени: "; cin >> exponent;
    cout << base << " в степени " << exponent << " = " << Power(base, exponent) << endl;

    // Тестирование Fibonacci
    int limit;
    cout << "Введите предел для ряда Фибоначчи: "; cin >> limit;
    cout << "Ряд Фибоначчи до " << limit << ": ";
    Fibonacci(limit);
    cout << endl;

    // Оригинальный код с elevator
    cout << "Введите номер этажа: "; cin >> n;
    elevator(n);
}

void elevator(int floor)
{
    if (floor == 0)
    {
        cout << "Вы в подвале" << endl;
        return;
    }
    cout << "Вы на " << floor << " этаже" << endl;
    elevator(floor - 1);
    cout << "Вы на " << floor << " этаже" << endl;
}

int Factorial(int n)
{
    if (n <= 1) return 1;       // базовый случай: факториал 0 и 1 равен 1
    return n * Factorial(n - 1); // рекурсивный случай
}

double Power(double base, int exponent)
{
    if (exponent == 0) return 1;                    // базовый случай: любое число в степени 0 равно 1
    if (exponent < 0) return 1 / Power(base, -exponent); // обработка отрицательных степеней
    return base * Power(base, exponent - 1);        // рекурсивный случай
}

void Fibonacci(int limit, int a, int b)
{
    if (a > limit) return;      // базовый случай: достигли предела
    cout << a << " ";           // выводим текущее число
    Fibonacci(limit, b, a + b); // рекурсивный вызов со следующими числами
}