#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list sąsiedztwa i listy mostów

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n, m, cv;                 // Liczba wierzchołków, krawędzi, numeracja
slistEl ** graf;              // Tablica list sąsiedztwa
int *D;                       // Numery DFS
slistEl * L;                  // Lista mostów

// Funkcja rekurencyjna wyszukująca mosty
// v  - numer bieżącego wierzchołka
// vf - ojciec bieżącego wierzchołka na drzewie rozpinającym
// Reszta parametrów to zmienne globalne
//----------------------------------------------------------
int DFSb ( int v, int vf )
{
  int Low, temp, u;
  slistEl * p;

  // Numerujemy wierzchołek, ustalamy wstępną wartość Low oraz zwiększamy numerację

  D [ v ] = Low = cv++;

  for( p = graf [ v ]; p; p = p->next ) // Przeglądamy listę sąsiadów
  {
    u = p->v;                 // u - numer wierzchołka sąsiada
    if( u != vf )             // u nie może być ojcem v
    {
      if( !D [ u ] )          // Jeśli sąsiad u nie był odwiedzany, to
      {
        temp = DFSb ( u, v ); // rekurencyjnie odwiedzamy go
        if( temp < Low ) Low = temp;
      }
      else if( D [ u ] < Low ) Low = D [ u ];
    }
  }

  // Wszyscy sąsiedzi zostali odwiedzeni. Teraz robimy test na most

  if( ( vf > -1 ) && ( Low == D [ v ] ) )
  {
    p = new slistEl;       // Mamy most. Dodajemy go do listy L
    p->v = v;
    p->next = L;
    L = p;
    p = new slistEl;
    p->v = vf;
    p->next = L;
    L = p;
  }

  return Low;              // Wynik
}

// **********************
// *** Program główny ***
// **********************

int main( )
{
  int i, u, v;             // Numery wierzchołków
  slistEl *p, *r;

  cin >> n >> m;           // Odczytujemy liczbę wierzchołków i krawędzi

  graf = new slistEl * [ n ]; // Tworzymy zmienne dynamiczne
  D = new int [ n ];
  L = NULL;

  for( i = 0; i < n; i++ )
  {
    graf [ i ] = NULL;
    D [ i ]    = 0;
  }

  // Odczytujemy kolejne definicje krawędzi

  for( i = 0; i < m; i++ )
  {
    cin >> v >> u;          // Wierzchołki tworzące krawędź
    p = new slistEl;        // Tworzymy nowy element
    p->v = u;               // Numerujemy go jako w
    p->next = graf [ v ];   // Dodajemy go na początek listy graf [ v ] 
    graf [ v ] = p;
    p = new slistEl;        // To samo dla krawędzi w drugą stronę
    p->v = v;
    p->next = graf [ u ];
    graf [ u ] = p;
  }

  // Szukamy mostów

  for( i = 0; i < n; i++ )
    if( !D [ i ] )          // Szukamy nieodwiedzonego wierzchołka
    {
      cv   = 1;             // Początek numeracji DFS
      DFSb ( i, -1 );       // Szukamy mostów
    }

  cout << endl;

  // Wypisujemy znalezione mosty

  v = 0;

  while( L )
  {
    cout << L->v << " ";
    v ^= 1;
    if( !v ) cout << endl;
    p = L;
    L = L->next;
    delete p;
  }

  // Usuwamy struktury dynamiczne

  delete [ ] D;

  for( i = 0; i < n; i++ )
  {
    p = graf [ i ];
    while( p )
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete graf;

  return 0;
}
 