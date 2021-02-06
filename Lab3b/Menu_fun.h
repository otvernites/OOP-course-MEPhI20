#include <iostream>
#include "../3b/Hex.h"

namespace Lab3a {

	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		while (!std::cin.good()) {
			std::cin.clear();
			std::cout << "Invalid input, try again: \n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			std::cin >> a;
		}
		return a;
	}


	void Dialog_input(Hex& num) {
		std::cout << "Enter the new first number:\n";
		try {
			Hex tmp;
			std::cin >> tmp;
			num = tmp;
		}
		catch (std::length_error& ex) {
			std::cout << ex.what() << std::endl;
			system("pause");
		}
		catch (std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
			system("pause");
		}
	}

	void Dialog_output(Hex& num) {
		std::cout << "Your number: ";
		std::cout <<  num;
	}

	void Dialog_add(Hex& num) {
		std::cout << "Enter the second decimal number\n";
		Hex second;
		try {
			std::cin >> second;
		}
		catch (std::length_error& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		catch (std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		try {
			Hex result = num.Add(second);

			std::cout << "Processing ...  \n";
			std::cout << num;
			std::cout << "+  \n";
			std::cout << second;
			std::cout << "= \n";
			std::cout << result;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}

	void Dialog_subtract(Hex& num) {
		std::cout << "Enter the second decimal number\n";
		Hex second;
		try {
			std::cin >> second;
		}
		catch (std::length_error& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		catch (std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		try {
			Hex result = num.Subtract(second);

			std::cout << "Processing ...  \n";
			std::cout << num;
			std::cout << "-  \n";
			std::cout << second;
			std::cout << "= \n";
			std::cout << result;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}

	void Dialog_parity(Hex& num) {
		std::cout << num;

		bool flag = num.Parity();
		if (flag == true) {
			std::cout << " - even number \n";
		}
		else {
			std::cout << " - odd number \n";
		}
	}

	void Dialog_compare(Hex& num) {
		std::cout << "Enter the second decimal number\n";
		Hex second;
		try {
			std::cin >> second;
		}
		catch (std::length_error& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		catch (std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		std::cout << num;

		int flag = num.Compare(second);
		if (flag == 1) {
			std::cout << " > ";
		}
		else if (flag == -1) {
			std::cout << " < ";
		}
		else {
			std::cout << " = ";
		}

		std::cout << second;
	}

	void Dialog_move_left(Hex& num) {
		std::cout << "Enter the number of digits to shift the number : \n";
		int n = getNum(n);

		try {
			num <<= (n);
			std::cout << num;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}

	void Dialog_move_right(Hex& num) {
		std::cout << "Enter the number of digits to shift the number : \n";
		int n = getNum(n);
		try {
			num >>=(n);
			std::cout << num;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
}
