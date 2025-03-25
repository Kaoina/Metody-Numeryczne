#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

double calc_polynomials (int node_number, double ** table, int quantity, double point);

int main () {
    

    //odczyt iloœci wêz³ów i sprawdzenie pliku
    int quantity;
    ifstream plik;
    //WYBIERZ ZADANIE 1 LUB 2 
    plik.open ("MN-1.txt", ios::in);  //ZADANIE 1
    //plik.open("MN-1.2.txt", ios::in); //ZADANIE 2

    if (plik.good () == false) {
        cout << "Plik nie istnieje\n";
            exit(0);
    }
    plik >> quantity;
    cout << "Ilosc podanych wezlow: " << quantity << endl;

    //odczyt tabelii wêz³ów i wartoœci
    double** interpol = new double* [quantity]; 
    for (int i = 0; i < quantity; i++) {
        interpol[i] = new double[2];
    }

    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < 2; j++) {
            plik >> interpol[i][j];
            //wyœwietlenie
            if (j == 0)
                cout << "wezel " << interpol[i][j];
            else
                cout << "->" << interpol[i][j] << endl;
        }
    }
    plik.close ();

    //liczenie interpolacji
    double point;
    cout << "Podaj punkt w ktorym obliczymy wartosc wielomianu: ";
    cin >> point;

    double polynomial = 0.0;
    for (int i = 0; i < quantity; i++) {
     polynomial += (interpol[i][1] * calc_polynomials(i, interpol, quantity, point));
     
    }
    cout << "Wartosc funckji w danym punkcie to " << polynomial << endl;

    //usuniêcie tablicy dynamicznej
    for (int i = 0; i < quantity; i++) {
        delete[] interpol[i];
    }
    delete[] interpol;
    return 0;
}

double calc_polynomials(int node_number, double ** table, int quantity, double point) { 
    double result = 1;
     for (int j = 0; j < quantity; j++){
            if (j == node_number) {
                continue;
            }
            result *= (point - table[j][0]) / (table[node_number][0] - table[j][0]);
        }  
    
            return result;  
}