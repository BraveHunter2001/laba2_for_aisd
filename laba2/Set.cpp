#include "Set.h"
#include <iostream>


#pragma region operator overloading
Set& Set::operator &=(const Set& B)
{
	Set C(*this);
	n = 0;
	for (int i = 0; i < C.n; i++)
	{
		for (int j = 0; j < B.n; j++)
		{
			if (C.A[i] == B.A[j]) A[n++] = C.A[i];
		}
	}
	A[n] = 0;
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
	
	for (int i = 0; i < B.n; i++)
	{
		bool f = true;
		for (int j = 0; j < n; j++)
		{
			if (B.A[i] == A[j]) f = false;
		}
		if (f) A[n++] = B.A[i];
	}
	A[n] = 0;
	// std::cout << "RECEIVED " << *this << " = " << S << " | " << B.S << std::endl;
	return *this;
}

Set Set::operator | (const Set & B) const
{
	// std::cout << "CALCULATION " << S << " | " << B.S << std::endl;
	Set C(*this);
	return (C |= B);
}

Set Set::operator~ () const
{
	Set C;
	for (char c = 'À'; c <= 'ß'; c++)
	{
		bool f = true;
		for (int j = 0; j < n; j++)
		{
			if (c == A[j])
			{
				f = false;
				break;
			}
		}

		if (f)
			C.A[C.n++] = c;
	}
	C.A[C.n] = 0;
	// std::cout << "RECEIVED " << C << " = ~" << S << std::endl;
	return C;
}

Set& Set::operator= (const Set& B)
{
	if (this != &B)
	{
		char* dst(A), * src(B.A); 
		n = B.n;
		while (*dst++ = *src++);
		
	}
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
	delete[] A;
}

Set::Set() : n(0), S('A' + cnt++), A(new char[N + 1]) 
{ 
	A[n] = 0;
	// std::cout << "CREATED " << *this << std::endl;
}

Set::Set(char) : n(0), S('A' + cnt++), A(new char[N + 1])
{
	
	for (int i = 0; i < N; i++)
		if (rand() % 2) 
			A[n++] = i + 'À';
	A[n] = 0;
	// std::cout << "CREATED " << *this << std::endl;
}

Set::Set(const Set& B) : S('A' + cnt++), A(new char[N + 1])
{
	char* dst(A), *src(B.A);
	while (*dst++ = *src++);
	(*this).n = B.n;
	// std::cout << "CREATED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(Set&& B) noexcept : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = nullptr;
	// std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(int len) : n(len), S('A' + cnt++), A(new char[N + 1])
{
	Generator(len, A);
	// std::cout << "CREATED " << *this << std::endl;
}

void Set::Show()
{
	std::cout << S << "[" << n << "]" << " = {" << ((A) ? A : "<EMPTY>") << "}";
}

void Set::Generator(int len,  char* arr)
{
	char *uni = new char[N + 1];
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

	for (int i = 0; i < len; i++)
	{
		arr[i] = uni[i];
	}
	arr[len] = 0;

	delete[] uni;
}
void Set::ZeroingCounter()
{
	cnt = 0;
}