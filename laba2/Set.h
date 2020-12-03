#pragma once
#include <iostream>
class Set
{
	private:
		static int N, cnt;
		int n;
		char S, *A;
		void Generator(int len, char* arr);

	public:
		Set operator| (const Set& ) const;
		Set operator& (const Set&) const;
		Set operator~ () const;
		Set& operator= (const Set&);
		Set& operator= (Set&& B);
		Set& operator &= (const Set&);
		Set& operator |= (const Set&);
		friend std::ostream& operator<< (std::ostream&, Set&);

		void Show();
		int power() { return n; }

		Set(char);
		Set();
		Set(const Set&);
		Set(Set&& B);
		Set(int len);
		static void ZeroingCounter();

		~Set() { delete[] A; }
};
