#include <iostream>
#include <vector>

using namespace std;

// Typy danych

// Zmienne globalne
//-----------------
int sptr, *S;

vector<vector<int>> graf;
vector<int> stos;

// kolory wierzchołków
const char WHITE = 0; //wierzcholek ani razu nie przerobiony
const char GRAY = 1;  //wierzcholek ktory jest w trakcie przerabiania przez DFS
const char GREEN = 2; //wierzcholek przerobiony (skonczony)

// Rekurencyjna funkcja dokonująca sortowania topologicznego
// v - wierzchołek startowy
//----------------------------------------------------------
bool DFStsort(int v, char *visited)
{

    if (visited[v] == GRAY) // Sprawdzamy, czy nie ma cyklu
    {
        cout << "\nNOT A DAG\n\n"; // Jest cykl - sortowanie topologiczne
        return false;              // nie może zostać wykonane
    }
    if (visited[v] == WHITE) // Jeśli wierzchołek jest biały,
    {
        visited[v] = GRAY;                       // to kolorujemy go na szaro
        for (int i = 0; i < graf[v].size(); i++) // i przeglądamy wszystkich sąsiadów
            if (!DFStsort(graf[v][i], visited))
                return false; // Wywołanie rekurencyjne
        visited[v] = GREEN;   // Wierzchołek kolorujemy na zielono
        stos.push_back(v);    // i umieszczamy go na stosie
    }
    return true; // Kończymy z wynikiem true
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int n, m, i, v1, v2;
    cin >> n >> m; // Czytamy liczbę wierzchołków i krawędzi

    // Tworzymy tablice dynamiczne
    char *visited = new char[n];
    vector<int> tym;
    for (i = 0; i < n; i++)
    {
        graf.push_back(tym);
        visited[i] = WHITE; // Wierzchołki kolorujemy na biało
    }

    // Odczytujemy definicje krawędzi grafu

    for (i = 0; i < m; i++)
    {
        cin >> v1 >> v2;
        graf[v1].push_back(v2);
    }

    cout << endl;

    // Wykonujemy sortowanie topologiczne grafu

    for (i = 0; i < n; i++)
        if (visited[i] == WHITE)
        {
            if (!DFStsort(i, visited))
                break;
        }

    // Wypisujemy wyniki

    if (stos.size() == n)
        while (!stos.empty())
        {
            cout << stos.back() << " ";
            stos.pop_back();
        }
    cout << endl;

    return 0;
}
