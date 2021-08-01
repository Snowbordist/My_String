#include "String.h"

int main() {
	setlocale(LC_ALL, "rus");

	std::cout << "Строка один:\n";
	BitString bit("0101011011");
	std::cout << bit << std::endl;
	std::cout << "Строка два:\n";
	BitString bit2("1001000001");
	std::cout << bit2 << std::endl;

	BitString bit3(bit);
	~bit3;
	String *str3 = &bit3;
	std::cout << "Строка три, обратная строке 1:\n";
	std::cout << *str3 << std::endl;

	std::cout << "Строка три в десятичной системе счисления:\n";
	std::cout << static_cast<int>(*str3) << "\n";

	std::cout << "Строка четыре = строка один & строка два:\n";
	BitString bit4(bit & bit2);
	std::cout << bit4 << std::endl;

	std::cout << "Строка пять = строка один ^ строка два:\n";
	BitString bit5(bit ^ bit2);
	String str5 = bit5;
	std::cout << str5 << std::endl;

	std::cout << "Побитовый сдвиг строки пять влево на 5 элементов:\n";
	bit5 << 5;
	std::cout << bit5 << std::endl;
	return 0;
}