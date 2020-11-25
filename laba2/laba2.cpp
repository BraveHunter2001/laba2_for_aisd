#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "BoolSet.h"

int Set::N = 32, Set::cnt = 0;
const int q0 = 100000;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    Set A('A'),
        B('B'),
        C('C'),
        D('D'),
        E;
    clock_t begin = clock();

    for (int i = 0; i < q0; i++)
    {
        E = (A | B) & (C & ~D);
    }
    
    clock_t end = clock();

    E.Show();

    cout << "Middle power =" <<
        (A.power() + B.power() + C.power() + E.power()) / 5 <<endl<<
        "Time=" << end - begin << "/" << q0 << endl;
    cin.get();
    //for test
    return 0;
}

