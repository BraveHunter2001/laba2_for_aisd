#include "Set.h"
#include <iostream>


#pragma region operator overloading
Set& Set::operator &=(const Set& B)
{
	Set C(*this);
	n = 0;
	for (int i = 0; i < C.n; i++)// ++i
	{
		for (int j = 0; j < B.n; j++)
		{
			if (C.A[i] == B.A[j]) A[n++] = C.A[i];
		}
	}
	A[n] = 0;
	return *this;
}

Set Set::operator& (const Set& B)const
{
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
	return *this;
}

Set Set::operator | (const Set & B) const
{
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



Set::Set() : n(0), S('A' + cnt++), A(new char[N + 1]) 
{ 
	A[n] = 0;
}

Set::Set(char) : n(0), S('A' + cnt++), A(new char[N + 1])
{
	
	for (int i = 0; i < N; i++)
		if (rand() % 2) 
			A[n++] = i + 'À';
	A[n] = 0;
	(*this).Show();
}

Set::Set(const Set& B) : S('A' + cnt++), A(new char[N + 1])
{
	char* dst(A), *src(B.A);
	while (*dst++ = *src++);
	(*this).n = B.n;
}

Set::Set(Set&& B) : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = nullptr;
}

Set::Set(int len) : n(len), S('A' + cnt++), A(new char[N + 1])
{
	Generator(len, A);
	(*this).Show();
}

void Set::Show()
{
	std::cout << S << "=[" << A << "]" << '\n';
}

void Set::Generator(int len,  char* arr)
{
	char *uni = new char[N+1];
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
}
