#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <algorithm>


const int MAX_LEN = 15; //������������ ����� ����� 

namespace Lab3a {

	class Hex {

	private:
		int len; //������� ����� ������� ����� 
		char hex[MAX_LEN]; //������ �������� ����

	public:
		//������������
		explicit Hex(); //������ �����������
		Hex(const long int num); //������������� 16-������ ����������
		Hex(const char* str); //������������� ��� ������ ��������
		Hex(const Hex&); //���������� �����������

		//������ � �������
		std::ostream& output(std::ostream&) const; //�����
		std::istream& input(std::istream&); //����

		//������ ������
		Hex Add(const Hex& num) const; //��������
		Hex Subtract(const Hex& num) const; //���������
		Hex& Move_left(int n); //����� ����� 
		Hex& Move_right(int n); //����� ������
		int Compare(const Hex& num) const; //���������
		int Compare(const Hex& num, bool abs) const; //��������� �� ������
		bool Parity() const; //�������� �� ��������
		//
		//�������
		char getSign() const;
		int getLen() const { return len; }

		Hex& operator= (const Hex& num);

	private:
		Hex& twos�omplement();
		void updateLen();

	};

	int charToHex(const char str);
	char hexToChar(const int num);
}
