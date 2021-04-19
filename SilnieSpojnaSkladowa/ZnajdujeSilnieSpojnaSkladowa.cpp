// Wyznaczanie silnie spójnych składowych
// Algorytm Korsaraju
// Data: 26.01.2014
// (C)2014 mgr Jerzy Wałaszek
//---------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list sąsiedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowująca stos

  public:
    stack( );      // konstruktor
    ~stack( );     // destruktor
    bool empty ( void );
    int  top ( void );
    void push ( int v );
    void pop ( void );
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack( )
{
  S = NULL;
}

// Destruktor - zwalnia tablicę dynamiczną
//----------------------------------------
stack::~stack( )
{
  while( S ) pop( );
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty ( void )
{
  return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top ( void )
{
  return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push ( int v )
{
  slistEl * e = new slistEl;
  e->v    = v;
  e->next = S;
  S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop ( void )
{
  if( S )
  {
    slistEl * e = S;
    S = S->next;
    delete e;
  }
}

// Przechodzi graf algorytmem DFS, umieszczając na stosie
// napotkane po drodze wierzchołki.
// v       - numer wierzchołka startowego
// visited - tablica odwiedzin
// S       - stos
// graf    - tablica list sąsiedztwa
//--------------------------------------------------------
void DFSstack ( int v, bool * visited, stack & S, slistEl ** graf )
{
  slistEl * p;

  visited [ v ] = true;          // Oznaczamy v jako odwiedzony

  // Przeglądamy sąsiadów v
  for( p = graf [ v ]; p; p = p->next )
    if( !visited [ p->v ] ) DFSstack ( p->v, visited, S, graf );

  S.push ( v );
}

// Wyświetla wierzchołki kolejno odwiedzane przez DFS
// v       - wierzchołek startowy
// visited - tablica odwiedzin
// graf    - tablica list sąsiedztwa
//---------------------------------------------------
void DFSprint ( int v, bool * visited, slistEl ** graf )
{
  slistEl * p;

  visited [ v ] = true;
  cout << setw ( 3 ) << v;
  for( p = graf [ v ]; p; p = p->next )
    if( !visited [ p->v ] ) DFSprint ( p->v, visited, graf );
}

// **********************
// *** Program główny ***
// **********************

int main( )
{
  int n, m;                      // Liczba wierzchołków i krawędzi
  slistEl **A, **AT;             // Tablice list sąsiedztwa
  bool * visited;
  stack S;
  int i, v, u, cn;
  slistEl *p, *r;

  cin >> n >> m;                 // Odczytujemy liczbę wierzchołków i krawędzi

  A  = new slistEl * [ n ];      // Tworzymy tablice dynamiczne
  AT = new slistEl * [ n ];

  // Inicjujemy tablice

  for( i = 0; i < n; i++ ) A [ i ] = AT [ i ] = NULL;

  // Odczytujemy kolejne definicje krawędzi.

  for( i = 0; i < m; i++ )
  {
    cin >> v >> u;               // Wierzchołki tworzące krawędź
    p = new slistEl;             // Tworzymy nowy element
    p->v = u;                    // Numerujemy go jako u
    p->next = A [ v ];           // i dodajemy na początek listy graf [ v ] 
    A [ v ] = p;
  }

  cout << endl;

  // Wyznaczamy silnie spójne składowe

  visited = new bool [ n ];      // Tworzymy tablicę odwiedzin
  for( i = 0; i < n; i++ )       // i wypełniamy ją wartościami false
    visited [ i ] = false;

  for( v = 0; v < n; v++ )       // Przeglądamy kolejne wierzchołki grafu
    if( !visited [ v ] ) DFSstack ( v, visited, S, A );

  // Transponujemy graf

  for( v = 0; v < n; v++ )       // Przeglądamy kolejne wierzchołki
    // Przeglądamy sąsiadów v
    for( p = A [ v ]; p; p = p->next )
    {
      r = new slistEl;           // Tworzymy nowy element listy
      r->v = v;                  // Zapamiętujemy w nim wierzchołek v
      r->next = AT [ p->v ];     // i dodajemy do listy sąsiada
      AT [ p->v ] = r;
    }

  for( v = 0; v < n; v++ )       // Zerujemy tablicę odwiedzin
    visited [ v ] = false;

  cn = 0;                        // Inicjujemy licznik składowych

  while( !S.empty( ) )           // Przetwarzamy wierzchołki ze stosu
  {
    v = S.top( ); S.pop( );      // Pobieramy wierzchołek ze stosu
    if( !visited [ v ] )
    {
      cout << "SCC" << setw ( 3 ) << ++cn << ":";
      DFSprint ( v, visited, AT );
      cout << endl;
    }
  }

  // Usuwamy tablice dynamiczne

  for( i = 0; i < n; i++ )
  {
    p = A [ i ];
    while( p )
    {
      r = p;
      p = p->next;
      delete r;
    }
    p = AT [ i ];
    while( p )
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [ ] A;
  delete [ ] AT;
  delete [ ] visited;

  return 0;
} 