#define _CRT_SECURE_NO_WARNINGS 1

#include "Hex.h"
#include <sstream>

namespace Lab3a {

	//пустой конструктор - положительное число, 0
	Hex::Hex() : len(1) {
		hex = new char[1];
		hex[0] = '0';
	}

	//инициализация строкой символов
	Hex::Hex(const char* str) {
		//учитываем, что первый может быть знак, запоминаем знак, а после записываем начиная с нулевого
		if (str == nullptr) {
			throw std::invalid_argument("Invalid value! Number out of range.");
		}

		len = strlen(str);

		if (str[0] == '+') {
			sign = true;
			str++;
			len--;
		}
		else if (str[0] == '-') {
			sign = false;
			str++;
			len--;
		}
		else {
			sign = true;
		}
		
		if ((str[0] == '0') && (len != 1)) { //если есть лидирующие нули 
			for (; *str == '0';) {
				str = str + 1;
				len = len - 1;
			}
		}

		if (len == 0) //проверка диапазона значений
			throw std::length_error("Error. Number out of range.");

		hex = new char[len];

		int j = 0;
		for (int i = strlen(str)-1; i >= 0; i--, j++) { //проверка на правильность ввода
			if ((str[i] < '0') || ((str[i] > '9'))
				&& ((str[i] < 'A') || (str[i] > 'F'))
				&& ((str[i] < 'a') || (str[i] > 'f')))
				throw std::invalid_argument("Invalid value! Enter a hexadecimal number.");

			hex[j] = str[i]; //посимвольное заполнение в обратном порядке
		}
	} 

	//инициализация шестнадцатеричной константой 
	Hex::Hex(const long int num) {
		int tmp = num;
		std::stringstream out;
		out << std::hex << num;
		int count = out.str().size();

		char* digits = new char[count+2]; //+1 для \0 
		_itoa(abs(num), digits+1, 16);
		digits[0] = (num > 0) ? '+' : '-';
		this->Hex::Hex(digits);
	}

	//копирующий конструктор
	Hex::Hex(const Hex& num): len(num.len), sign(num.sign) {
		hex = new char[len];

		for (int i = 0; i < len; i++) {
			hex[i] = num.hex[i];
		}
	}

	//перемещающий конструктор
	Hex::Hex(Hex&& num): len(num.len), sign(num.sign), hex(num.hex) {
		num.hex = nullptr;
	}

	Hex& Hex::operator= (const Hex& num) {
		if (this != &num) {
			len = num.len;
			sign = num.sign;

			delete[] hex;
			hex = nullptr;
			
			hex = new char[num.len];
			for (int i = 0; i < len; i++) {
				hex[i] = num.hex[i];
			}
		}
		return *this;
	}

	std::istream& operator>>(std::istream& in, Hex& num) {
		num.input(in);
		if (!in.good()) {
			in.setstate(std::ios::failbit);
		}
		return in;
	} 

	std::istream& Hex::input(std::istream& in) {
		std::string s;
		std::cin >> s;
		if (!in.good()) {
			return in;
		}
		int i = 0;
		if ((s[0] == '+') || s[0] == '-') {
			i = 1;
		}
		if (s.substr(i, 2) == "0x") {
			s.erase(i, 2);
		}
		for (i; i < s.size(); i++) {
			if ((s[i] < '0') || ((s[i] > '9'))
				&& ((s[i] < 'A') || (s[i] > 'F'))
				&& ((s[i] < 'a') || (s[i] > 'f')))
				throw std::invalid_argument("Invalid value! Enter a hexadecimal number.");
		}

		Hex f(s.c_str());
		*this = f;
		return in;
	}

	std::ostream& operator<<(std::ostream& out, const Hex& num) {
		return num.output(out);
	}

	std::ostream& Hex::output(std::ostream& out) const {
		if ((sign == false) && (len != 0)) out << '-';
		for (int i = len-1; i >= 0; --i) {
			out << hex[i];
		}
		if (len <= 0) out << '0';
		out << std::endl;
		return out;
	}

	Hex Hex::Add(const Hex& num) const {

		Hex first = *this;
		Hex second = num;
		Hex sum;

		int n = first.len - second.len;
		int indx = std::max(first.len, second.len);
		sum.hex = new char[indx];
		sum.len = indx;
		if (n > 0) {
			second.Complement(n);
		}
		else if (n < 0) {
			first.Complement(n);
		}
		
		if ((first.sign == false) && (first.len == 1) && (first.hex[0] == '0')) {
			first.sign = true;
		}
		else if ((second.sign == false) && (second.len == 1) && (second.hex[0] == '0')) {
			second.sign = true;
		}

		if (first.getSign() == second.getSign()) {
			int num, overdrive = 0;
			for (int i = 0; i < indx; i++) {
				num = (charToHex(first.hex[i]) + charToHex(second.hex[i])) + overdrive;
				sum.hex[i] = hexToChar(num % 16);
				overdrive = num / 16;
			}
			if (overdrive) {
				char* tmp;
				tmp = new char[indx + 1];

				for (int i = 0; i < indx; i++) {
					tmp[i] = sum.hex[i];
				}
				tmp[indx] = '1';
				delete[] sum.hex;
				sum.hex = tmp;
				sum.len++;
			}
			sum.sign = first.sign;
		}
		else {
			bool sign;
			if (first.Compare(second, true) >= 0 && first.sign == true ||
				first.Compare(second, true) <= 0 && first.sign == false) {
				sum.sign = true;
			}
			else sum.sign = false;


			first.twosСomplement();
			second.twosСomplement();

			int num, overdrive = 0;
			for (int i = 0; i < indx; i++) {
				num = (charToHex(first.hex[i]) + charToHex(second.hex[i])) + overdrive;
				sum.hex[i] = hexToChar(num % 16);
				overdrive = num / 16;
			}

			sum.twosСomplement();
		}

		if ((sum.hex[len-1] == '0') && (len != 1)) { //если есть лидирующие нули 
			for (int i = len-1; ((sum.hex[i] == '0')&& (i>0)); i--) {
				sum.hex[i] = '\0';
				sum.len = sum.len - 1;
			}
		}

		return sum;
	}

