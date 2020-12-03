#include "MachineWordSet.h"
#include <iostream>


#pragma region operator overloading
Set& Set::operator &=(const Set& B)
{
	Set C(*this);

	n = 0;
	A = A & B.A;
	CalcPower();
	return *this;
}

Set Set::operator& (const Set& B)const
{
	Set C(*this);
	return (C &= B);
}

Set& Set::operator |=(const Set& B)
{

	A = A | B.A;
	CalcPower();
	return *this;
}

Set Set::operator | (const Set& B) const
{
	Set C(*this);
	return (C |= B);
}

Set Set::operator~ () const
{
	Set C;
	C.A = ~A;
	C.CalcPower();
	return C;
}

Set& Set::operator= (const Set& B)
{
	if (this != &B)
	{
		A = B.A;
	}
	CalcPower();
	return *this;
}

Set& Set::operator= (Set&& B)
{
	if (this != &B)
	{
		n = B.n;
		A = B.A;

		B.A = 0;
	}
	return *this;
}

std::ostream& operator<< (std::ostream& os, Set& set) {
	set.Show();

	return os;
}

#pragma endregion



Set::Set() : n(0), S('A' + cnt++), A(0)
{
	
}

Set::Set(char) : n(0), S('A' + cnt++), A(0)
{

	A = rand() % 0x3FF;
	CalcPower();
	(*this).Show();
}


Set::Set(const Set& B) : S('A' + cnt++)
{
	A = B.A;
	(*this).n = B.n;
}

Set::Set(Set&& B) : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = 0;
}

Set::Set(int len) : n(len), S('A' + cnt++), A(0)
{
	Generator(len, &A);
	(*this).Show();
}

void Set::Show()
{
	std::cout << S << "=[";

	int one = 1;
	for (size_t i = 0; i < N; ++i) {
		if (A & one << i) {
			std::cout << (unsigned char)(i + SHIFT);
		}
	}
	std::cout << "]" << " Power: " << n << '\n';

}

void Set::CalcPower()
{
	int tempCount = 0;
	for (size_t i = 0; i < N; i++)
	{
		if (A & 1 << i)
			tempCount++;
	}
	n = tempCount;
}

void Set::Generator(int len, int* arr)
{
	char* uni = new char[N + 1];
	uni[N] = 0;
	for (int i = 0; i < N; i++)
	{
		uni[i] = 'À' + i;
	}

	for (int i = 0; i < len; i++)
	{
		int p = rand() % (N - i);
		if (p)
		{
			std::swap(uni[p + i], uni[i]);
		}
	}
	
	for (size_t i = 0; i < len; ++i) {
		*arr = *arr | 1 << (uni[i] - SHIFT);
	}


	delete[] uni;
}

void Set::ZeroingCounter()
{
	cnt = 0;
}