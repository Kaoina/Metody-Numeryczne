#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

double* wczytaj_matrix (int size, fstream& plik)
{
    double* matrix = new double[size];

    for (int i = 0; i < size; i++) {
        plik >> matrix[i];
    }

    for (int i = 0; i < size; i++) {
        cout << " " << matrix[i] << " ";
    }
    return matrix;
}

//lab 3
void policz_rozwiazania (int quantity, double** table, double* wyniki) {
    for (int l = quantity - 1; l >= 0; l--) {
        wyniki[l] = table[l][quantity] / table[l][l]; //b_n/a_nn
        for (int k = l + 1; k < quantity; k++) {
            wyniki[l] -= (table[l][k] * wyniki[k]) / table[l][l]; //reszta wzoru
        }
    }
    for (int i = 0; i < quantity; i++) { //wypisanie roziwazañ
        cout << "a" << i << " = " << wyniki[i] << endl;
    }
}
void wypisz_macierz (int quantity, double** el_gausso) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            cout << " " << el_gausso[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
void odejmij_wiersz (double** table, int quantity, int i, int j, double mnoz) {
    for (int k = 0; k <= (quantity + 1); k++) { //do odejmowania  w kazdej kolumnie
        table[j][i + k] = table[j][i + k] - (table[i][i + k] * mnoz);
    }
    // wypisz_macierz (quantity, table);
}
void gaussZero (double** table, int quantity, int i) {
    for (int j = i + 1; j < quantity; j++) { //tyle co wierszy, j -> wiersze
        if (table[i][i] == 0) {
            cout << "W wierszu " << j + 1 << ". kolumnie " << i << " jest 0, nie trzeba nic zmieniac\n\n";
            return;
        }
        double mnoz = (table[j][i] / table[i][i]);
        // cout << "\nMnoznik wiersz " << j << ". kolmna "<< i << ".  -> " << mnoz << endl;
        odejmij_wiersz (table, quantity, i, j, mnoz);
    }
}
//lab3
double suma (double m, double* x_matrix, double* waga, int k, int j)
{
    double Suma = 0;
    for (int i = 0; i < m; i++)
    {
        Suma += pow (x_matrix[i], k) * pow (x_matrix[i], j) * waga[i];
    }
    return Suma;
}
double* nowe_Y (double* a, double* x_matrix, int m, int stop_wielo)
{
    double* new_matrix_y = new double[m];

    for (int i = 0; i < m; i++) {
        double nowy = 0;

        for (int j = 0; j < (stop_wielo + 1); j++)
        {
            nowy += a[j] * pow (x_matrix[i], j);
        }
        new_matrix_y[i] = nowy;
        cout << "Y[" << i+1 << "] = " << new_matrix_y[i] << endl;
    }
    return new_matrix_y;
}

int main ()
{
    int m;
    fstream plik_x, plik_y, plik_w;
    //------------X & m
    plik_x.open ("wezly_x.txt", ios::in);
    if (!plik_x.is_open ()) {
        cout << "Plik nie istnieje\n";
        exit (0);
    }
    plik_x >> m;
    cout << "Liczba wezlow: " << m << endl;
    cout << "Wezly aproksymacji" << endl;
    cout << "x:";
    double* x_matrix = wczytaj_matrix (m, plik_x);
    plik_x.close ();

    //------------Y
    plik_y.open ("wezly_y.txt", ios::in);
    if (!plik_y.is_open ()) {
        cout << "Plik nie istnieje\n";
        exit (0);
    }
    cout << endl << "y:";
    double* y_matrix = wczytaj_matrix (m, plik_y);
    plik_y.close ();

    //-------------W
    plik_w.open ("wezly_w.txt", ios::in);
    if (!plik_w.is_open ()) {
        cout << "Plik nie istnieje\n";
        exit (0);
    }
    cout << endl << "wagi:";
    double* w_matrix = wczytaj_matrix (m, plik_w);
    plik_w.close ();


    //-------------n
    int stop_wielo;
    stop_wielo = 1; //WYBIERZ STOPIEŃ WIELOMIANU
    cout << endl << "Stopien wielomianu: " << stop_wielo << endl << endl;
    //~~~~~~~~~~~~~~koniec wczytywania danych~~~~~~~~~~~~~~~~//

    double** g_matrix = new double* [stop_wielo + 1];
    for (int i = 0; i < stop_wielo + 1; i++) {
        g_matrix[i] = new double[stop_wielo + 2]; // Zwiększam o 1 dla kolumny wektora F

        for (int j = 0; j < stop_wielo + 1; j++) {
            g_matrix[i][j] = suma (m, x_matrix, w_matrix, i, j);
        }
    }
    cout << "Macierz g: " << endl;
    wypisz_macierz (stop_wielo + 1, g_matrix);

    cout << "Wektor F: " << endl;
    double* F = new double[stop_wielo + 1];
    for (int i = 0; i < stop_wielo + 1; i++) {
        F[i] = 0;

        for (int j = 0; j < m; j++) {
            F[i] += pow (x_matrix[j], i) * y_matrix[j] * w_matrix[j];
        }
        g_matrix[i][stop_wielo + 1] = F[i];
        cout << "F[" << i << "]" << F[i] << endl;
    }
    cout << endl;
    //-------eliminacja gaussa lab3

  //postepowanie proste
    for (int i = 0; i < stop_wielo; i++) { //tyle co kolumn, i -> kolumny
        gaussZero (g_matrix, stop_wielo + 1, i);
    }
    cout << "Macierz po postepowaniu prostym: " << endl;
    wypisz_macierz (stop_wielo + 1, g_matrix);

    //rozwiazania równania - postepowanie odwrotne 
    cout << "Wyniki: " << endl;
    double* wyniki = new double[stop_wielo];
    policz_rozwiazania (stop_wielo + 1, g_matrix, wyniki);

    //nowe wartosci 
    cout << endl << "Wartosci po aproksymacji: " << endl;
    y_matrix = nowe_Y(wyniki, x_matrix, m, stop_wielo);

    return 0;
}

