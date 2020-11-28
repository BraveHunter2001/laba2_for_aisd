#include "ListSet.h"
#include <iostream>

Set::Set() : n(0), S('A' + cnt++), A(new ST(0, nullptr)) {};

Set::Set(char) : n(0), S('A' + cnt++), A(new ST(0, nullptr))
{
	for (int i = 0; i < N; i++)
		if (rand() % 2)
			A = new ST(i + '�', A);
	(*this).Show();
}

Set::Set(const Set& B) : S('A' + cnt++), A(new ST(0, nullptr))
{
	ST* src(B.A);
	while (src) {
		A = new ST(src->letter, A);
		src = src->next;
	}
	(*this).n = B.n;
}

Set::Set(Set&& B) noexcept : S('A' + cnt++), n(B.n), A(B.A)
{
	B.A = nullptr;
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
	return *this;
}

Set Set::operator& (const Set& B)const
{
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
	for (char c = '�'; c <= '�'; c++)
		if (!isInSet(c)) {
			C.A = new ST(c, C.A);
			C.n++;
		}
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
	return *this;
}

Set::Set(int len) : n(len), S('A' + cnt++) {
	Generator(len, A);
	(*this).Show();
}

void Set::Show() {
	std::cout << S << "=[";
	ST* T = A;
	while (T) {
		std::cout << T->letter;
		T = T->next;
	}
	std::cout << ']' << '\n';

}

void Set::Generator(int len, ST* set) {
	char* uni = new char[N + 1];
	uni[N] = 0;
	for (int i = 0; i < N; i++)
	{
		uni[i] = '�' + i;
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
