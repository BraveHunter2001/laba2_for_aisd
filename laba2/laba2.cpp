#include <iostream>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "ListSet.h"

using namespace std;

int Set::N = 32, Set::cnt = 0;
const long q0 = 100000;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(nullptr));
    for (int i = 0; i < 12; ++i) {
        cout << "Power = " << i << '\n';
        Set A(i), B(i), C(i), D(i), E;
        E = A & ~(B | C | D);
        E.Show();
        cout << "Power of result = " << E.power() << '\n';
    }
    return 0;
}
