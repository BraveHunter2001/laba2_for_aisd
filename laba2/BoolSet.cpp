#include "BoolSet.h"

#include <iostream>
#include <random>


#pragma region operator overloading
Set& Set::operator &=(const Set& B)
{
	Set C(*this);
	
	n = 0;
	for (size_t i = 0; i < C.N; i++)
	{
		A[i] = C.A[i] * B.A[i];
	}
	
	return *this;
}

Set Set::operator& (const Set& B)const
{
	Set C(*this);
	return (C &= B);
}

Set& Set::operator |=(const Set& B)
{

	for (int i = 0; i < B.N; i++)
	{
		A[i] += B.A[i];
	}
	
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
	for (size_t i = 0; i < N; i++)
	{
		C.A[i] = !A[i];
	}
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
	return *this;
}

Set& Set::operator= (Set&& B)
{
	if (this != &B)
	{
		n = B.n;
		A = B.A;

		B.A = nullptr;
	}
	return *this;
}

#pragma endregion



Set::Set() : n(0), S('A' + cnt++), A(new bool[N])
{
	for (size_t i = 0; i < N; i++)
	{
		A[i] = false;
	}
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
	(*this).Show();
}

Set::Set(const Set& B) : S('A' + cnt++), A(new bool[N])
{
	for (size_t i = 0; i < N; i++)
	{
		A[i] = B.A[i];
	}
	(*this).n = B.n;
}

Set::Set(Set&& B) : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = nullptr;
}

Set::Set(int len) : n(len), S('A' + cnt++), A(new bool[N])
{
	Generator(len, A);
	(*this).Show();
}

void Set::Show()
{
	std::cout << S << "=[";

	for (size_t i = 0; i < N; i++)
	{
		if (A[i])
			std::cout << (char)('À' + i);
	}
	std::cout << "]" << '\n';

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


}
