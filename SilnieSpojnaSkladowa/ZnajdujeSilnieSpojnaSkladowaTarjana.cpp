#include <iostream>
#include <vector>
using namespace std;

const int _maxN = 100000;

vector<int> listaSasiedztwa[_maxN];

int low[_maxN];
int visited[_maxN];
int licznikDFS = 0;

int DFSTarjan(int v)
{
    licznikDFS++;
    visited[v] = true;
    low[v] = licznikDFS;

    int tLow = licznikDFS;
    for (int i = 0; i < listaSasiedztwa[v].size(); i++)
    {
        int n = listaSasiedztwa[v][i];
        if (!visited[n])
            tLow = min(tLow, DFSTarjan(n));
        else
            tLow = min(tLow, low[n]);
    }

    low[v] = tLow;
    return tLow;
}

bool isVis[_maxN];
int main()
{
    int n, m;
    cin >> n >> m;

    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        listaSasiedztwa[a].push_back(b);
    }

    for (int i = 0; i <= _maxN; i++)
        if (!visited[i] && !listaSasiedztwa[i].empty())   //TO DO ZMIENIC WSZEDZIE TABLICE NA ILOSC WIERZCHOLKOW A NIE MAX INT
            DFSTarjan(i);

    int temp = n;
    for (int i = 1; i <= _maxN; i++)
        if (!isVis[low[i]])
            isVis[low[i]] = true;
        else
            temp--;

    cout << temp;
}
