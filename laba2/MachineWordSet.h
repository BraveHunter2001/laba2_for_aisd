#pragma once
#include <iostream>
class Set
{
private:
	const short SHIFT = 192;
	static int N, cnt;
	int n;
	char S;
	int A;
	void Generator(int len, int* arr);
	void CalcPower();

public:
	Set operator| (const Set&) const;
	Set operator& (const Set&) const;
	Set operator~ () const;
	Set& operator= (const Set&);
	Set& operator= (Set&& B);
	Set& operator &= (const Set&);
	Set& operator |= (const Set&);
	friend std::ostream& operator<< (std::ostream&, Set&);
	static void ZeroingCounter();

	void Show();
	int power() { return n; }

	Set(char);
	Set();
	Set(const Set&);
	Set(Set&& B);
	Set(int len);

	~Set() {  }
};
