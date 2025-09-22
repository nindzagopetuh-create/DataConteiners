#include<iostream>
using namespace std;

void elevator(int floor);
int Factorial(int n);
double Power(double base, int exponent); 
void Fibonacci(int limit, int a = 0, int b = 1); 

void main()
{
    setlocale(LC_ALL, "");

    // ������������ Factorial
    int n;
    cout << "������� ����� ��� ���������� ����������: "; cin >> n;
    cout << "��������� " << n << " = " << Factorial(n) << endl;

    // ������������ Power
    double base;
    int exponent;
    cout << "������� ���������: "; cin >> base;
    cout << "������� ���������� �������: "; cin >> exponent;
    cout << base << " � ������� " << exponent << " = " << Power(base, exponent) << endl;

    // ������������ Fibonacci
    int limit;
    cout << "������� ������ ��� ���� ���������: "; cin >> limit;
    cout << "��� ��������� �� " << limit << ": ";
    Fibonacci(limit);
    cout << endl;

    // ������������ ��� � elevator
    cout << "������� ����� �����: "; cin >> n;
    elevator(n);
}

void elevator(int floor)
{
    if (floor == 0)
    {
        cout << "�� � �������" << endl;
        return;
    }
    cout << "�� �� " << floor << " �����" << endl;
    elevator(floor - 1);
    cout << "�� �� " << floor << " �����" << endl;
}

int Factorial(int n)
{
    if (n <= 1) return 1;       // ������� ������: ��������� 0 � 1 ����� 1
    return n * Factorial(n - 1); // ����������� ������
}

double Power(double base, int exponent)
{
    if (exponent == 0) return 1;                    // ������� ������: ����� ����� � ������� 0 ����� 1
    if (exponent < 0) return 1 / Power(base, -exponent); // ��������� ������������� ��������
    return base * Power(base, exponent - 1);        // ����������� ������
}

void Fibonacci(int limit, int a, int b)
{
    if (a > limit) return;      // ������� ������: �������� �������
    cout << a << " ";           // ������� ������� �����
    Fibonacci(limit, b, a + b); // ����������� ����� �� ���������� �������
}