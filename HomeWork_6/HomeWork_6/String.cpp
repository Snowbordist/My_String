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

BitString &BitString::operator<<(signed int num) {
	if (num < 0) {
		throw std::exception(" оличество сдвигов должно быть положительным числом!");
	}
	else {
		BitString tempString(getSize());
		tempString.setSize(getSize());
		for (int i = 0; i < getSize(); i++) {
			tempString.getArray()[i] = getArray()[i];
		}
		if (num >= getSize() - 1) {
			for (int j = 0; j < getSize() - 1; j++) {
				getArray()[j] = '0';
			}
		}
		else {
			int k{ 0 };
			for (int h = num; h < tempString.getSize() - 1; h++) {
				getArray()[k] = tempString.getArray()[h];
				k++;
			}
			for (int n = k; n < getSize() - 1; n++) {
				getArray()[k] = '0';
				k++;
			}
		}
		return *this;
	}
}

BitString &BitString::operator>>(signed int num) {
	if (num < 0) {
		throw std::exception(" оличество сдвигов должно быть положительным числом!");
	}
	else {
		BitString tempString(getSize());
		tempString.setSize(getSize());
		for (int i = 0; i < getSize(); i++) {
			tempString.getArray()[i] = getArray()[i];
		}
		if (num >= getSize() - 1) {
			for (int j = 0; j < getSize() - 1; j++) {
				getArray()[j] = '0';
			}
		}
		else {
			int k{ 0 };
			for (int h = 0; h < num; h++) {
				getArray()[k] = '0';
				k++;
			}
			for (int n = 0; n < getSize() - 1 - num; n++) {
				getArray()[k] = tempString.getArray()[n];
				k++;
			}
		}
		return *this;
	}
}

BitString BitString::operator ~ () {
	for (int i = 0; i < getSize() - 1; i++) {
		if (isBitString(getArray())) {
			if (getArray()[i] == '0') {
				getArray()[i] = '1';
			}
			else {
				getArray()[i] = '0';
			}
		}
		else {
			throw std::exception("Ѕитова€ строка должна содержать '0' или '1'!");
		}
	}
	return *this;
}

BitString operator | (BitString &one, BitString &two) {
	if (one.getSize() != two.getSize()) {
		throw std::exception("—троки должны быть одного размера!");
	}
	else {
		BitString result(one.getSize());
		result.setSize(one.getSize());
		for (int i = 0; i < result.getSize() - 1; i++) {
			if (one.getArray()[i] == '1' || two.getArray()[i] == '1') {
				result.getArray()[i] = '1';
			}
			else {
				result.getArray()[i] = '0';
			}
		}
		return result;
	}
}

BitString operator & (BitString &one, BitString &two) {
	if (one.getSize() != two.getSize()) {
		throw std::exception("—троки должны быть одного размера!");
	}
	else {
		BitString result(one.getSize());
		result.setSize(one.getSize());
		for (int i = 0; i < result.getSize() - 1; i++) {
			if (one.getArray()[i] == '1' && two.getArray()[i] == '1') {
				result.getArray()[i] = '1';
			}
			else {
				result.getArray()[i] = '0';
			}
		}
		return result;
	}
}

BitString operator ^ (BitString &one, BitString &two) {
	if (one.getSize() != two.getSize()) {
		throw std::exception("—троки должны быть одного размера!");
	}
	else {
		BitString result(one.getSize());
		result.setSize(one.getSize());
		for (int i = 0; i < result.getSize() - 1; i++) {
			if (one.getArray()[i] != two.getArray()[i]) {
				result.getArray()[i] = '1';
			}
			else {
				result.getArray()[i] = '0';
			}
		}
		return result;
	}
}
