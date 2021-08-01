#ifndef STRING

#define STRING

#include<iostream>
#include<conio.h>
#include<bitset>
#include<math.h>

class String
{
public:
	String(int sizeS) : size{ sizeS }, array{ allocatorString.allocate(sizeS) } {}
	String() :String(80) {}
	String(const char *newStr);
	String(const String &object);

	virtual void setNewArray();

	int getSize() {
		return size;
	}

	char *getArray() {
		return array;
	}

	void setSize(int nSize){
		size = nSize;
	}

	void setArray(char *arr);

	void PrintArray();

	char &operator[](const int index);

	const char &operator[](const int index) const;

	int operator()(const char elem);

	//Возвращает длину строки
	virtual operator int() { return size; }

	String &operator++();

	String operator++(int);

	String &operator--();

	String operator--(int);

	String operator+(String &one);

	friend std::ostream &operator<< (std::ostream &out, const String &one);

	friend std::istream &operator>> (std::istream &in, String &one);
	
	void addMemory(char *newStr);

	void free();

	void trimm();
	
	~String() {
		allocatorString.deallocate(array);
	}
	
protected:
	struct AllocatorString {
		char *allocate(int size) const {
			return new char[size] {0};
		}

		void deallocate(char *arr) {
			if (arr)delete[] arr;
		}

	}allocatorString;
private:
	
	int size;
	char *array;
};

class BitString : public String {
public:
	BitString(int size) : String(size) {}
	BitString() : String() {}
	BitString(const char *NewStr);
	BitString(const String &object);

	void setNewArray() override;

	//Перевод в десятичное число. Изменяет старое поведение. Но решила оставить так из-за текущего задания.
	operator int() override;

private:
	bool isBitString(const char *str);

	bool isBitSymbol(char sym);
};

#endif STRING