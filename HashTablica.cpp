#include <iostream>
#include <vector>
#include <map>

using namespace std;


int main()
{
    map<string,int> mapa;
    auto a = make_pair("abc",2);
    mapa.insert(a);
    mapa["abc"]++;
    cout << mapa["abc"];



    return 0;
}