#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int MAXINT = -2147483647;
int n;
// Procedura szukania ścieżki
// vs - numer wierzchołka startowego
// vk - numer wierzchołka końcowego
//----------------------------------
void BFS_Path(int vs, int vk, vector<vector<int>> graf)
{
    vector<int> Q;
    int v, u, i;

    bool CzyZnalezlismySciezke = false;
    bool *visited = new bool[n]; // Tworzymy tablice odwiedzin

    for (i = 0; i < n; i++) // Tablicę visited zerujemy
        visited[i] = false;

    int *P = new int[n]; // Tworzymy tablicę ścieżki

    P[vs] = -1;

    Q.push_back(vs); // W kolejce umieszczamy wierzchołek startowy

    visited[vs] = true; // i oznaczamy go jako startowy

    while (!Q.empty())
    {
        v = Q.front(); // Pobieramy z kolejki wierzchołek v
        Q.erase(Q.begin());

        if (v == vk) // Sprawdzamy koniec ścieżki
        {
            CzyZnalezlismySciezke = true; // Zaznaczamy sukces
            break;                        // Przerywamy pętlę
        }

        // Przeglądamy sąsiadów wierzchołka v

        for (int k = 0; k < graf[v].size(); k++)
        {
            u = graf[v][k];
            if (!visited[u])
            {
                P[u] = v;          // W P zapisujemy fragment ścieżki
                Q.push_back(u);    // Sąsiad zostaje umieszczony w kolejce
                visited[u] = true; // i oznaczony jako odwiedzony
            }
        }
    }

    if (!CzyZnalezlismySciezke)
        cout << "BRAK"; // Ścieżka nie została znaleziona
    else
        while (v > -1)
        {
            cout << setw(3) << v; // Wypisujemy wierzchołki ścieżki
            v = P[v];             // Cofamy się do poprzedniego wierzchołka ścieżki
        }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int m, i, v1, v2;

    cin >> n >> m; // Czytamy liczbę wierzchołków i krawędzi

    vector<vector<int>> graf; //graf reprezentowany jako lista siasiedztwa

    // Tablicę wypełniamy pustymi listami
    vector<int> a;

    for (i = 0; i < n; i++)
    {
        graf.push_back(a);
    }
    // Odczytujemy kolejne definicje krawędzi

    for (i = 0; i < m; i++)
    {
        cin >> v1 >> v2; // Wierzchołek startowy i końcowy krawędzi
        graf[v1].push_back(v2);
    }

    // Odczytujemy wierzchołek startowy i końcowy ścieżki

    cin >> v1 >> v2;

    cout << endl;

    BFS_Path(v1, v2, graf); // Szukamy ścieżki

    cout << endl;

    return 0;
}
