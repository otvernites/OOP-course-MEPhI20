#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <algorithm>

const int MAX_LEN = 15; //максимальная длина числа 

namespace Lab3a {

	class Hex {

	private:
		int len; //текущая длина массива чисел 
		char hex[MAX_LEN]; //массив значений цифр

	public:
		//конструкторы
		explicit Hex(); //пустой конструктор
		Hex(const long int num); //инициализация 16-ричной константой
		Hex(const char* str); //инициализация как строки символов
		Hex(const Hex&); //копирующий конструктор

		//работа с потоком
		std::ostream& output(std::ostream&) const; //вывод
		std::istream& input(std::istream&); //ввод

		//другие методы
		Hex Add(const Hex& num) const; //сложение
		Hex Subtract(const Hex& num) const; //вычитание
		int Compare(const Hex& num) const; //сравнение
		int Compare(const Hex& num, bool abs) const; //сравнение по модулю
		bool Parity() const; //проверка на четность
		Hex& Move_left(int n); //сдвиг влево 
		Hex& Move_right(int n); //сдвиг вправо

		//геттеры
		char getSign() const;
		int getLen() const { return len; }

		Hex& operator= (const Hex& num);

		//работа с потоком
		friend std::istream& operator>>(std::istream& in, Hex& num);
		friend std::ostream& operator<<(std::ostream& out, const Hex& num);

		Hex operator+ (const Hex& num) const { return this->Add(num); }
		Hex operator- (const Hex& num) const { return this->Subtract(num); }

		Hex& operator>>= (const int n);
		Hex& operator<<= (const int n);

		Hex operator+= (const Hex& num) { return *this = *this + num; }

	private:
		Hex& twosСomplement();
		void updateLen();

	};

	int charToHex(const char str);
	char hexToChar(const int num);
}

