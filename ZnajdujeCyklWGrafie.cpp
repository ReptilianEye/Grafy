#include <iostream>
#include <vector>

using namespace std;

// Funkcja rekurencyjna wyszukująca cykl
//--------------------------------------
bool DFSfindCycle(vector<vector<int>> graf, int v, int w, vector<int> &S, bool *visited)
{
    int u;
    vector<int> p;

    visited[w] = true; // Oznaczamy wierzchołek jako odwiedzony
    p = graf[w];       // Rozpoczynamy przeglądanie sąsiadów
    while (p.empty() == false)
    {
        u = p.back();      // u - numer wierzchołka będącego sąsiadem
        if (u != S.back()) // Pomijamy wierzchołek, z którego przyszliśmy
        {
            S.push_back(w); // Na stos wierzchołek bieżący
            if (u == v)
            {
                return true; // Cykl znaleziony, kończymy
            }
            if (!visited[u] && DFSfindCycle(graf, v, u, S, visited))
            {
                return true;
            }
            S.pop_back();
        }
        p.pop_back();
    }
    return false;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int n, m;
    int i, j, u, v1, v2;
    // slistEl * p, * r, ** listaSasiedztwa;
    vector<int> S;
    cin >> n >> m; // Czytamy liczbę wierzchołków i krawędzi

    //tworzymy liste sasiedztwa i wypelniamy ją pustymi listami
    vector<vector<int>> listaSasiedztwa;
    vector<int> robocza;
    for (i = 0; i < n; i++)
        listaSasiedztwa.push_back(robocza);

    // Odczytujemy kolejne definicje krawędzi
    for (i = 0; i < m; i++)
    {

        cin >> v1 >> v2; // Wierzchołek startowy i końcowy krawędzi
        listaSasiedztwa[v1].push_back(v2);
        //listaSasiedztwa[v2].push_back(v1); //poniewaz graf jest nieskierowany dodajemy krawerdz w druga strone
    }

    cout << endl;

    bool *visited = new bool[n]; // Tworzymy tablicę odwiedzin

    for (i = 0; i < n; i++) // Przechodzimy przez kolejne wierzchołki grafu
    {
        for (j = 0; j < n; j++) // Zerujemy tablicę odwiedzin
            visited[j] = false;

        S.push_back(-1); // Na stos znacznik początku ścieżki

        if (!DFSfindCycle(listaSasiedztwa, i, i, S, visited)) // Szukamy cyklu
        {
            S.pop_back();            // Usuwamy ze stosu początek ścieżki
            cout << i << " - no cycle\n"; // Komunikat
        }
        else
        {
            auto pos = S.begin();
            while (!S.empty()) // Wypisujemy cykl, jeśli istnieje
            {
                u = S.front();
                S.erase(pos); // Pobieramy ze stosu numer wierzchołka
                if (u > -1)
                    cout << u << " "; // i wypisujemy go
            }
            cout << i; // Wypisujemy wierzchołek startowy cyklu
            cout << endl;
        }
    }

    return 0;
}