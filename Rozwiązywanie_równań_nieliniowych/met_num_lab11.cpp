#include <iostream>
#include <cmath>

using namespace std;

double f (double x) {
    return (-1*(pow (x, 3)) + (10 * x) + 5); //FUNCKJA Z INSTRUKCJI
    //return ((pow (x, 4)) + (3 * pow(x, 2)) + (2 * x) + 1);//FUNCKJA WŁASNA
}

double f_pochodna (double x) {
    return (( -1 * 3 * pow (x, 2)) + 10);//POCHODNA Z INSTRUKCJI
    //return ((4 * pow (x, 3)) + (6 * x) + 2);//POCHODNA WŁASNA
}

void metoda_stycznych (double (*f)(double), double (*f_poch)(double), double x0, int iterations) {
    double x = x0;
    cout << "Iteracja 0" << ": x = " << x0 << ", f(x) = " << f (x0) << endl;
    for (int i = 0; i < iterations; ++i) {
        double x_next = x - (f(x) / f_poch(x));
        cout << "Iteracja " << i + 1 << ": x = " << x_next << ", f(x) = " << f (x_next) << endl;
        x = x_next;
    }
}

void metoda_siecznych (double (*f)(double), double x_prev, double x0, int iterations) {
    cout << "Iteracja 0" << ": x = " << x0 << ", f(x) = " << f (x0) << endl;
    for (int i = 0; i < iterations; ++i) {
        double x_next = x0 - (f(x0) * ((x0 - x_prev) / (f(x0) - f(x_prev))));
        cout << "Iteracja " << i + 1 << ": x = " << x_next << ", f(x) = " << f (x_next) << endl;
        x_prev = x0;
        x0 = x_next;
    }
}

int main () {
    double x0 = 6;
    int iterations = 10; //ZMIANA ITERACJI

    cout << "Metoda stycznych:" << endl;
    metoda_stycznych (f, f_pochodna, x0, iterations);

    cout << "\nMetoda siecznych:" << endl;
    double x_prev = x0 - 0.1;
    metoda_siecznych (f, x_prev, x0, iterations);

    return 0;
}
