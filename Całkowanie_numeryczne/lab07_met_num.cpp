ï»¿#include <iostream>
#include <cmath>
using namespace std;

double rectagle_integral(double a, double b, int n, double (*f)(double)) {
    double s = (b - a) / n;
    //cout << s;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += f((a + (i*s)) + (0.5 * s));
    } 
    sum *= s;
    return sum;
}
double trapezium_integral (double a, double b, double n, double (*f)(double)) {
    double s = (b - a) / n;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double x_i = a + (i * s);
        double x_i1 = a + ((i + 1) * s);
        sum += ((x_i1 - x_i )/ 2) * (f (x_i) + f(x_i1));
    }
    return sum;
}
double simpson_integral (double a, double b, double n, double (*f)(double)) {
    double s = (b - a) / n;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double x_i = a + (i * s);
        double x_i1 = a + ((i + 1) * s);
        sum += ((x_i1 - x_i) / 6) * (f(x_i) + 4 * f((x_i + x_i1)/2) + f(x_i1));
    }
    return sum;
}

double function (double x) {
    double sum = (x * x) + (2 * x) + 5;
    return sum;
}
int main()
{
    double a, b, integral;
    int n;

    a = 0.5;
    b = 2.5;
    n = 4;
    cout << "Przedzial a = " << a << ", b = " << b << ", n = " << n << endl;
    cout << "Calkowanie funckji sinus" << endl;

    //przyklad 1
    integral = rectagle_integral (a, b, n, sin);
    cout << "Wynik calki prostokaty: " << integral << endl;

    integral = trapezium_integral (a, b, n, sin);
    cout << "Wynik calki trapezy: " << integral << endl;

    integral = simpson_integral (a, b, n, sin);
    cout << "Wynik calki simpson: " << integral << endl;

    //przyklad 2
    a = 0.5;
    b = 5;
    n = 4;
    cout << "\nPrzedzial a = " << a << ", b = " << b << ", n = " << n << endl;

    cout << "\nCalkowanie funckji kwadratowej" << endl;
    integral = rectagle_integral (a, b, n, function);
    cout << "Wynik calki prostokaty: " << integral << endl;

    integral = trapezium_integral (a, b, n, function);
    cout << "Wynik calki trapezy: " << integral << endl;

    integral = simpson_integral (a, b, n, function);
    cout << "Wynik calki simpson: " << integral << endl;

    //przyklad 3
    cout << "\nCalkowanie funckji exp" << endl;
    integral = rectagle_integral (a, b, n, exp);
    cout << "Wynik calki prostokaty: " << integral << endl;

    integral = trapezium_integral (a, b, n, exp);
    cout << "Wynik calki trapezy: " << integral << endl;

    integral = simpson_integral (a, b, n, exp);
    cout << "Wynik calki simpson: " << integral << endl;
    return 0;
}
