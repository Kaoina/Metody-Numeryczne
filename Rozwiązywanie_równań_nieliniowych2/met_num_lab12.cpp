#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f (double x) {
    return cos(pow(x, 3) - 2 * x);
}

double metoda_bisekcji (double a, double b, double blad) {
    double x_0;

    x_0 = ((a + b) / 2);

    while(abs (f (x_0)) > blad) {
        x_0 = ((a + b) / 2);
        cout << "x0: " << x_0 << "  f(x0): " << f (x_0) << endl;
        if ((f (a) * f (x_0)) < 0) {
            b = x_0;
        }
        else {
            a = x_0;
        }
    }

    return x_0;
}


double metoda_fal_lin (double a, double b, double tol) {
    double x1 = a - (f (a) * (b - a)) / (f (b) - f (a));    
    while (abs (f (x1)) > tol) {
        x1 = a - (f (a) * (b - a)) / (f (b) - f (a));
        if (f (x1) * f (a) < 0) {
            b = x1;
        }
        else
        {
            a = x1;
        }
        cout << "Iteracja: x = " << x1 << ", f(x) = " << f(x1) << endl;
    }
    return x1;
}

int main () {
    double a = 0.0;
    double b = 2.0;
    double blad = 0.01;

    //Metoda Bisekcji
    cout << "f(x) = cos(x^3 - 2x) = 0" << endl;
    cout << "Metoda Bisekcji: " << endl;
    cout << metoda_bisekcji (a, b, blad);

    cout << endl;

    //Metoda fałszywej linii
    cout << "Metoda falszywej linii: " << endl;
    cout << metoda_fal_lin (a, b, blad) << endl;
   

    return 0;
}