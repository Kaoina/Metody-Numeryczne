#include <iostream>
#include <cmath>
using namespace std;

double rectagle_integral (double a, double b, int n, double (*f)(double)) {
    double s = (b - a) / n;
    //cout << s;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += f ((a + (i * s)) + (0.5 * s));
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
        sum += ((x_i1 - x_i) / 2) * (f (x_i) + f (x_i1));
    }
    return sum;
}
double simpson_integral (double a, double b, double n, double (*f)(double)) {
    double s = (b - a) / n;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double x_i = a + (i * s);
        double x_i1 = a + ((i + 1) * s);
        sum += ((x_i1 - x_i) / 6) * (f (x_i) + 4 * f ((x_i + x_i1) / 2) + f (x_i1));
    }
    return sum;
}

double lagrange_integral (double a, double b, double n, double (*f)(double), double* waga, double* wezel) {
    double sum = 0;
    double iloraz = ((b - a) / 2);
    for (int i = 0; i < n; i++) {
        double t_i;
        t_i = ((a + b) / 2) + iloraz * wezel[i];
        sum += (waga[i] * f (t_i));
    }
    return iloraz * sum;
}

double function (double x) {
    double sum = (x * x) + (2 * x) + 5;
    return sum;
}
int main ()
{
    cout << "Wynik calki Lagrange'a: " << endl;
    double a, b;
    a = a = 0.5;
    b = 2.5;

    //Dla dwóch węzłów
    double* waga2 = new double[2];
    double* wezel2 = new double[2];
    double n = 2;
    wezel2[0] = -1.0 * (sqrt (3) / 3);
    wezel2[1] = sqrt (3) / 3;
    waga2[0] = 1;
    waga2[1] = 1;
    cout << "\nsinus" << endl;
    double integ2 = lagrange_integral (a, b, n, sin, waga2, wezel2);
    cout << "Wartosc dla " << n << " wezlow: " << integ2 << endl;

    //Dla trzech węzłów
    double* waga3 = new double[3];
    double* wezel3 = new double[3];
    n = 3;
    wezel3[0] = -1 * sqrt (3.0 / 5.0);
    wezel3[1] = 0;
    wezel3[2] = sqrt (3.0 / 5.0);

    waga3[0] = 5.0 / 9.0;
    waga3[1] = 8.0 / 9.0;
    waga3[2] = 5.0 / 9.0;
    double integ3 = lagrange_integral (a, b, n, sin, waga3, wezel3);
    cout << "Wartosc dla " << n << " wezlow: " << integ3 << endl;

    //Dla czterech węzłów
    n = 4;
    double* waga4 = new double[4];
    double* wezel4 = new double[4];
    wezel4[0] = -1.0 * (1.0 / 35.0) * sqrt (525.0 + 70.0 * sqrt (30.0));
    wezel4[1] = -1.0 * (1.0 / 35.0) * sqrt (525.0 - 70 * sqrt (30.0));
    wezel4[2] = (1.0 / 35.0) * sqrt (525.0 - 70.0 * sqrt (30.0));
    wezel4[3] = (1.0 / 35.0) * sqrt (525.0 + 70.0 * sqrt (30.0));

    waga4[0] = (1.0 / 36.0) * (18.0 - sqrt (30.0));
    waga4[1] = (1.0 / 36.0) * (18.0 + sqrt (30.0));
    waga4[2] = (1.0 / 36.0) * (18.0 + sqrt (30.0));
    waga4[3] = (1.0 / 36.0) * (18.0 - sqrt (30.0));

    double integ4 = lagrange_integral (a, b, n, sin, waga4, wezel4);
    cout << "Wartosc dla " << n << " wezlow: " << integ4 << endl;


    cout << "\nkwadratowa" << endl;;
    n = 2;
    b = 5;
    integ2 = lagrange_integral (a, b, n, function, waga2, wezel2);
    cout << "Wartosc dla " << n << " wezlow: " << integ2 << endl;
    n = 3;
    integ3 = lagrange_integral (a, b, n, function, waga3, wezel3);
    cout << "Wartosc dla " << n << " wezlow: " << integ3 << endl;
    n = 4;
    integ4 = lagrange_integral (a, b, n, function, waga4, wezel4);
    cout << "Wartosc dla " << n << " wezlow: " << integ4 << endl;


    cout << "\nexp" << endl;
    n = 2;
    integ2 = lagrange_integral (a, b, n, exp, waga2, wezel2);
    cout << "Wartosc dla " << n << " wezlow: " << integ2 << endl;
    n = 3;
    integ3 = lagrange_integral (a, b, n, exp, waga3, wezel3);
    cout << "Wartosc dla " << n << " wezlow: " << integ3 << endl;
    n = 4;
    integ4 = lagrange_integral (a, b, n, exp, waga4, wezel4);
    cout << "Wartosc dla " << n << " wezlow: " << integ4 << endl;


    double integral;
    a = 0.5;
    b = 2.5;
    n = 20;
    cout << "\n\nZadanie zajecia lab07" << endl;
    cout << "\nPrzedzial a = " << a << ", b = " << b << ", n = " << n << endl;
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
    n = 20;
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