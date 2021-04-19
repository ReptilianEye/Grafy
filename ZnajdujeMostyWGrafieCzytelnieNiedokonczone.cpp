#include <iostream>
#include <vector>

using namespace std;

// Typy dla dynamicznej tablicy list sąsiedztwa i listy mostów

struct slistEl
{
    slistEl *next;
    int v;
};
class Wierzcholek
{
public:
    int gdzieProwadzi;
    int numerKrawedzi;
};
class DoOdwiedzenia
{
public:
    int gdzieProwadzi;
    int ojciec = -1;
    int KrokTrasy;
};
class Krawedz
{
public:
    int v1;
    int v2;
    bool CzyMost = false;
};
// Zmienne globalne

int n,
    m, cv; // Liczba wierzchołków, krawędzi, numeracja
//slistEl **graf; // Tablica list sąsiedztwa
vector<vector<Wierzcholek>> Graf;
int *D; // Numery DFS
//slistEl *L;     // Lista mostów
Krawedz *CzyKrawedzJestMostem;

// Funkcja rekurencyjna wyszukująca mosty
// v  - numer bieżącego wierzchołka
// ojciec - ojciec bieżącego wierzchołka na drzewie rozpinającym
// Reszta parametrów to zmienne globalne
//----------------------------------------------------------
int DFSb(int WierzcholekStartowy)
{
    int Low, temp, sasiad;

    // Numerujemy wierzchołek, ustalamy wstępną wartość Low oraz zwiększamy numerację

    vector<DoOdwiedzenia> StosRekurencyjny;
    DoOdwiedzenia pierwszy;
    pierwszy.gdzieProwadzi = WierzcholekStartowy;
    pierwszy.KrokTrasy = 1;

    StosRekurencyjny.push_back(pierwszy);

    vector<int> Trasa;

    while (!StosRekurencyjny.empty())
    {
        DoOdwiedzenia aktualnyWierzcholek = StosRekurencyjny.back();
        StosRekurencyjny.pop_back();

        while (Trasa.size() >= aktualnyWierzcholek.KrokTrasy)
        {
            int numerWierzcholka = Trasa.back();

            Trasa.pop_back();
            Low--;
        }
        Trasa.push_back(aktualnyWierzcholek.gdzieProwadzi);
       
        Low = cv;
        cv++;
        D[aktualnyWierzcholek.gdzieProwadzi] = Low;

        bool CzyDodalismySasiada = false;
        for (int i = 0; i < Graf[aktualnyWierzcholek.gdzieProwadzi].size(); i++)
        //for (p = graf[v]; p; p = p->next) // Przeglądamy listę sąsiadów
        {
            //sasiad = p->v;        // sasiad - numer wierzchołka sąsiada
            DoOdwiedzenia sasiad;
            sasiad.gdzieProwadzi = Graf[aktualnyWierzcholek.gdzieProwadzi][i].gdzieProwadzi;

            if (sasiad.gdzieProwadzi != aktualnyWierzcholek.gdzieProwadzi)
            //if (sasiad != ojciec) // sasiad nie może być ojcem v
            {
                if (D[sasiad.gdzieProwadzi] == 0) // Jeśli sąsiad sasiad nie był odwiedzany, to
                {
                    CzyDodalismySasiada = true;
                    sasiad.ojciec = aktualnyWierzcholek.gdzieProwadzi;
                    sasiad.KrokTrasy = Trasa.size() + 1;
                    StosRekurencyjny.push_back(sasiad);
                    //temp = DFSb(sasiad, v); // rekurencyjnie odwiedzamy go
                }
                else if (Low > D[sasiad.gdzieProwadzi])
                    Low = D[sasiad.gdzieProwadzi];
            }
        }
        if (!CzyDodalismySasiada)
        {
            if ((aktualnyWierzcholek.ojciec > -1) && (Low == D[aktualnyWierzcholek.gdzieProwadzi]))
            {
                int numerKrawedzi;
                for (int i = 0; i < Graf[aktualnyWierzcholek.gdzieProwadzi].size(); i++)
                    if (Graf[aktualnyWierzcholek.gdzieProwadzi][i].gdzieProwadzi == aktualnyWierzcholek.ojciec)
                    {
                        numerKrawedzi = Graf[aktualnyWierzcholek.gdzieProwadzi][i].numerKrawedzi;
                        CzyKrawedzJestMostem[numerKrawedzi].CzyMost = true;
                        CzyKrawedzJestMostem[numerKrawedzi].v1 = aktualnyWierzcholek.gdzieProwadzi;
                        CzyKrawedzJestMostem[numerKrawedzi].v2 = Graf[aktualnyWierzcholek.gdzieProwadzi][i].gdzieProwadzi;

                        break;
                    }
            }
            if (temp < Low)
                Low = temp;
        }

        // Wszyscy sąsiedzi zostali odwiedzeni. Teraz robimy test na most
    }
    return Low; // Wynik
}

// **********************
// *** Program główny ***
// **********************

int main()
{
    int i, sasiad, v; // Numery wierzchołków
    slistEl *p, *r;

    cin >> n >> m; // Odczytujemy liczbę wierzchołków i krawędzi
    CzyKrawedzJestMostem = new Krawedz[m + 1];

    D = new int[n + 1]{0};

    vector<Wierzcholek> a;
    for (i = 0; i <= n; i++)
    {
        Graf.push_back(a);
    }

    // Odczytujemy kolejne definicje krawędzi

    for (i = 1; i <= m; i++)
    {
        cin >> v >> sasiad; // Wierzchołki tworzące krawędź
        Wierzcholek nowy;
        nowy.gdzieProwadzi = sasiad;
        nowy.numerKrawedzi = i;
        Graf[v].push_back(nowy);
        nowy.gdzieProwadzi = v;
        Graf[sasiad].push_back(nowy);
    }

    // Szukamy mostów

    for (i = 0; i < Graf.size(); i++)
        if (!Graf[i].empty())
            if (D[i] == 0) // Szukamy nieodwiedzonego wierzchołka
            {
                cv = 1;  // Początek numeracji DFS
                DFSb(i); // Szukamy mostów
            }

    cout << endl;

    // Wypisujemy znalezione mosty

    for (int i = 1; i <= m; i++)
    {
        if (CzyKrawedzJestMostem[i].CzyMost)
            cout << CzyKrawedzJestMostem[i].v1 << " " << CzyKrawedzJestMostem[i].v2 << endl;
    }

    // v = 0;

    // while (L)
    // {
    //     cout << L->v << " ";
    //     v ^= 1;
    //     if (!v)
    //         cout << endl;
    //     p = L;
    //     L = L->next;
    //     delete p;
    // }

    // Usuwamy struktury dynamiczne

    return 0;
}
