#include <iostream>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <ctime>
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
        clock_t begin = clock();
        for (long repeat = 0; repeat < q0; repeat++)
            E = A & ~(B | C | D);
        clock_t end = clock();
        E.Show();
        cout << "Power of result = " << E.power() << '\n';
        cout << "Time = " << end - begin << endl;
    }
    return 0;
}
