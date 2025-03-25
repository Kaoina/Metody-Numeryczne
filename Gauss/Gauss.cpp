#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
void gaussZero (double** table, int quantity, int wiersz);
void wypisz_macierz (int quantity, double** el_gausso);
void policz_rozwiazania (int quantity, double** table, double* wyniki);
void usun_tablice (double** el_gausso, int quantity, double* wyniki);

int main () {

    int quantity;
    ifstream plik;
    plik.open ("RURL_dane1.txt", ios::in);//opcja 1
    //plik.open ("RURL_dane2.txt", ios::in); //opcja 2
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
    }

    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
            plik >> el_gausso[i][j];
        }
    }
    plik.close ();



    wypisz_macierz (quantity, el_gausso);
    //postêpowanie proste
    for (int i = 0; i < (quantity - 1); i++) { //tyle co kolumn, i -> kolumny
        gaussZero (el_gausso, quantity, i);
    }
    wypisz_macierz (quantity, el_gausso);

     //rozwi¹zania równania - postêpowanie odwrotne 
     double* wyniki = new double[quantity];
     policz_rozwiazania (quantity, el_gausso, wyniki);




     usun_tablice (el_gausso, quantity, wyniki);
     return 0;
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
        cout << "Wynik rownania " << i + 1 << ". to " << wyniki[i] << endl;
    }
}
void wypisz_macierz (int quantity, double ** el_gausso) {
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity + 1; j++) {
            cout << " " << el_gausso[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
void odejmij_wiersz(double ** table, int quantity, int i, int j, double mnoz){
    for (int k = 0; k <= (quantity+1); k++) { //do odejmowania  w kazdej kolumnie
        table[j][i+k] = table[j][i+k] - (table[i][i+k] * mnoz);
    }
   // wypisz_macierz (quantity, table);
}
void gaussZero(double** table,int quantity, int i) {
    for (int j = i + 1; j < quantity; j++) { //tyle co wierszy, j -> wiersze
        if (table[i][i] == 0) {
            cout << "W wierszu " << j+1 <<". kolumnie " << i << " jest 0, nie trzeba nic zmieniac\n\n";
            return;
        }
        double mnoz = (table[j][i] / table[i][i]); 
       // cout << "\nMnoznik wiersz " << j << ". kolmna "<< i << ".  -> " << mnoz << endl;
        odejmij_wiersz(table ,quantity, i, j, mnoz);
    }
}

