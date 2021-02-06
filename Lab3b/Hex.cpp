#define _CRT_SECURE_NO_WARNINGS 1

#include "../3b/Hex.h"

namespace Lab3a {

	//пустой конструктор - положительное число, во всех разрядах нули 
	Hex::Hex() : len(1) {
		for (int i = 0; i < MAX_LEN; i++) {
			hex[i] = '0';
		}
	}

	//инициализация шестнадцатеричной константой 
	Hex::Hex(const long int num) {
		char digits[MAX_LEN + 1];
		_itoa(abs(num), digits + 1, 16);
		digits[0] = (num > 0) ? '0' : '1';
		digits[MAX_LEN] = '\0';
		this->Hex::Hex(digits);
		updateLen();
	}

	//инициализация строкой символов
	Hex::Hex(const char* str) : len(strlen(str)) {

		if (str[1] == '0') { //если есть лидирующие нули 
			for (; *str == '0';) {
				str = str + 1;
				len = len - 1;
			}
		}

		if ((len > MAX_LEN) || (len == 0)) //проверка диапазона значений
			throw std::length_error("Error. Number out of range.");

		int j = 0;
		for (int i = len - 1; i > 0; i--, ++j) { //проверка на правильность ввода
			if ((str[i] < '0') || ((str[i] > '9'))
				&& ((str[i] < 'A') || (str[i] > 'F'))
				&& ((str[i] < 'a') || (str[i] > 'f')))
				throw std::invalid_argument("Invalid value! Enter a hexadecimal number.");

			hex[j] = str[i]; //посимвольное заполнение в обратном порядке
		}

		for (int i = len - 1; i < MAX_LEN - 1; i++) {
			hex[i] = '0'; //заполнение нулями 
		}

		if (str[0] == '0' || str[0] == '+') {
			hex[MAX_LEN - 1] = 48;
		}
		else {
			hex[MAX_LEN - 1] = '1';
		}
		updateLen();
	}

	//копирующий конструктор
	Hex::Hex(const Hex& num) {
		len = num.len;
		for (int i = 0; i < MAX_LEN; i++) {
			hex[i] = num.hex[i];
		}
	}

	Hex& Hex::operator= (const Hex& num) {
		if (this != &num) {
			len = num.len;
			for (int i = 0; i < MAX_LEN; i++) {
				hex[i] = num.hex[i];
			}
		}
		return *this;
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
		if (i == 0) {
			s.insert(0, 1, '+');
		}
		for (int j = 1; j < s.size(); j++) {
			if ((s[j] < '0') || ((s[j] > '9'))
				&& ((s[j] < 'A') || (s[j] > 'F'))
				&& ((s[j] < 'a') || (s[j] > 'f')))
				throw std::invalid_argument("Invalid value! Enter a hexadecimal number.");
		}

		Hex f(s.c_str());
		*this = f;
		return in;
	}

	std::istream& operator>>(std::istream& in, Hex& num) {
		num.input(in);
		if (!in.good()) {
			in.setstate(std::ios::failbit);
		}
		return in;
	}

	std::ostream& operator<<(std::ostream& out, const Hex& num) {
		return num.output(out);
	}

