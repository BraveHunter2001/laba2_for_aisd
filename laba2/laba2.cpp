//E = A & ~(B | C | D);

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
// #include "SetArray.h"
// #include "SetList.h"
// #include "SetListOth.h"
#include "ControlListSet.h"
// #include "SetMachineWord.h"
int
Set::N = 32,
Set::cnt = 0;
const long number_of_repeats = 100000;

// только для класса-контролерра
int
ST::mup = 0,
ST::mup_spare = 0;
ST ST::list_memory[ST::max_mup];

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(static_cast<unsigned int>(time(nullptr)));
	bool mode;
	cout << "Enter work's mode: ";
	cin >> mode;
	system("cls");
		for (int i = 0; i < 12; ++i) {
			//ST::Clear(); // только для класса-контролерра
			//ST::Mark(); // только для класса-контролерра
			Set
				A(i),
				B(i),
				C(i),
				D(i),
				E;
			cout << A << endl << B << endl << C << endl << D << endl << endl;
			//ST::Mark(); // только для класса-контролерра
			clock_t begin = clock();
			for (long repeat = 0; repeat < number_of_repeats; repeat++) {
				//E = Set(); // только для класса-контролерра
				//ST::Release(); // только для класса-контролерра
				E = A & ~(B | C | D);
			}
			clock_t end = clock();
			//MemoryOutput(); // только для класса-контролерра
			cout << endl << "In result: set - " << E << endl
				<< setw(12) << ' ' << "power of initial set's - " << i << endl <<
				setw(12) << ' ' << "time - "
				<< end - begin << endl << "-----" << endl << endl;
		}
	}

