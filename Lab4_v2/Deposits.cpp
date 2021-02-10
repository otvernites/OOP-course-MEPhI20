#include "Deposits.h"

namespace Accs {
	Deposit::Deposit(double sum0, date open_date0, double percent0):
		sum(sum0), open_date(open_date0), percent(percent0) {}

	std::ostream& operator<< (std::ostream& out, const Deposit& dep) {
		return dep.getInfo(out);
	}

	double Deposit::income(const Deposit& dep, const date& curr_date) const {
		double k = (-(dep.getLast().day + dep.getLast().month * 31 + dep.getLast().year * 372) +
			(curr_date.day + curr_date.month * 31 + curr_date.year * 372))/31.0;
		k = k * 100 / 100; // округление
		if (k <= 0) {
			throw std::exception("Incorrect current date");
		}

		return (dep.sum * 0.01 * dep.percent * k);
	}

	std::ostream& commonDeposit::getInfo(std::ostream& out) const {
		out << "Type of deposit: " << "Common" << "\n" <<
			"Amount of money: " << sum << "\n" <<
			"Percent: " << percent << "\n" <<
			"Date of open: " << open_date << "\n" <<
			"Date of last changes: " << last_date << "\n";

			return out;
	}

	commonDeposit::commonDeposit(double sum0, date open_date0, double percent0, date last_date0) :
		Deposit(sum0, open_date0, percent0), last_date(last_date0) {}

	void commonDeposit::changeSum(const double sum0, const date& curr_date) {
		sum += sum0;
		changeLast(curr_date);
	}

	void commonDeposit::changeLast(const date& curr_date) {
		last_date = curr_date;
	}

	date commonDeposit::getLast() const {
		return last_date;
	}

	std::ostream& termDeposit::getInfo(std::ostream& out) const {
		out << "Type of deposit: " << "Term" << "\n" <<
			"Amount of money: " << sum << "\n" <<
			"Percent: " << percent << "\n" <<
			"Date of open: " << open_date << "\n" <<
			"Storage date (in days): " << storage_term << "\n";      

		return out;
	}

	termDeposit::termDeposit(double sum0, date open_date0, double percent0, int storage_term0) :
		Deposit(sum0, open_date0, percent0), storage_term(storage_term0) {}

	date termDeposit::getLast() const {
		return open_date;
	}

	std::ostream& currDeposit::getInfo(std::ostream& out) const {
		out << "Type of deposit: " << "Current" << "\n" <<
			"Amount of money: " << sum << "\n" <<
			"Percent: " << percent << "\n" <<
			"Date of open: " << open_date << "\n" <<
			"Date of last changes: " << last_date << "\n";
		if (curr == 1) {
			out << "Currency: rub " << "\n";
		}
		else if (curr == 2) {
			out << "Currency: usd " << "\n";
		}
		else {
			out << "Currency: eur " << "\n";
		}
		return out;
	}

	currDeposit::currDeposit(double sum0, date open_date0, double percent0, int curr0,
		date last_date0, double exchangeRate0) : Deposit(sum0, open_date0, percent0), curr(curr0),
		last_date(last_date0), exchangeRate(exchangeRate0) {}

	void currDeposit::changeSum(const double sum0, const date& curr_date) {
		sum += sum0;
		changeLast(curr_date);
	}

	void currDeposit::changeLast(const date& curr_date) {
		last_date = curr_date;
	}

	date currDeposit::getLast() const {
		return last_date;
	}

	double currDeposit::convertRub() {
		return (sum * exchangeRate);
	}

	std::istream& operator>> (std::istream& in, Deposit& dep) {
		return dep.inputInfo(in);
	}

	std::istream& commonDeposit::inputInfo(std::istream& in) {

		std::cout << "Enter the deposit amount: " << std::endl;
		std::cin >> sum;
		if (sum <= 0) {
			throw std::exception("Incorrect sum value");
		}
		
		std::cout << "Percent (up to 15%): " << std::endl;
		std::cin >> percent;
		if ((percent <= 0) || (percent > 15)) {
			throw std::exception("Incorrect percent value");
		}
		std::cout << "Enter the current date... " << std::endl;
		std::cin >> open_date;
		if ((open_date.day <= 0) || (open_date.day > 31) || 
			(open_date.month <=0) || (open_date.month > 12) || 
			(open_date.year < 2000) || (open_date.year > 2021)) {
			throw std::exception("Incorrect date value");
		}
		last_date = open_date;
	}

	std::istream& termDeposit::inputInfo(std::istream& in) {
		std::cout << "Enter the deposit amount: " << std::endl;
		std::cin >> sum;
		if (sum <= 0) {
			throw std::exception("Incorrect sum value");
		}

		std::cout << "Percent (up to 15%): " << std::endl;
		std::cin >> percent;
		if ((percent <= 0) || (percent > 15)) {
			throw std::exception("Incorrect percent value");
		}
		std::cout << "Enter the current date... " << std::endl;
		std::cin >> open_date;
		if ((open_date.day <= 0) || (open_date.day > 31) ||
			(open_date.month <= 0) || (open_date.month > 12) ||
			(open_date.year < 2000) || (open_date.year > 2021)) {
			throw std::exception("Incorrect date value");
		}
		
		std::cout << "Enter the storage term in days: " << std::endl;
		std::cin >> storage_term;
		if (storage_term <= 0) {
			throw std::exception("Incorrect storage term value");
		}
	}

	std::istream& currDeposit::inputInfo(std::istream& in) {
		std::cout << "Enter the deposit amount: " << std::endl;
		std::cin >> sum;
		if (sum <= 0) {
			throw std::exception("Incorrect sum value");
		}

		std::cout << "Percent (up to 15%): " << std::endl;
		std::cin >> percent;
		if ((percent <= 0) || (percent > 15)) {
			throw std::exception("Incorrect percent value");
		}
		std::cout << "Enter the current date... " << std::endl;
		std::cin >> open_date;
		if ((open_date.day <= 0) || (open_date.day > 31) ||
			(open_date.month <= 0) || (open_date.month > 12) ||
			(open_date.year < 2000) || (open_date.year > 2021)) {
			throw std::exception("Incorrect date value");
		}
		last_date = open_date;

		std::cout << "Enter the deposit currency: " << std::endl;
		std::cout << "1. Rub; 2. Usd; 3. Eur;" << std::endl;

		int i;
		do {
			i = getNum(i);
		} while ((i < 1) || (i > 3));

		switch (i) {
		case 1:
			curr = 1;
			exchangeRate = 1;
			break;
		case 2:
			curr = 2;
			exchangeRate = 74.01;
			break;
		case 3:
			curr = 3;
			exchangeRate = 89.63;
			break;
		}
	}
}