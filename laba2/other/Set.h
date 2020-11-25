#pragma once
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

		void Show();
		int power() { return n; }

		Set(char);
		Set();
		Set(const Set&);
		Set(Set&& B);
		Set(int len);
		
		~Set() { delete[] A; }
};