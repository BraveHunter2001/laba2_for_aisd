#include "ListSet.h"
#include <iostream>

Set::Set() : n(0), S('A' + cnt++), A(nullptr) {
	 std::cout << "CREATED " << *this << std::endl;
}

Set::Set(char) : n(0), S('A' + cnt++), A(nullptr)
{
	for (int i = 0; i < N; i++)
		if (rand() % 2)
			A = new ST(i + 'À', A);
	 std::cout << "CREATED " << *this << std::endl;
}

Set::Set(const Set& B) : S('A' + cnt++), A(nullptr)
{
	ST* src(B.A);
	while (src) {
		A = new ST(src->letter, A);
		src = src->next;
	}
	(*this).n = B.n;
	 std::cout << "CREATED " << *this << " FROM " << B.S << std::endl;
}

Set::Set(Set&& B) noexcept : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = nullptr;
	 std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
}

bool Set::isInSet(unsigned char item) const {
	ST* x = A;
	while (x) {
		if ((x->letter == item) && x->letter != 0) {
			return true;
		}
		x = x->next;
	}

	return false;
}

Set& Set::operator |=(const Set& B)
{
	for (ST* z = B.A; z; z = z->next) {
		if (!isInSet(z->letter)) {
			A = new ST(z->letter, A);
			n++;
		}
	}
	 std::cout << "RECEIVED " << *this << " = " << S << " | " << B.S << std::endl;
	return *this;
}

Set Set::operator& (const Set& B)const
{
	 std::cout << "CALCULATION " << S << " & " << B.S << std::endl;
	Set C(*this);
	return (C &= B);
}

Set& Set::operator &=(const Set& B)
{
	Set C(*this);
	delete A;
	A = nullptr;
	n = 0;
	for (ST* z = B.A; z; z = z -> next) {
		if (C.isInSet(z->letter)) {
			A = new ST(z->letter, A);
			n++;
		}
	}
	 std::cout << "RECEIVED " << *this << " = " << C.S << " & " << B.S << std::endl;
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
	for (char c = 'À'; c <= 'ß'; c++)
		if (!isInSet(c)) {
			C.A = new ST(c, C.A);
			C.n++;
		}
	 std::cout << "RECEIVED " << C << " = ~" << S << std::endl;
	return C;
}

Set& Set::operator= (const Set& B)
{
	if (this != &B) {
		ST* src(B.A);
		delete A;
		A = nullptr;
		while (src->letter) {
			A = new ST(src->letter, A);
			src = src->next;
		}
		(*this).n = B.n;
	}
	 std::cout << "RECEIVED " << *this << " FROM " << B.S << std::endl;
	return *this;
}

Set& Set::operator= (Set&& B) noexcept
{
	if (this != &B)
	{
		delete A;
		n = B.n;
		A = B.A;

		B.A = nullptr;
	}
	std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
	return *this;
}

Set::Set(int len) : n(len), S('A' + cnt++) {
	Generator(len, A);
	 std::cout << "CREATED " << *this << std::endl;
}

void Set::Show() {
	std::cout << S << "[" << n << "] = {";
	if (A != nullptr) {
		ST* T = A;
		while (T) {
			std::cout << T->letter;
			T = T->next;
		}
	}
	else std::cout << "<EMPTY>";
	std::cout << '}';

}

void Set::Generator(int len, ST* set) {
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

	A = new ST(0, A);

	for (int i = 0; i < len; i++)
	{
		A = new ST(uni[i], A);
	}

	delete[] uni;
}

std::ostream& operator<< (std::ostream & os, Set& set) {
	set.Show();

	return os;
}
void Set::ZeroingCounter()
{
	cnt = 0;
}

Set::~Set() { std::cout << "DELETED " << *this << std::endl;
	delete A; }