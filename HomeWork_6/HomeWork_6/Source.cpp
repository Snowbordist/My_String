#include "String.h"

int main() {
	setlocale(LC_ALL, "rus");

	std::cout << "������ ����:\n";
	BitString bit("0101011011");
	std::cout << bit << std::endl;
	std::cout << "������ ���:\n";
	BitString bit2("1001000001");
	std::cout << bit2 << std::endl;

	BitString bit3(bit);
	~bit3;
	String *str3 = &bit3;
	std::cout << "������ ���, �������� ������ 1:\n";
	std::cout << *str3 << std::endl;

	std::cout << "������ ��� � ���������� ������� ���������:\n";
	std::cout << static_cast<int>(*str3) << "\n";

	std::cout << "������ ������ = ������ ���� & ������ ���:\n";
	BitString bit4(bit & bit2);
	std::cout << bit4 << std::endl;

	std::cout << "������ ���� = ������ ���� ^ ������ ���:\n";
	BitString bit5(bit ^ bit2);
	String str5 = bit5;
	std::cout << str5 << std::endl;

	std::cout << "��������� ����� ������ ���� ����� �� 5 ���������:\n";
	bit5 << 5;
	std::cout << bit5 << std::endl;
	return 0;
}