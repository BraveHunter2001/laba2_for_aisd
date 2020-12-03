#include <iostream>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include "BoolSet.h"

using namespace std;

int Set::N = 32, Set::cnt = 0;
const long q0 = 100000;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(nullptr));
    
        
        for (long repeat = 0; repeat < 2; repeat++)
        {
            Set A('s'), B('s'), C('s'), D('s'), E;
            E = A & ~(B | C | D);
            cout << E;
            cout << "Power of result = " << E.power() << '\n';
        }
    return 0;
}
