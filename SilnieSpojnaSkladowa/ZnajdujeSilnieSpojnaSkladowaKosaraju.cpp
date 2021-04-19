#include <iostream>
#include <vector>

using namespace std;

// Typy danych
vector<vector<int>> listaSasiedztwa; // Tablica list sąsiedztwa
vector<int> StosOdwiedzonych;
bool *visited;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
void TranspozycjaGrafu()
{
    vector<vector<int>> listaSasiedztwaTransponowana;
    vector<int> a;
    for (int i = 0; i < listaSasiedztwa.size(); i++)
        listaSasiedztwaTransponowana.push_back(a);

    for (int i = 0; i < listaSasiedztwa.size(); i++)
    {
        for (int j = 0; j < listaSasiedztwa[i].size(); i++)
        {
            listaSasiedztwaTransponowana[listaSasiedztwa[i][j]].push_back(i);
        }
    }
    listaSasiedztwa = listaSasiedztwaTransponowana;
}
void DFS(int v, bool CzyWypisuje)
{
    if (CzyWypisuje)
        cout << v << " ";
    visited[v] = true;
    for (int i = 0; i < listaSasiedztwa[v].size(); i++)
    {
        if (!visited[listaSasiedztwa[v][i]])
        {
            DFS(listaSasiedztwa[v][i], CzyWypisuje);
        }
    }
    StosOdwiedzonych.push_back(v);
}

int main()
{
    int wierzcholek, n, m;
    int x, y, w;
    int i, j, u;

    cin >> n >> m; //wczytanie liczby wierzcholkow i krawedzi

    // Tworzymy tablice dynamiczne
    visited = new bool[n + 1]{false}; //n+1 na wypadek gdybym liczyl wierzcholki od 1
    vector<int> a;                      //robocza lista aby wypelnic czyms liste sasiedztwa
    for (int i = 0; i < n + 1; i++)
    {
        listaSasiedztwa.push_back(a);
    }

    // Odczytujemy dane wejściowe
    for (i = 0; i < m; i++)
    {
        cin >> x >> y; // Odczytujemy krawędź z wagą

        listaSasiedztwa[x].push_back(y); // Element dołączamy do listy
    }
    for (int i = 0; i < listaSasiedztwa.size(); i++)
    {
        if (!visited[i] && !listaSasiedztwa[i].empty())
            DFS(i, false);
    }
    TranspozycjaGrafu();
    for (int i = 0; i < sizeof(visited); i++)
        visited[i] = false;
    int iloscSilnieSpojnychSkladowych = 0;
    while (!StosOdwiedzonych.empty())
    {
        int v = StosOdwiedzonych.back();
        StosOdwiedzonych.pop_back();
        if (!visited[v])
        {
            iloscSilnieSpojnychSkladowych++;
            cout << "Spojna skladowa: ";
            DFS(v, true);
            cout << endl;
        }
    }
    cout << iloscSilnieSpojnychSkladowych << endl;

    return 0;
}
