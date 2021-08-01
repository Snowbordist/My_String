#include "String.h"

String::String(const char *newStr) {
	size = strlen(newStr) + 1;
	array = allocatorString.allocate(size);
	for (int i = 0; i < size - 1; i++) {
		array[i] = newStr[i];
	}
	array[size - 1] = '\0';
}

String::String(const String &object) : size{ object.size }, array{ allocatorString.allocate(object.size) }{
	for (int i = 0; i < size; i++) {
		array[i] = object.array[i];
	}
}

void String::setNewArray() {
	std::cout << "¬ведите строку и нажмите Enter.\n";
	if (size < 80) {
		size = 80;
		allocatorString.deallocate(array);
		array = allocatorString.allocate(size);
	}
	for (int i = 0; i < size - 1; i++) {
		array[i] = _getch();
		std::cout << array[i];
		if (array[i] == 13) {
			break;
		}
	}
	std::cout << std::endl;
}

void String::setArray(char *arr) {
	int TempSize(strlen(arr) + 1);
	if (array) {
		allocatorString.deallocate(array);
	}
	array = allocatorString.allocate(TempSize);
	for (int i = 0; i < TempSize - 1; i++) {
		array[i] = arr[i];
	}
	array[TempSize - 1] = '/0';
}

void String::PrintArray() {
	std::cout << "¬аша строка: \n";
	int i{ 0 };
	while (array[i] != '\0') {
		std::cout << array[i];
		i++;
	}
	std::cout << "\n";
}

char &String::operator[](const int index) {
	if (index < 0 || index >= size) {
		throw std::exception("Ёлемента с заданным индексом не существует!");
	}
	else {
		return array[index];
	}
}

const char &String::operator[](const int index) const {
	if (index < 0 || index >= size) {
		throw std::exception("Ёлемента с заданным индексом не существует!");
	}
	else {
		return array[index];
	}
}

int String::operator()(const char elem) {
	for (int i = 0; i < size; i++) {
		if (array[i] == elem) {
			return i;
		}
	}
	return -1;
}

String &String::operator++() {
	char *temp = allocatorString.allocate(size);
	for (int i = 0; i < size; i++) {
		temp[i] = array[i];
	}
	allocatorString.deallocate(array);
	array = allocatorString.allocate(size + 1);
	for (int i = 0; i < size - 1; i++) {
		array[i] = temp[i];
	}
	array[size - 1] = ' ';
	array[size] = '\0';
	++size;
	allocatorString.deallocate(temp);
	return *this;
}

String &String::operator--() {
	if (size>=2)
	{
		char *temp = allocatorString.allocate(size);
		for (int i = 0; i < size; i++) {
			temp[i] = array[i];
		}
		allocatorString.deallocate(array);
		array = allocatorString.allocate(--size);
		for (int j = 0; j < size - 1; j++) {
			array[j] = temp[j];
		}
		array[size - 1] = '\0';
		allocatorString.deallocate(temp);
		return *this;
	}
	else{
		return *this;
	}
}

String String::operator++(int) {
	String temp(*this);
	++(*this);
	return temp;
}

String String::operator--(int) {
	if (size>=2)
	{
		String temp(*this);
		--(*this);
		return temp;
	}
	else{
		return *this;
	}
}

String String::operator+(String &one) {
	int resultSize = size + one.size - 1;
	String result(resultSize);
	int i{ 0 };
	for (int j = 0; j < size - 1; j++) {
		result[i] = array[j];
		i++;
	}
	for (int k = 0; k < one.size; k++) {
		result[i] = one.array[k];
		i++;
	}
	return result;
}

std::ostream &operator<< (std::ostream &out, const String &one) {
	int i{ 0 };
	while (one[i] != '\0') {
		out << one[i];
		i++;
	}
	return out;
}

std::istream& operator>> (std::istream &in, String &one) {
	in >> one.array;
	one.addMemory(one.array);
	one.trimm();
	return in;
}

void String::addMemory(char *newStr) {
	int newSize{ 0 };
	newSize = strlen(newStr) + 1;
	if (newSize <= size) {
		for (int i = 0; i < newSize - 1; i++) {
			array[i] = newStr[i];
		}
		array[newSize - 1] = '\0';
	}
	else {
		array = nullptr;
		array = allocatorString.allocate(newSize);
		for (int j = 0; j < newSize - 1; j++) {
			array[j] = newStr[j];
		}
		array[newSize - 1] = '\0';
		size = newSize;
	}
}

void String::free() {
	if (array) {
		array = nullptr;
		size = 0;
	}
}

void String::trimm() {
	if (array) {
		int i{ 0 };
		while (array[i] != '\0') {
			i++;
		}
		i++;
		if (i < size) {
			char *temp = allocatorString.allocate(i);
			for (int j = 0; j < i - 1; j++) {
				temp[j] = array[j];
			}
			temp[i - 1] = '\0';
			allocatorString.deallocate(array);
			array = allocatorString.allocate(i);
			for (int k = 0; k < i; k++) {
				array[k] = temp[k];
			}
			size = i;
			allocatorString.deallocate(temp);
		}
	}
}

BitString::BitString(const char *NewStr) : String() {
	if (isBitString(NewStr)) {
		setSize(strlen(NewStr) + 1);
		for (int i = 0; i < getSize() - 1; i++) {
			getArray()[i] = NewStr[i];
		}
	}
	else {
		throw std::exception("Ѕитова€ строка должна содержать '0' или '1'!");
	}
}

BitString::BitString(const String &object) : String(object) {
	if (!isBitString(getArray())) {
		for (int i = 0; i < getSize() - 1; i++) {
			getArray()[i] = 0;
		}
		throw std::exception("Ѕитова€ строка должна содержать '0' или '1'!");
	}
}

void BitString::setNewArray() {
	std::cout << "¬ведите строку и нажмите Enter.\n";
	if (getSize() < 80) {
		setSize(80);
		allocatorString.deallocate(getArray());
		setArray(allocatorString.allocate(getSize()));;
	}
	for (int i = 0; i < getSize() - 1; i++) {
		getArray()[i] = _getch();
		std::cout << getArray()[i];
		if (!isBitSymbol(getArray()[i])) {
			throw std::exception("Ѕитова€ строка должна содержать '0' или '1'!");
		}
		if (getArray()[i] == 13) {
			break;
		}
	}
	std::cout << std::endl;
}

BitString::operator int() {
	const int notationSystem{ 2 };
	int rankNumber{ 0 };
	while (getArray()[rankNumber] != '\0') {
		rankNumber++;
	}
	int result{ 0 };
	int j = rankNumber - 1;
	for (int i = 0; i < rankNumber; i++) {
		if (getArray()[i] == '0') {
			j--;
			continue;
		}
		else {
			result += pow(notationSystem, j);
			j--;
		}
	}
	return result;
}

bool BitString::isBitString(const char *str) {
	int tempSize = strlen(str);
	for (int i = 0; i < tempSize; i++) {
		if (str[i] != '0' && str[i] != '1') return false;
	}
	return true;
}

bool BitString::isBitSymbol(char sym) {
	if (sym == 0 || sym == 1) {
		return true;
	}
	else {
		return false;
	}
}