
#include <iostream>
#include <vector>

using namespace std;

const int MAXINT = 2147483647/2; // Największa liczba całkowita

class Wierzcholek
{
public:
    int gdzieProwadzi;
    int waga;
};
int n, m;
// Funkcja wyznacza najkrótsze ścieżki
// v - wierzchołek startowy
// Wyjście:
// true  - wyniki w d i p
// false - graf zawiera ujemny cykl
//------------------------------------
bool BF(int v, vector<vector<Wierzcholek>> listaSasiedztwa, int *tablicaKosztow, int *tablicaSciezek)
{
    int i, x;
    bool test;

    tablicaKosztow[v] = 0;  // Zerujemy koszt dojścia do v
    for (i = 1; i < n; i++) // Pętla relaksacji
    {
        test = true;                                                                                                      // Oznacza, że algorytm nie wprowadził zmian do d i p
        for (x = 0; x < n; x++)                                                                                           // Przechodzimy przez kolejne wierzchołki grafu
            for (int k = 0; k < listaSasiedztwa[x].size(); k++)                                                           // Przeglądamy listę sąsiadów wierzchołka x
                if (tablicaKosztow[listaSasiedztwa[x][k].gdzieProwadzi] > tablicaKosztow[x] + listaSasiedztwa[x][k].waga) // Sprawdzamy warunek relaksacji
                {
                    test = false;                                                                                         // Jest zmiana w d i p
                    tablicaKosztow[listaSasiedztwa[x][k].gdzieProwadzi] = tablicaKosztow[x] + listaSasiedztwa[x][k].waga; // Relaksujemy krawędź z x do jego sąsiada
                    tablicaSciezek[listaSasiedztwa[x][k].gdzieProwadzi] = x;                                              // Poprzednikiem sąsiada będzie x
                }
        if (test)
            return true; // Jeśli nie było zmian, to kończymy
    }

    // Sprawdzamy istnienie ujemnego cyklu

    for (x = 0; x < n; x++)
        for (int k = 0; k < listaSasiedztwa[x].size(); k++)
            if (tablicaKosztow[listaSasiedztwa[x][k].gdzieProwadzi] > tablicaKosztow[x] + listaSasiedztwa[x][k].gdzieProwadzi)
                return false; // ujemny cykl!!

    return true;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int main()
{
    int i, v;
    int x, y, w;
    int sptr;
    vector<int> S;

    cin >> v >> n >> m; // Wierzchołek startowy, liczba wierzchołków i krawędzi

    vector<vector<Wierzcholek>> ListaSasiedztwa;
    vector<Wierzcholek> a;             //lista robocza do wypelnienia vectora
    int *tablicaKosztow = new int[n]; // Tworzymy tablicę kosztów dojścia
    int *tablicaSciezek = new int[n]; // Tworzymy tablice poprzedników

    for (i = 0; i < n; i++) // Inicjujemy struktury danych
    {
        ListaSasiedztwa.push_back(a);
        tablicaKosztow[i] = MAXINT;
        tablicaSciezek[i] = -1;
    }

    for (i = 0; i < m; i++)
    {
        cin >> x >> y >> w; // Czytamy wierzchołki krawędzi oraz jej wagę
        Wierzcholek nowy;
        nowy.gdzieProwadzi = y;
        nowy.waga = w;
        ListaSasiedztwa[x].push_back(nowy);
    }

    cout << endl;

    // Wyznaczamy najkrótsze ścieżki algorytmem Bellmana-Forda

    if (BF(v, ListaSasiedztwa, tablicaKosztow, tablicaSciezek))
    {
        vector<int> S; // Tworzymy prosty stos
        sptr = 0;

        for (i = 0; i < n; i++)
        {
            cout << i << ": ";
            for (x = i; x != -1; x = tablicaSciezek[x]) // Wierzchołki ścieżki umieszczamy na stosie
                S.push_back(x);                          // w kolejności od ostatniego do pierwszego

            while (S.empty() == false) // Wierzchołki ze stosu drukujemy
            {
                cout << S.back() << " "; // w kolejności od pierwszego do ostatniego
                S.pop_back();
            }
            cout << "$" << tablicaKosztow[i] << endl; // Na końcu wyświetlamy koszt
        }
    }
    else
        cout << "Negative Cycle found!" << endl;

    // Usuwamy struktury dynamiczne

    return 0;
}