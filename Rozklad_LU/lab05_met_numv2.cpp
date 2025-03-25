#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
void gaussZero (double** table, int quantity, int wiersz);
void wypisz_macierz (int quantity, double** table);
void policz_rozwiazania (int quantity, double** table, double* wyniki);
void usun_tablice_dwuwym (double** table, int quantity);
void wypisz_macierz_kwadrat (int quantity, double** table);
void lower_and_upper (double** U, double** L, double** A, int quantity);
void policz_y (double* B, double** L, double* wyniki, int quantity);
void policz_matrix_UandY (double** U, double* Y, double** A, int quantity);

int main () {

    int quantity;
    ifstream plik;
    //plik.open ("RURL_dane1.txt", ios::in);//opcja 1
    plik.open ("RURL_dane2.txt", ios::in);//opcja 2
    if (plik.good () == false) {
        cout << "Plik nie istnieje\n";
        exit (0);
    }
    plik >> quantity;
    cout << "Ilosc rownan: " << quantity << endl;

    //stworzenie macierzy
    double** matrix_A = new double* [quantity];
    double** matrix_L = new double* [quantity];
    double** matrix_U = new double* [quantity];
    double* matrix_B = new double[quantity];

    for (int i = 0; i < quantity; i++) {
        matrix_A[i] = new double[quantity + 1];
        matrix_L[i] = new double[quantity];
        matrix_U[i] = new double[quantity];
    }

    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
            plik >> matrix_A[i][j];
            if (j == quantity) {
                matrix_B[i] = matrix_A[i][j];
            }
        }
    }
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            matrix_U[i][j] = 0;
            if (i == j) {
                matrix_L[i][j] = 1;
            }
            else {
                matrix_L[i][j] = 0;
            }
        }
    }
    plik.close ();

    cout << "Macierz glowna A: " << endl;
    wypisz_macierz (quantity, matrix_A);

    lower_and_upper (matrix_U, matrix_L, matrix_A, quantity);

    cout << "Macierz B: " << endl;
    for (int i = 0; i < quantity; i++) {
        cout << matrix_B[i]<<endl;
    }
    cout << endl;

    double* matrix_Y = new double [quantity];
    policz_y (matrix_B, matrix_L, matrix_Y, quantity);
    policz_matrix_UandY (matrix_U, matrix_Y, matrix_A, quantity);
    double* wyniki2 = new double[quantity];
    policz_rozwiazania (quantity, matrix_A, wyniki2);

    usun_tablice_dwuwym(matrix_A, quantity);
    usun_tablice_dwuwym (matrix_L, quantity);
    usun_tablice_dwuwym (matrix_U, quantity);
    delete[] matrix_B;
    delete[] matrix_Y;
    return 0;
}

void usun_tablice_dwuwym (double** table, int quantity) {
    for (int i = 0; i < quantity; i++) {
        delete[] table[i];
    }
    delete[] table;
}
void wypisz_macierz (int quantity, double** table) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
            cout << " " << table[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
void wypisz_macierz_kwadrat (int quantity, double** table) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            cout << " " << table[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
void policz_rozwiazania (int quantity, double** table, double* wyniki) {
    for (int l = quantity - 1; l >= 0; l--) {
        wyniki[l] = table[l][quantity] / table[l][l]; //b_n/a_nn
        for (int k = l + 1; k < quantity; k++) {
            wyniki[l] -= (table[l][k] * wyniki[k]) / table[l][l]; //reszta wzoru
        }
    }
    for (int i = 0; i < quantity; i++) { //wypisanie roziwazań
        cout << "Wynik rownania " << i + 1 << ". to " << wyniki[i] << endl;
    }
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
            cout << "W wierszu " << j + 1 << ". kolumnie " << i << " jest 0\n\n";
            return;
        }
        double mnoz = (table[j][i] / table[i][i]);
        //cout << "\nMnoznik wiersz " << j << ". kolmna "<< i << ".  -> " << mnoz << endl;
        odejmij_wiersz (table, quantity, i, j, mnoz);
    }
}
void lower_and_upper (double** U, double** L, double** A, int quantity) {
    double suma = 0;
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            if (i <= j) {
                for (int k = 0; k < i; k++) {
                    suma += (L[i][k] * U[k][j]);
                }
                U[i][j] = A[i][j] - suma;
                suma = 0;
            }
            else {
                for (int k = 0; k < j; k++) {
                    suma += (L[i][k] * U[k][j]);
                }
                L[i][j] = (1 / U[j][j]) * (A[i][j] - suma);
                suma = 0;
            }
        }
    }
    //Wyświetl
    cout << "Macierz Lower: " << endl;
    wypisz_macierz_kwadrat (quantity, L);
    cout << "Macierz Upper: " << endl;
    wypisz_macierz_kwadrat (quantity, U);
}
void policz_y (double* B, double** L, double* Y, int quantity) {
    double suma = 0;
    Y[0] = B[0];
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < i; j++) {
            suma += (L[i][j] * Y[j]);
        }
        Y[i] = B[i] - suma;
        suma = 0;
    }

    //wyświetl
    cout << "Macierz Y: " << endl;
    for (int i = 0; i < quantity; i++) {
        cout << Y[i] << endl;
    }
    cout << endl;
}
void policz_matrix_UandY (double ** U, double* Y, double** A, int quantity) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
            if (j == quantity) {
                A[i][j] = Y[i];
            }
            else {
                A[i][j] = U[i][j];
            }
        }
    }

    cout << "Macierz U rozszerzona o macierz Y: " << endl;
    wypisz_macierz (quantity, A);
}