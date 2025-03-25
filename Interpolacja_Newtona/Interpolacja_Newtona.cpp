#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

double newton (int quantity, double** table, double point);
double count_b (int quantity, double** table);
double count_multi (int quantity, int i, double** table);
double count_p (int quantity, double point, double** table);

int main () {


    //odczyt iloœci wêz³ów i sprawdzenie pliku
    int quantity;
    ifstream plik;
    //wybierz opcjê 1 lub 2
    plik.open ("MN-2-p1.txt", ios::in);//opcja 1
    //plik.open ("MN-2-p2.txt", ios::in); //opcja 2
    if (plik.good () == false) {
        cout << "Plik nie istnieje\n";
        exit (0);
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

    //liczenie interpolacji Newtona
    double point;
    cout << "Podaj punkt w ktorym obliczymy wartosc wielomianu: ";
    cin >> point;

    double polynomial;
    double sum = 0.0;
    cout << "0 Wspolczynnik wielomianu Newtona: " << interpol[0][1] << endl;
    sum = newton (quantity, interpol, point);
    polynomial = interpol[0][1] + sum;
    cout << "Wartosc funkcji w danym punkcie " << polynomial << endl;
        

    //usuniêcie tablicy dynamicznej
    for (int i = 0; i < quantity; i++) {
        delete[] interpol[i];
    }
    delete[] interpol;
    return 0;
}

double newton (int quantity, double ** table, double point) {
    double sum = 0.0;
  
    for (int k = 1; k < quantity; k++) {
        sum += (count_b(k, table) * count_p(k, point, table));
    }

    return sum;
}
double count_b (int quantity, double ** table) {
    double result = 0.0;
    for (int i = 0; i <= quantity; i++) {
        result += (table[i][1] / count_multi(quantity, i, table));
    }
    cout << quantity << " Wspolczynnik wielomianu Newtona: " << result <<endl;
    return result;
}
double count_multi (int quantity, int i, double ** table) {
    double result = 1;
    for (int j = 0; j <= quantity; j++) {
        if (j == i) {
            continue;
        }
        result *= (table[i][0] - table[j][0]);
    }
    return result;
}
double count_p (int quantity, double point, double** table) {
    double result = 1;
    for (int i = 0; i <= (quantity - 1); i++) {
        result *= (point - table[i][0]);
    }
    return result;
}
