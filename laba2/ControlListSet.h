#pragma once
#include <iostream>
class ST {
public:
	friend class Set;
	ST() : letter('!'), next(nullptr) {}
	ST(char e, ST* n = nullptr) : letter(e), next(n) { }
	~ST() {
		if (this) {
			delete next;
			letter = '*';
		}
	}
	static void* operator new(size_t) {
		return (mup < max_mup ? &list_memory[mup++] : nullptr);
	}
	static void operator delete(void*, size_t) { }
	static void Mark() { mup_spare = mup; }
	static void Release() { mup = mup_spare; }
	static void Clear() { mup = 0; }
	friend static void MemoryOutput();
private:
	char letter;
	ST* next;
	static const int max_mup = 300;
	static ST list_memory[max_mup];
	static int mup, mup_spare;
};

class Set {
public:
	Set(int); // ����������� ���������
	Set(); // ����������� � �� ���������
	Set(const Set&); // ����������� �����
	Set(Set&&) noexcept; // ����������� ����������� � ���������
	~Set(); // ���������� ���������
	Set& operator|=(const Set&); // ����������� � �������������
	Set operator|(const Set&) const; // �����������
	Set& operator&=(const Set&); // ����������� c �������������
	Set operator&(const Set&) const; // �����������
	Set operator~() const; // ���������� �� ����������
	Set& operator=(const Set&); // ������������
	Set& operator=(Set&&) noexcept; // ������������ � ���������
	int power() const { return n; } // ��������� ��������
	bool IsInSet(char) const; // �������� ������� �������� � ���������;
	friend std::ostream& operator<<(std::ostream&, Set&); // ���������� ��������� ������
	void Show();
private:
	static int N, // �������� ����������
			   cnt; // ������� ��������
	int n; // �������� ���������
	char S; // ���
	ST* A; // ��������� �� "������" ������
	void Generator(int, ST*);
};
static void MemoryOutput() {
	std::cout << "Memory for list elements (total - " << std::dec << ST::mup << "):"
		<< std::endl;
	for (int i = 0; i < ST::max_mup; ++i) {
		if (!(i % 100) && i) std::cout << std::endl;
		std::cout << ST::list_memory[i].letter;
	}
	std::cout << std::endl;
}
