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
Set::Set(int len) :
	S('A' + cnt++),
	n(len),
	A(nullptr)
{
	Generator(n, A);
	 std::cout << "CREATED " << *this << std::endl;
}
// конструктор — по умолчанию
Set::Set() :
	n(0),
	S('A' + cnt++),
	A(nullptr)
{
	 std::cout << "CREATED " << *this << std::endl;
}
// конструктор копии
Set::Set(const Set& B) :
	S('A' + cnt++),
	n(B.n),
	A(nullptr)
{
	for (ST* p = B.A; p; p = p->next) {
		A = new ST(p->letter, A);
	}
	std::cout << "CREATED " << *this << " FROM " << B.S << std::endl;
}
// конструктор копирования с переносом
Set::Set(Set&& B) noexcept :
	S('A' + cnt++),
	n(B.n),
	A(B.A)
{
	B.A = nullptr;
	B.n = 0;
	 std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
}
// деструктор множества
Set::~Set() {
	 std::cout << "DELETED " << *this << std::endl;
	A->ST::~ST();
}
// присваивание
Set& Set::operator=(const Set& B) {
	if (this != &B) {
		 std::cout << "DELETED LIST-SET {" << A << "} FROM " << S << " BUT NOT OBJECT" << std::endl;
		delete A;
		A = nullptr;
		n = B.n;
		for (ST* p = B.A; p; p = p->next) {
			A = new ST(p->letter, A);
		}
	}
	 std::cout << "RECEIVED " << *this << " FROM " << B.S << std::endl;
	return *this;
}
// присваивание с переносом
Set& Set::operator=(Set&& B) noexcept {
	if (this != &B) {
		 std::cout << "DELETED LIST-SET {" << A << "} FROM " << S << " BUT NOT OBJECT" << std::endl;
		delete A;
		n = B.n;
		A = B.A;
		B.A = nullptr;
		B.n = 0;
	}
	 std::cout << "BECOMED " << *this << " FROM " << B.S << std::endl;
	return *this;
}
// объединение с присваиванием
Set& Set:: operator|=(const Set& B) {
	for (ST* p = B.A; p; p = p->next) {
		if (!IsInSet(p->letter)) {
			A = new ST(p->letter, A);
		}
	}
	std::cout << "RECEIVED " << *this << " = " << S << " | " << B.S << std::endl;
	return *this;
}
// объединение
Set Set:: operator|(const Set& B) const {
 std::cout << "CALCULATION " << S << " | " << B.S << std::endl;
	Set C(*this);
	return (C |= B);
}
// пересечение с присваиванием
Set& Set::operator&=(const Set& B) {
	Set C(*this);
 std::cout << "DELETED LIST-SET {" << A << "} FROM " << S << " BUT NOT OBJECT" << std::endl;
	delete A;
	A = nullptr;
	n = 0;
	for (ST* p = B.A; p; p = p->next) {
		if (C.IsInSet(p->letter)) {
			A = new ST(p->letter, A);
			++n;
		}
	}
	 std::cout << "RECEIVED " << *this << " = " << C.S << " & " << B.S << std::endl;
	return *this;
}
// пересечение
Set Set::operator&(const Set& B) const {
	 std::cout << "CALCULATION " << S << " & " << B.S << std::endl;
	Set C(*this);
	return (C &= B);
}
// дополнение до универсума
Set Set::operator~() const {
	Set C;
	for (char c = 'A'; c <= 'Z'; ++c) {
		if (!IsInSet(c)) {
			C.A = new ST(c, C.A);
		}
	}
	 std::cout << "RECEIVED " << C << " = ~" << S << std::endl;
	return C;
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

	if (len) A = new ST(0, A);

	for (int i = 0; i < len; i++)
	{
		A = new ST(uni[i], A);
	}

	delete[] uni;
}

void Set::Show() {
	std::cout << S << "[" << n << "] = {";
	if (A) {
		ST* T = A;
		while (T) {
			std::cout << T->letter;
			T = T->next;
		}
	}
	else std::cout << "<EMPTY>";
	std::cout << '}';
}