	Hex Hex::Subtract(const Hex& num) const {
		Hex decrease = num;
		if (decrease.sign == false) {
			decrease.sign = true;
		}
		else
			if (decrease.sign == true) {
				decrease.sign = false;
			};
		return this->Add(decrease);
	}

	Hex& Hex::operator>>= (const int n) {
		Move_right(n);
		return *this;
	}

	Hex& Hex::Move_right(const int n) {
		if (n < 0)
			throw std::exception("Invalid index");

		char* tmp;
		if (len <= n) {
			tmp = new char[1];
			tmp[0] = '0';
			delete[] hex;
			hex = tmp;
			len = 1;
			return *this;
		}
		else {
			tmp = new char[len - n];
			for (int i = n; i < len; i++) {
				tmp[i-n] = hex[i];
			}
			delete[] hex;
			hex = tmp;
		}
		len -= n;
		return *this;
	}

	Hex& Hex::operator<<= (const int n) {
		Move_left(n);
		return *this;
	}
	//копируем символы последние и потом дополняем нулями
	Hex& Hex::Move_left(const int n) {
		if (n < 0)
			throw std::exception("Invalid index");

		char* tmp;
		tmp = new char[len + n];

		for (int i = 0; i < len; i++) {
			tmp[n+i] = hex[i];
		}
		for (int i = 0; i < n; i++) {
			tmp[i] = '0';
		}

		delete[] hex;
		hex = tmp;

		len += n;
		return *this;
	}

	int Hex::Compare(const Hex& num) const {

		//обработка случаев, когда знаки разные
		if ((sign == true) && (num.getSign() == false)) {
			return 1;
		}

		else if ((sign == false) && (num.getSign() == true)) {
			return -1;

			//когда знак один
		}
		else {
			Hex result = this->Subtract(num);
			if ((result.len == 1) && (result.hex[0] == '0')) {/////////////
				return 0;
			}

			if (result.getSign() == true) {
				return 1;
			}
			else if (result.getSign() == false) {
				return -1;
			}
		}
	}

	int Hex::Compare(const Hex& num, bool abs) const {
		if (!abs) return this->Compare(num);
		for (int i = len - 1; i >= 0; i--)
		{
			if (charToHex(hex[i]) > charToHex(num.hex[i])) return 1;
			if (charToHex(hex[i]) < charToHex(num.hex[i])) return -1;
		}
		return 0;
	} 

	bool Hex::Parity() const {
		int last = 0xf - charToHex(hex[0]) + 1;
		if ((last) % 2 == 0)
			return true;
		else return false;
	}

	Hex& Hex::twosСomplement() {
		if (sign == true)
			return *this;
		else {
			for (int i = 0; i < len; i++) {
				hex[i] = hexToChar(0xf - charToHex(hex[i]));
			}

			int i = 0;
			while (hex[i] == 'F') {
				i++;
			}
			
			if ((i != 0) && (i == len)) {    //дичь - в массиве char будут 2 пустых символа
				char* tmp = new char[len + 1];
				for (int i = 0; i < len; i++)
				{
					tmp[i] = hex[i];           
				}
				tmp[len] = '0';
				delete[] hex;
				hex = tmp;                       
			}
			else if (i != 0) {
				for (int j = 0; j < i; j++) {
					hex[j] = '0';
				}
				hex[i] = hexToChar(charToHex(hex[i]) + 1);
			}
			else {
				hex[0] = hexToChar(charToHex(hex[0]) + 1);
			}

			sign = false;
		}

		return *this;
	} 
	
	Hex& Hex::Complement(int n) {
		char* tmp;
		tmp = new char[len + abs(n)];
		for (int i = 0; i < len; i++) {
			tmp[i] = hex[i];
		}
		for (int i = len; i < len + abs(n); i++)
		{
			tmp[i] = '0';
		}
		delete[] hex;
		hex = tmp;
		return *this;
	}

	int charToHex(const char str) {
		if ((str >= '0') && (str <= '9'))
			return str - '0';
		else if ((str >= 'a') && (str <= 'f'))
			return str - 'a' + 10;
		else if ((str >= 'A') && (str <= 'F'))
			return str - 'A' + 10;
		return 1;
	}

	char hexToChar(const int num) {
		if ((num >= 0) && (num <= 9))
			return num + '0';
		else if ((num >= 10) && (num <= 15))
			return num + 'A' - 10;
		throw std::exception("Invalid parametr");
	}
	
}




