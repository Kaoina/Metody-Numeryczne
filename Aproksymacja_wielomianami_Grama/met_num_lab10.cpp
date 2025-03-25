ï»¿#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

int silnia(int n) {
    if (n == 0) {
        return 1;
    } else {
        int wynik = 1;
        for (int i = n; i > 1; i--) {
            wynik *= i;
        }
        return wynik;
    }
}

double dwumian_newtona(double n, double k) {
    if (k > n) return 0;
    double wynik = silnia(static_cast<int>(n)) / (silnia(static_cast<int>(k)) * silnia(static_cast<int>(n - k)));
    return wynik;
}

double wiel_czyn(double x, double n) {
    double wynik = 1;
    for (int j = 0; j < n; j++) {
        wynik *= (x - j);
    }
    return wynik;
}

double wiel_grama(double n, double q, double k) {
    double suma = 0;
    for (int s = 0; s <= k; s++) {
        suma += (pow(-1, s) * dwumian_newtona(k, s) * dwumian_newtona(k + s, s) * (wiel_czyn(q, s) / wiel_czyn(n, s)));
    }
    return suma;
}

void wyswietl_tablice(double* tab, int n) {
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;
}

void oblicz_y_m (int n, double* tab_x, double* y_m, double h, double* c_k, double* s_k, int stop_wielo) {
    for (int m = 0; m < n; m++) {
        double q = ((tab_x[m] - tab_x[0]) / h);

        for (int k = 0; k <= stop_wielo; k++) {
            y_m[m] += ((c_k[k] / s_k[k]) * wiel_grama (n - 1, q, k));
        }
        cout << "y_m[" << m << "] = " << y_m[m] << endl;
    }
}

void oblicz_y_dla_x (double x, int n, double* tab_x, double h, double* c_k, double* s_k, int stop_wielo) {
    double q = ((x - tab_x[0]) / h);
    double moj_y = 0;
    for (int k = 0; k <= stop_wielo; k++) {
        moj_y += ((c_k[k] / s_k[k]) * wiel_grama (n - 1, q, k));
    }

    cout << "\ny_m[" << x << "] = " << moj_y << endl;
}

int main() {
    int n;
    ifstream plik;
    plik.open("dane_gram.txt", ios::in);

    if (!plik.good()) {
        cout << "Plik nie istnieje\n";
        exit(0);
    }

    plik >> n;
    cout << "Ilosc wezlow: " << n << endl;

    // Stworzenie macierzy
    double* tab_x = new double[n];
    double* tab_y = new double[n];
    double* y_m = new double[n];
   
    for (int i = 0; i < n; i++) {
        plik >> tab_x[i];
        y_m[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        plik >> tab_y[i];
    }
    plik.close();

    cout << "Punkty x: ";
    wyswietl_tablice(tab_x, n);
    cout << "Punkty y: ";
    wyswietl_tablice(tab_y, n);

    double h = tab_x[1] - tab_x[0];
    const int stop_wielo = 1;
    cout << "Stopien wielomianu: " << stop_wielo << endl;

    double x = 0;
    cout << "\nwprowadz x = ";
    cin >> x;

    double c_k[stop_wielo + 1];
    double s_k[stop_wielo + 1];

    for (int k = 0; k <= stop_wielo; k++) {
        c_k[k] = 0;
        s_k[k] = 0;
        double q = 0;
        for (int i = 0; i < n; ++i) {
            q = (tab_x[i] - tab_x[0]) / h;
            double F_k = wiel_grama (n - 1, q , k);
            s_k[k] += F_k * F_k;
            c_k[k] += tab_y[i] * F_k;
        }
    }

    for (int i = 0; i <= stop_wielo; i++) {
        cout << "c_k = " << c_k[i] << "   s_k = " << s_k[i] << endl;
    }
    cout << endl;

    oblicz_y_m (n, tab_x, y_m, h, c_k, s_k, stop_wielo);
    oblicz_y_dla_x (x, n, tab_x, h, c_k, s_k, stop_wielo);

    delete[] tab_x;
    delete[] tab_y;
    delete[] y_m;

    return 0;
}
