#pragma once
#include <iostream>
class Set
{
private:
	static int N, cnt;
	int n;
	char S;
	bool* A;
	void Generator(int len, bool* arr);
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

	~Set() { delete[] A; }
};

