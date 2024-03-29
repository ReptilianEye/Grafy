#include <iostream>
#include <vector>

using namespace std;

// Typy danych

class Wierzcholek
{
public:
    int gdzieProwadzi;
    int waga;
};

const int MAXINT = 2147483647;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int wierzcholek, n, m;
    int x, y, w;
    int i, j, u;

    cin >> wierzcholek >> n >> m; //wczytanie wierzcholka startowego, liczby wierzcholkow i krawedzi

    // Tworzymy tablice dynamiczne
    int *tablicaKosztowD = new int[n]; // Tablica kosztów dojścia
    int *tablicasciezkiP = new int[n]; // Tablica poprzedników
    bool *QS = new bool[n];            // Zbiory Q i S
    int *tablicaWag = new int[n];
    vector<vector<Wierzcholek>> listaSasiedztwa; // Tablica list sąsiedztwa

    // Odczytujemy dane wejściowe
    for (i = 0; i < n; i++)
    {
        tablicaKosztowD[i] = MAXINT;
        tablicasciezkiP[i] = -1;
        QS[i] = false;
        vector<Wierzcholek> a;
        listaSasiedztwa.push_back(a);
    }
    for (i = 0; i < m; i++)
    {
        cin >> x >> y >> w; // Odczytujemy krawędź z wagą

        Wierzcholek NowyWierzcholek;       // Tworzymy element listy sąsiedztwa
        NowyWierzcholek.gdzieProwadzi = y; // Wierzchołek docelowy krawędzi
        NowyWierzcholek.waga = w;          // Waga krawędzi

        listaSasiedztwa[x].push_back(NowyWierzcholek); // Element dołączamy do listy
    }

    cout << endl;

    tablicaKosztowD[wierzcholek] = 0; // Koszt dojścia do wierzcholka startowego jest zerowy

    vector<int> QWierzcholkow;
    QWierzcholkow.push_back(wierzcholek);

    // Wyznaczamy ścieżki
    for (i = 0; i < n; i++)
    {
        //for (j = 0; QS[j]; j++)
        //    ; //ustawiamy j na wierzcholek nalezacy do Q (grafu niezanalizowanego)

        //for (u = j++; j < n; j++)
        //    if (!QS[j] && (tablicaKosztowD[j] < tablicaKosztowD[u])) // Szukamy wierzchołka w Q o najmniejszym koszcie d
        if (QWierzcholkow.empty())
            break;
        u = QWierzcholkow.front();

        QS[u] = true; // Znaleziony wierzchołek przenosimy do S
        QWierzcholkow.erase(QWierzcholkow.begin());
        // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q

        for (int k = 0; k < listaSasiedztwa[u].size(); k++)
            if (!QS[listaSasiedztwa[u][k].gdzieProwadzi] && (tablicaKosztowD[listaSasiedztwa[u][k].gdzieProwadzi] > tablicaKosztowD[u] + listaSasiedztwa[u][k].waga))
            {
                tablicaKosztowD[listaSasiedztwa[u][k].gdzieProwadzi] = tablicaKosztowD[u] + listaSasiedztwa[u][k].waga;

                tablicasciezkiP[listaSasiedztwa[u][k].gdzieProwadzi] = u;

                if (QWierzcholkow.empty())
                {
                    QWierzcholkow.push_back(listaSasiedztwa[u][k].gdzieProwadzi);
                    continue;
                }
                for (int q = 0; q < QWierzcholkow.size(); q++)
                {
                    if (tablicaKosztowD[QWierzcholkow[q]] >= tablicaKosztowD[listaSasiedztwa[u][k].gdzieProwadzi])
                    {
                        QWierzcholkow.insert(QWierzcholkow.begin() + q, listaSasiedztwa[u][k].gdzieProwadzi);
                        break;
                    }
                    if(q == QWierzcholkow.size() - 1)   //jesli przepatrzylismy wszystkie a dalej nie dodalismy wierzcholka 
                    {
                        QWierzcholkow.push_back(listaSasiedztwa[u][k].gdzieProwadzi);   //dodajemy go na koncu
                    }
                }
            }
    }

    // Gotowe, wyświetlamy wyniki
    vector<int> stosDoWyswietlaniaSciezki;
    for (i = 0; i < n; i++)
    {
        cout << i << ": ";

        // Ścieżkę przechodzimy od końca ku początkowi,
        // Zapisując na stosie kolejne wierzchołki

        for (j = i; j > -1; j = tablicasciezkiP[j])
            stosDoWyswietlaniaSciezki.push_back(j);

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while (!stosDoWyswietlaniaSciezki.empty())
        {
            cout << stosDoWyswietlaniaSciezki.back() << " ";
            stosDoWyswietlaniaSciezki.pop_back();
        }
        // Na końcu ścieżki wypisujemy jej koszt

        cout << "$" << tablicaKosztowD[i] << endl;
    }

    return 0;
}
