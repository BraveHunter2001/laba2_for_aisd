#include "MachineWordSet.h"
#include <iostream>


#pragma region operator overloading
Set& Set::operator &=(const Set& B)
{
	Set C(*this);

	n = 0;
	A = A & B.A;
	CalcPower();
	std::cout << "RECEIVED " << *this << " = " << C.S << " & " << B.S << std::endl;
	return *this;
}

Set Set::operator& (const Set& B)const
{
	std::cout << "CALCULATION " << S << " & " << B.S << std::endl;
	Set C(*this);
	return (C &= B);
}

Set& Set::operator |=(const Set& B)
{

	A = A | B.A;
	CalcPower();
	std::cout << "RECEIVED " << *this << " = " << S << " | " << B.S << std::endl;
	return *this;
}

Set Set::operator | (const Set& B) const
{
	std::cout << "CALCULATION " << S << " | " << B.S << std::endl;
	Set C(*this);
	return (C |= B);
}

Set Set::operator~ () const
{
	Set C;
	C.A = ~A;
	C.CalcPower();
	std::cout << "RECEIVED " << C << " = ~" << S << std::endl;
	return C;
}

Set& Set::operator= (const Set& B)
{
	if (this != &B)
	{
		A = B.A;
	}
	CalcPower();
	std::cout << "RECEIVED " << *this << " FROM " << B.S << std::endl;
	return *this;
}

Set& Set::operator= (Set&& B) noexcept
{
	if (this != &B)
	{
		n = B.n;
		A = B.A;

		B.A = 0;
	}
	std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
	return *this;
}

std::ostream& operator<< (std::ostream& os, Set& set) {
	set.Show();

	return os;
}

#pragma endregion

Set::~Set() { 
	std::cout << "DELETED " << *this << std::endl;
}

Set::Set() : n(0), S('A' + cnt++), A(0)
{
	std::cout << "CREATED " << *this << std::endl;
}

Set::Set(char) : n(0), S('A' + cnt++), A(0)
{

	A = rand() % 0x3FF;
	CalcPower();
	std::cout << "CREATED " << *this << std::endl;
}


Set::Set(const Set& B) : S('A' + cnt++)
{
	A = B.A;
	(*this).n = B.n;
	std::cout << "CREATED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(Set&& B) noexcept : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = 0;
	std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(int len) : n(len), S('A' + cnt++), A(0)
{
	Generator(len, &A);
	std::cout << "CREATED " << *this << std::endl;
}

void Set::Show()
{
	std::cout << S << "[" << n << "] = {";

	if (n) {
		int one = 1;
		for (size_t i = 0; i < N; ++i) {
			if (A & one << i) {
				std::cout << (unsigned char)(i + SHIFT);
			}
		}
	}
	else std::cout << "<EMPTY>";
	std::cout << "}";

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