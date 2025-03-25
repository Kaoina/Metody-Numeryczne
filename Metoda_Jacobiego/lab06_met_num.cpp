#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath> 
using namespace std;
void wypisz_macierz (int quantity, double** table);
void usun_tablice_dwuwym (double** table, int quantity);
void wypisz_macierz_kwadrat (int quantity, double** table);
void policz_matrix_UandL (double** A, double** LU, int quantity);
void policz_matrix_D (double** A, double** D, int quantity);
bool macierz_slabodominujaca (double** A, int quantity);
void policz_ciag_przyblizen (int quantity, int iteracje, double** LU, double** D, double* matrix_X, double* B);
void policz_ciag_przyblizen_epsilon (int quantity, double epsilon, double** LU, double** D, double* X, double* B);

int main () {

    int quantity;
    ifstream plik;
    plik.open ("RURL_Jacobi_dane1.txt", ios::in);
    if (plik.good () == false) {
        cout << "Plik nie istnieje\n";
        exit (0);
    }
    plik >> quantity;
    cout << "Ilosc rownan: " << quantity << endl;

    //stworzenie macierzy
    double** matrix_A = new double* [quantity];
    double** matrix_D = new double* [quantity];
    double** matrix_LU = new double* [quantity];
    double* matrix_B = new double[quantity];
    double* matrix_X = new double[quantity];

    for (int i = 0; i < quantity; i++) {
        matrix_A[i] = new double[quantity + 1];
        matrix_D[i] = new double[quantity];
        matrix_LU[i] = new double[quantity];
        matrix_X[i] = 0;
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
            matrix_D[i][j] = 0;
            matrix_LU[i][j] = 0;
        }
    }
    plik.close ();

    cout << "Macierz glowna A: " << endl;
    wypisz_macierz (quantity, matrix_A);
   
    policz_matrix_UandL (matrix_A, matrix_LU, quantity);
    policz_matrix_D (matrix_A, matrix_D, quantity);

    bool verification = macierz_slabodominujaca (matrix_A, quantity);
    if (verification = false) {
        return 0;
    }
    else {
        ////zadanie 1
        //int iteracje = 0;
        //cout << "Wybierz ilosc iteracji: ";
        //cin >> iteracje;
        //cout << endl;
        //policz_ciag_przyblizen (quantity, iteracje, matrix_LU, matrix_D, matrix_X, matrix_B);

        //zadanie 2
        //double epsilon = 0.001; 
        double epsilon = 0.000001;
        cout << "Obliczenia dla epsilon = " << epsilon << endl;
        policz_ciag_przyblizen_epsilon (quantity, epsilon, matrix_LU, matrix_D, matrix_X, matrix_B);
    }
    
    usun_tablice_dwuwym (matrix_LU, quantity);
    usun_tablice_dwuwym (matrix_D, quantity);
    delete[] matrix_B;
    delete[] matrix_X;
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
void policz_matrix_UandL (double** A, double** LU, int quantity) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            if (i == j) {
                LU[i][j] = 0;
            }
            else {
                LU[i][j] = A[i][j];
            }
        }
    }
    cout << "Macierz L + U: " << endl;
    wypisz_macierz_kwadrat (quantity, LU);
}
void policz_matrix_D (double** A, double** D, int quantity) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            if (i == j) {
                D[i][j] = 1/ A[i][j];
            }
            else {
                D[i][j] = 0;
            }
        }
    }
    cout << "Macierz Diagonalna * -1: " << endl;
    wypisz_macierz_kwadrat (quantity, D);
}
bool macierz_slabodominujaca (double** A, int quantity) {
    int counter = 0;
    for (int i = 0; i < quantity; i++) {
        double non_diagonal_sum = 0;

        for (int j = 0; j < quantity; j++) {
            if (j != i) {
                non_diagonal_sum += A[i][j];
            }
        }

        if (A[i][i] = non_diagonal_sum) {
            counter++;
        }
        if (A[i][i] < non_diagonal_sum) {
            cout << "Macierz NIE JEST diagonalnie slabo dominujaca\n" << endl;
            return false;
        }
    }

    if (counter > 0) {
        cout << "Macierz JEST diagonalnie slabo dominujaca\n" << endl;
        return true;
    }
    return false;
}
void policz_ciag_przyblizen (int quantity, int iteration, double ** LU, double** D, double* X, double* B) { 
    for (int k = 0; k < iteration; k++) {
        double* tempX = new double[quantity];
        for (int i = 0; i < quantity; i++) {
            double LUX = 0;
            for (int j = 0; j < quantity; j++) {
                if (i != j) {
                    LUX += LU[i][j] * X[j]; //LU * X to macierz 4x1
                }
            }
            tempX[i] = (B[i] - LUX) * D[i][i]; 
        }

        for (int i = 0; i < quantity; i++) {
            X[i] = tempX[i];
        }
    }

    cout << "Rozwiazanie po " << iteration << " iteracjach: " << endl;
    for (int i = 0; i < quantity; i++) {
        cout << "x[" << i << "] = " << X[i] << endl;
    }
}
void policz_ciag_przyblizen_epsilon (int quantity, double epsilon, double** LU, double** D, double* X, double* B) {
    double* tempX = new double[quantity];
    bool converged = false; //zbieżny
    int iteration = 0;
    int max_iterations = 10000;
    double temp_epsilon = 0;

    for (int k = 0; !converged && k < max_iterations; k++) { //dpouki wynik nie będzie zbiezny
        converged = true; 

        for (int i = 0; i < quantity; i++) {
            double LUX = 0;
            for (int j = 0; j < quantity; j++) {
                if (i != j) {
                    LUX += LU[i][j] * X[j];
                }
            }
            tempX[i] = (B[i] - LUX) * D[i][i];
            //sprawdzanie warunku epsilona
            temp_epsilon = fabs (tempX[i] - X[i]);
            if (temp_epsilon >= epsilon) {
                converged = false;
            }
        }
        for (int i = 0; i < quantity; i++) {
            X[i] = tempX[i];
        }
        
        cout << "Iteracja " << iteration << ": Epsilon " << temp_epsilon << endl;
        iteration++;
    }

    cout << "Rozwiazanie po " << iteration << " iteracjach: " << endl;
    for (int i = 0; i < quantity; i++) {
        cout << "x[" << i << "] = " << X[i] << endl;
    }
    
    delete[] tempX; 
}