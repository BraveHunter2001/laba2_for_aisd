#include "ControlListSet.h"
#include <iostream>
// проверка наличия элемента в множестве;
bool Set::IsInSet(char element) const {
	for (ST* p = A; p; p = p->next) {
		if (element == p->letter) {
			return true;
		}
	}
	return false;
}
// конструктор множества
Set::Set(int _power) :
	S('A' + cnt++),
	n(_power),
	A(nullptr)
{
	Generator(n, A);
	// std::cout << "CREATED " << *this << std::endl;
}
// конструктор — по умолчанию
Set::Set() :
	n(0),
	S('A' + cnt++),
	A(nullptr)
{
	// std::cout << "CREATED " << *this << std::endl;
}
// конструктор копии
Set::Set(const Set& S) :
	S('A' + cnt++),
	n(S.n),
	A(nullptr)
{
	for (ST* p = S.A; p; p = p->next) {
		A = new ST(p->letter, A);
	}
	// std::cout << "CREATED " << *this << " FROM " << S.tag << std::endl;
}
// конструктор копирования с переносом
Set::Set(Set&& S) noexcept :
	S('A' + cnt++),
	n(S.n),
	A(S.A)
{
	S.A = nullptr;
	// std::cout << "BECOMED " << *this << " FROM " << S.tag << std::endl;
}
// деструктор множества
Set::~Set() {
		// std::cout << "DELETED " << *this << std::endl;
		A->ST::~ST();
}
// присваивание
Set& Set::operator=(const Set& S) {
	if (this != &S) {
		// std::cout << "DELETED LIST-SET {" << set << "} FROM " << tag << " BUT NOT OBJECT" << std::endl;
		delete A;
		A = nullptr;
		n = S.n;
		for (ST* p = S.A; p; p = p->next) {
			A = new ST(p->letter, A);
		}
	}
	// std::cout << "RECEIVED " << *this << " FROM " << S.tag << std::endl;
	return *this;
}
// присваивание с переносом
Set& Set::operator=(Set&& S) noexcept {
	if (this != &S) {
		// std::cout << "DELETED LIST-SET {" << set << "} FROM " << tag << " BUT NOT OBJECT" << std::endl;
		delete A;
		n = S.n;
		A = S.A;
		S.A = nullptr;
	}
	// std::cout << "BECOMED " << *this << " FROM " << S.tag << std::endl;
	return *this;
}
// объединение с присваиванием
Set& Set:: operator|=(const Set& rS) {
	for (ST* p = rS.A; p; p = p->next) {
		if (!IsInSet(p->letter)) {
			A = new ST(p->letter, A);
		}
	}
	// std::cout << "RECEIVED " << *this << " = " << tag << " | " << rS.tag << std::endl;
	return *this;
}
// объединение
Set Set:: operator|(const Set& rS) const {
	// std::cout << "CALCULATION " << tag << " | " << rS.tag << std::endl;
	Set lS(*this);
	return (lS |= rS);
}
// пересечение с присваиванием
Set& Set::operator&=(const Set& rS) {
	Set lS(*this);
	// std::cout << "DELETED LIST-SET {" << set << "} FROM " << tag << " BUT NOT OBJECT" << std::endl;
	delete A;
	A = nullptr;
	n = 0;
	for (ST* p = rS.A; p; p = p->next) {
		if (lS.IsInSet(p->letter)) {
			A = new ST(p->letter, A);
			++n;
		}
	}
	// std::cout << "RECEIVED " << *this << " = " << lS.tag << " & " << rS.tag << std::endl;
	return *this;
}
// пересечение
Set Set::operator&(const Set& rS) const {
	// std::cout << "CALCULATION " << tag << " & " << rS.tag << std::endl;
	Set lS(*this);
	return (lS &= rS);
}
// дополнение до универсума
Set Set::operator~() const {
	Set S;
	for (char c = 'A'; c <= 'Z'; ++c) {
		if (!IsInSet(c)) {
			S.A = new ST(c, S.A);
		}
	}
	// std::cout << "RECEIVED " << S << " = ~" << tag << std::endl;
	return S;
}

std::ostream& operator<<(std::ostream& os, Set& S) {
	S.Show();
	return os;
}

void Set::Generator(int len, ST* set) {
	char* uni = new char[N + 1];
	uni[N] = 0;
	for (int i = 0; i < N; i++)
	{
		uni[i] = 'А' + i;
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

void Set::Show() {
	std::cout << S << "=[";
	ST* T = A;
	while (T) {
		std::cout << T->letter;
		T = T->next;
	}
	std::cout << ']' << '\n';
}
