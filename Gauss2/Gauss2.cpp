#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;
vector<int> kolejnosc_kolumn;
void gaussZero (double** table, int quantity, int wiersz);
void wypisz_macierz (int quantity, double** el_gausso);
void policz_rozwiazania (int quantity, double** table, double* wyniki);
void usun_tablice (double** el_gausso, int quantity, double* wyniki);
void ustaw_najwiekszy_wiersze (double** table, int quantity);
void ustaw_najwiekszy_kolumny (double** table, int quantity);

int main () {
    int quantity;
    ifstream plik;
    //plik.open ("RURL_dane1.txt", ios::in);//opcja 1
    plik.open ("RURL_dane2.txt", ios::in); //opcja 2
    //plik.open ("RURL_dane3.txt", ios::in); //opcja 3
    if (plik.good () == false) {
        cout << "Plik nie istnieje\n";
        exit (0);
    }
    plik >> quantity;
    cout << "Ilosc rownan: " << quantity << endl;

    //stworzenie macierzy
    double** el_gausso = new double* [quantity];
    for (int i = 0; i < quantity; i++) {
        el_gausso[i] = new double[quantity + 1];
        kolejnosc_kolumn.push_back (i);
    }

    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
            plik >> el_gausso[i][j];
        }
    }
    plik.close ();

    cout << "Przed zamiana: " << endl;
    wypisz_macierz (quantity, el_gausso);

    ////-------------------------------------------------------
    ////ZADANIE I 
    //ustaw_najwiekszy_wiersze (el_gausso, quantity);
  
    //cout << "Po zamianie: " << endl;
    //wypisz_macierz (quantity, el_gausso);

    //double* wyniki = new double[quantity];
    //policz_rozwiazania (quantity, el_gausso, wyniki);

    ////----------------------------------------------------------------
    //ZADANIE II 
    ustaw_najwiekszy_kolumny (el_gausso, quantity);

    cout << "Po zamianie: " << endl;
    wypisz_macierz (quantity, el_gausso);

    double* wyniki = new double[quantity];
    policz_rozwiazania (quantity, el_gausso, wyniki);
    //----------------------------------------------------------------
    //usun_tablice (el_gausso, quantity, wyniki);
    return 0; 
}

void ustaw_najwiekszy_kolumny (double** table, int quantity) {
    for (int i = 0; i < quantity - 1; i++) { //to do kazdego wiersza
        double value = abs(table[i][i]);
        int column = i;
       
        for (int j = i + 1; j < quantity; j++) { //to do kazdej kolumny
            if (abs(table[i][j]) > value) {
                value = table[i][j];
                column = j;
            }
        }
       // cout << "Najwieksza wartosc w kolumnie " << column << " i wierszu " << i << " to: " << value << endl;

        if (column != i) {
            for (int k = 0; k < quantity; k++) { // zamieñ ca³¹ kolumnê
                double temp = table[k][i];
                table[k][i] = table[k][column];
                table[k][column] = temp;
            }
            
            int temp2 = kolejnosc_kolumn[i];
            kolejnosc_kolumn[i] = kolejnosc_kolumn[column];
            kolejnosc_kolumn[column] = temp2;
        }
        gaussZero (table, quantity, i);
    }
}

void ustaw_najwiekszy_wiersze (double** table, int quantity){ //i to indeks kolumny 
    for (int i = 0; i < (quantity - 1); i++) {
        int line = i;
        double value = table[i][i];

        for (int j = i + 1; j < quantity; j++) {
            if (abs (value) < abs (table[j][i])) {
                value = table[j][i];
                line = j;
            }
        }
        //cout << "Najwieksza wartosc w kolumnie " << i << " i wierszu " << line << " to: " << value << endl;

        for (int k = 0; k <= quantity + 1; k++) {
            double temp = table[i][k];
            table[i][k] = table[line][k];
            table[line][k] = temp;
        }
        //zerownie kolumn 
        gaussZero (table, quantity, i);
    }
}

void usun_tablice (double** el_gausso, int quantity, double* wyniki) {
    for (int i = 0; i < quantity; i++) {
        delete[] el_gausso[i];
    }
    delete[] el_gausso;
    delete[] wyniki;
}

void policz_rozwiazania (int quantity, double** table, double* wyniki) {
    for (int l = quantity - 1; l >= 0; l--) {
        wyniki[l] = table[l][quantity] / table[l][l]; //b_n/a_nn
        for (int k = l + 1; k < quantity; k++) {
            wyniki[l] -= (table[l][k] * wyniki[k]) / table[l][l]; //reszta wzoru
        }
    }

    for (int i = 0; i < quantity; i++) { //wypisanie roziwazañ
        for (int j = 0; j < quantity; j++){
            if (kolejnosc_kolumn[j] == i) {
                cout << "Wynik rownan to x" << i << " = " << wyniki[j] << endl;
            }
        }
    }
}

void wypisz_macierz (int quantity, double** el_gausso) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
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
    //wypisz_macierz (quantity, table);
}

void gaussZero (double** table, int quantity, int i) {
    for (int j = i + 1; j < quantity; j++) { //tyle co wierszy, j -> wiersze

        if (table[i][i] == 0) {
            cout << "W wierszu " << j + 1 << ". kolumnie " << i << " jest 0\n\n";
            return;
        }
        
        double mnoz = (table[j][i] / table[i][i]);
        // cout << "\nMnoznik wiersz " << j << ". kolmna "<< i << ".  -> " << mnoz << endl;
        odejmij_wiersz (table, quantity, i, j, mnoz);
    }
}
