#include "BoolSet.h"

#include <iostream>


#pragma region operator overloading
Set& Set::operator &=(const Set& B)
{
	Set C(*this);
	
	n = 0;
	for (size_t i = 0; i < C.N; i++)
	{
		A[i] = C.A[i] * B.A[i];
	}
	CalcPower();
	// std::cout << "RECEIVED " << *this << " = " << C.S << " & " << B.S << std::endl;
	return *this;
}

Set Set::operator& (const Set& B)const
{
	// std::cout << "CALCULATION " << S << " & " << B.S << std::endl;
	Set C(*this);
	return (C &= B);
}

Set& Set::operator |=(const Set& B)
{

	for (int i = 0; i < B.N; i++)
	{
		A[i] += B.A[i];
	}
	CalcPower();
	// std::cout << "RECEIVED " << *this << " = " << S << " | " << B.S << std::endl;
	return *this;
}

Set Set::operator | (const Set& B) const
{
	// std::cout << "CALCULATION " << S << " | " << B.S << std::endl;
	Set C(*this);
	return (C |= B);
}

Set Set::operator~ () const
{
	Set C;
	for (size_t i = 0; i < N; i++)
	{
		C.A[i] = !A[i];
	}
	C.CalcPower();
	// std::cout << "RECEIVED " << C << " = ~" << S << std::endl;
	return C;
}

Set& Set::operator= (const Set& B)
{
	if (this != &B)
	{
		for (size_t i = 0; i < N; i++)
		{
			A[i] = B.A[i];
		}

	}
	CalcPower();
	// std::cout << "RECEIVED " << *this << " FROM " << B.S << std::endl;
	return *this;
}

Set& Set::operator= (Set&& B) noexcept
{
	if (this != &B)
	{
		n = B.n;
		A = B.A;

		B.A = nullptr;
	}
	// std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
	return *this;
}

std::ostream& operator<< (std::ostream& os, Set& set) {
	set.Show();

	return os;
}

#pragma endregion

Set::~Set() { 
	// std::cout << "DELETED " << *this << std::endl;
	delete[] A; }

Set::Set() : n(0), S('A' + cnt++), A(new bool[N])
{
	for (size_t i = 0; i < N; i++)
	{
		A[i] = false;
	}
	// std::cout << "CREATED " << *this << std::endl;
}

Set::Set(char) : n(0), S('A' + cnt++), A(new bool[N])
{

	for (int i = 0; i < N; i++)
		if (rand() % 2)
		{
			A[i] = true;
			n++;
		}
		else
			A[i] = false;
	// std::cout << "CREATED " << *this << std::endl;
}

Set::Set(const Set& B) : S('A' + cnt++), A(new bool[N])
{
	for (size_t i = 0; i < N; i++)
	{
		A[i] = B.A[i];
	}
	(*this).n = B.n;
	// std::cout << "CREATED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(Set&& B) noexcept : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = nullptr;
	// std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(int len) : n(len), S('A' + cnt++), A(new bool[N])
{
	Generator(len, A);
	// std::cout << "CREATED " << *this << std::endl;
}

void Set::Show()
{
	std::cout << S << "[" << n << "] = {";

	if (n) {
		for (size_t i = 0; i < N; i++)
		{
			if (A[i])
				std::cout << (char)('À' + i);
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
		if (A[i])
			tempCount++;
	}
	n = tempCount;
}

void Set::Generator(int len, bool* arr)
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
	for (size_t i = 0; i < N; i++)
	{
		arr[i] = 0;
	}
	for (size_t i = 0; i < len; ++i) {
		arr[uni[i] -'À'] = true;
	}

	delete[] uni;
}
void Set::ZeroingCounter()
{
	cnt = 0;
}