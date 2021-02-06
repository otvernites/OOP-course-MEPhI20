#include <iostream>
#include "..//laba3a/hex.h"

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
			tmp.input(std::cin);
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
		num.output(std::cout);
	}
	
	void Dialog_add(Hex& num) {
		std::cout << "Enter the second decimal number\n";
		Hex second;
		try {
			second.input(std::cin);
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
			num.output(std::cout);
			std::cout << "+  \n";
			second.output(std::cout);
			std::cout << "= \n";
			result.output(std::cout);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	
	void Dialog_subtract(Hex& num) {
		std::cout << "Enter the second decimal number\n";
		Hex second;
		try {
			second.input(std::cin);
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
			num.output(std::cout);
			std::cout << "-  \n";
			second.output(std::cout);
			std::cout << "= \n";
			result.output(std::cout);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	
	void Dialog_parity(Hex& num) {
		num.output(std::cout);

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
			second.input(std::cin);
		}
		catch (std::length_error& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		catch (std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		num.output(std::cout);

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

		second.output(std::cout);
	}
	
	void Dialog_move_left(Hex& num) {
		std::cout << "Enter the number of digits to shift the number : \n"; 
		int n = getNum(n);

		try {
			num.Move_left(n).output(std::cout);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	
	void Dialog_move_right(Hex& num) {
		std::cout << "Enter the number of digits to shift the number : \n";
		int n = getNum(n);
		try {
			num.Move_right(n).output(std::cout);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
}
