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
	Set(int); // конструктор множества
	Set(); // конструктор — по умолчанию
	Set(const Set&); // конструктор копии
	Set(Set&&) noexcept; // конструктор копирования с переносом
	~Set(); // деструктор множества
	Set& operator|=(const Set&); // объединение с присваиванием
	Set operator|(const Set&) const; // объединение
	Set& operator&=(const Set&); // пересечение c присваиванием
	Set operator&(const Set&) const; // пересечение
	Set operator~() const; // дополнение до универсума
	Set& operator=(const Set&); // присваивание
	Set& operator=(Set&&) noexcept; // присваивание с переносом
	int power() const { return n; } // получение мощности
	bool IsInSet(char) const; // проверка наличия элемента в множестве;
	friend std::ostream& operator<<(std::ostream&, Set&); // перегрузка оператора вывода
	void Show();
private:
	static int N, // мощность универсума
			   cnt; // счетчик множеств
	int n; // мощность множества
	char S; // тег
	ST* A; // указатель на "голову" списка
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