	std::ostream& Hex::output(std::ostream& out) const {
		int k = std::min(len - 1, MAX_LEN - 2);
		if ((hex[MAX_LEN - 1] == '1') && (len != 0)) out << '-';
		for (int i = k; i >= 0; --i) {
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

		if (first.getSign() == second.getSign()) {
			int num, overdrive = 0;
			for (int i = 0; i < MAX_LEN - 1; i++) {
				num = (charToHex(first.hex[i]) + charToHex(second.hex[i])) + overdrive;
				sum.hex[i] = hexToChar(num % 16);
				overdrive = num / 16;
			}
			if (overdrive) throw std::exception("Overflow");
			sum.hex[MAX_LEN - 1] = first.hex[MAX_LEN - 1];
		}
		else {
			bool sign;
			if (first.Compare(second, true) >= 0 && first.hex[MAX_LEN - 1] == '0' ||
				first.Compare(second, true) <= 0 && first.hex[MAX_LEN - 1] == '1') {
				sign = 0;
			}
			else sign = 1;


			first.twosСomplement();
			second.twosСomplement();

			int num, overdrive = 0;
			for (int i = 0; i < MAX_LEN - 1; i++) {
				num = (charToHex(first.hex[i]) + charToHex(second.hex[i])) + overdrive;
				sum.hex[i] = hexToChar(num % 16);
				overdrive = num / 16;
			}

			sum.hex[MAX_LEN - 1] = hexToChar(int(sign));
			sum.twosСomplement();
		}
		sum.updateLen();
		return sum;
	}

	Hex Hex::Subtract(const Hex& num) const {
		Hex decrease = num;
		if (decrease.hex[MAX_LEN - 1] == '1') {
			decrease.hex[MAX_LEN - 1] = '0';
		}
		else
			if (decrease.hex[MAX_LEN - 1] == '0') {
				decrease.hex[MAX_LEN - 1] = '1';
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

		for (int i = 0; i < len - n; i++) { //копирование 
			hex[i] = hex[n + i];
		}

		for (int i = std::max(len - n, 0); i < MAX_LEN - 1; i++) { //дополнение нулями, с учетом большого зн. n
			hex[i] = '0';
		}

		len -= n;
		return *this;
	}

	Hex& Hex::operator<<= (const int n) {
		Move_left(n);
		return *this;
	}

	Hex& Hex::Move_left(const int n) {
		if (n < 0)
			throw std::exception("Invalid index");

		int j = MAX_LEN - 2;

		for (int i = (MAX_LEN - (n + 2)); i >= 0; i--, j--) {

			hex[j] = hex[i];
		}

		int k = std::min(MAX_LEN - 2, n);

		for (int i = 0; i < k; i++) {
			hex[i] = '0';
		}

		len += n;
		return *this;
	}

	int Hex::Compare(const Hex& num) const {

		//обработка случаев, когда знаки разные
		if ((hex[MAX_LEN - 1] == '0') && (num.getSign() == '-')) {
			return 1;
		}

		else if ((hex[MAX_LEN - 1] == '1') && (num.getSign() == '+')) {
			return -1;

			//когда знак один
		}
		else {
			Hex result = this->Subtract(num);
			if (result.len == 0) {
				return 0;
			}

			if (result.getSign() == '+') {
				return 1;
			}
			else if (result.getSign() == '-') {
				return -1;
			}
		}
	}

	int Hex::Compare(const Hex& num, bool abs) const {
		if (!abs) return this->Compare(num);
		for (int i = MAX_LEN - 2; i >= 0; i--)
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
		if (hex[MAX_LEN - 1] == '0')
			return *this;
		else {
			for (int i = 0; i < MAX_LEN - 1; i++) {
				hex[i] = hexToChar(0xf - charToHex(hex[i]));
			}

			int i = 0;
			while (hex[i] == 'F') {
				i++;
			}

			if (i != 0) {
				for (int j = 0; j < i; j++) {
					hex[j] = '0';
				}
				hex[i] = hexToChar(charToHex(hex[i]) + 1);
			}
			else {
				hex[0] = hexToChar(charToHex(hex[0]) + 1);
			}
			hex[MAX_LEN - 1] = '1';
		}

		return *this;
	}

	char Hex::getSign() const { //получение знака числа
		if ((hex[MAX_LEN - 1] == '0'))
			return '+';
		else return '-';
	}

	void Hex::updateLen() {
		int new_len = MAX_LEN - 1;
		for (int i = MAX_LEN - 2; i >= 0; i--)
		{
			if (hex[i] == '0') new_len--;
			else break;
		}
		len = new_len;
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
		throw std::exception("invalid parametr");
	}
}



