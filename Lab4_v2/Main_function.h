#pragma once
#include <iostream>
#include "AccTable.h"
#include <typeinfo>
#include <ctime>
#include <time.h>

namespace Accs {

	void Dialog_open_account(accTable& tab) {
		std::cout << "Enter the type of deposit: " << std::endl;
		std::cout << "1. Common;  2. Term;  3. Currency;" << std::endl;

		int type;
		do {
			getNum(type);
		} while ((type < 1) || (type > 3));

		Deposit* new_deposit = nullptr;
		commonDeposit d1;
		termDeposit d2;
		currDeposit d3;

		switch (type) {
		case 1:
			new_deposit = &d1;
			break;
		case 2:
			new_deposit = &d2;
			break;
		case 3:
			new_deposit = &d3;
			break;
		}
		try {
			std::cin >> (*new_deposit);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		int id;
		srand(time(NULL));
		do {
			id = rand() % INT_MAX;
		} while (!tab.addDeposit(id, new_deposit->copy()));
	}

	void Dialog_show_account_status(accTable& tab) {
		std::cout << "Enter your bank account number: " << std::endl;
		int id;
		std::cin >> id;

		try {
			Deposit* dep = tab.findDeposit(id);
			std::cout << *(dep);

			date open = dep->getOpen();
			date now;
			std::cout << "------------------------- " << std::endl;
			std::cout << "Enter the current date (to calculate interest) ... " << std::endl;
			std::cin >> now;
			if ((now.day <= 0) || (now.day > 31) ||
				(now.month <= 0) || (now.month > 12) ||
				(now.year < 2000) || (now.year > 2021) || (!(open < now))) {
				throw std::exception("Incorrect date value");
			}
			std::cout << "Accrued sum: " << dep->income(*dep, now) << std::endl;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
	}

	void Dialog_close_account(accTable& tab) {
		std::cout << "Enter your bank account number: " << std::endl;
		int id;
		std::cin >> id;

		Deposit* dep = nullptr;
		try {
			 dep = tab.findDeposit(id);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		date open = dep->getOpen();
		date now;

		try {
			std::cout << "------------------------- " << std::endl;
			std::cout << "Enter the current date (to calculate interest) ... " << std::endl;
			std::cin >> now;
			if ((now.day <= 0) || (now.day > 31) ||
				(now.month <= 0) || (now.month > 12) ||
				(now.year < 2000) || (now.year > 2021) || (!(open < now))) {
				throw std::exception("Incorrect date value");
			}
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		if (typeid(*dep) == typeid(termDeposit)) {
			termDeposit* tmp = dynamic_cast<termDeposit*>(dep);
			int all_days = tmp->getTerm();
			tm now_t = { 0 }, open_t = { 0 };
			now_t.tm_year = now.year - 1900;
			now_t.tm_mon = now.month - 1;
			now_t.tm_mday = now.day;
			open_t.tm_year = open.year - 1900;
			open_t.tm_mon = open.month - 1;
			open_t.tm_mday = open.day;
				
			int delta = (mktime(&now_t) - mktime(&open_t)) / 60 / 60 / 24;

			double profit;
			try {
				profit = dep->income(*dep, now);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				return;
			}

			if (delta < all_days) {
				std::cout << "Deposit amount: " << (*dep).getSum() << std::endl;  
				std::cout << "Interest accruals (penalty 25%): " << 0.75 * profit << std::endl;
				std::cout << "Final sum: " << ((*dep).getSum() + 0.75 * profit) << std::endl;
			}
			else {
				std::cout << "Deposit amount: " << (*dep).getSum() << std::endl;
				std::cout << "Interest accruals: " << profit << std::endl;
				std::cout << "Final sum: " << ((*dep).getSum() + profit) << std::endl;
			}
		}
		else {
			double profit_;
			try {
				profit_ = dep->income(*dep, now);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				return;
			}
			std::cout << "Deposit amount: " << (*dep).getSum() << std::endl;
			std::cout << "Interest accruals: " << profit_ << std::endl;
			std::cout << "Final sum: " << ((*dep).getSum() + profit_) << std::endl;
		}

		try {
			tab.removeDeposit(id);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
	}
		

	void Dialog_work_with_account(accTable& tab) {
		std::cout << "Enter your bank account number: " << std::endl;
		int id;
		std::cin >> id;

		Deposit* dep = nullptr;
		commonDeposit* d1 = nullptr;
		currDeposit* d2 = nullptr;

		try {
			dep = tab.findDeposit(id);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		date open;
		int type;
		if (typeid(*dep) == typeid(commonDeposit)) {
			type = 1;
			d1 = dynamic_cast<commonDeposit*>(dep);
			open = (*d1).getOpen();
		}
		else if (typeid(*dep) == typeid(termDeposit)) {
			type = 2;
			std::cout << "Operations with a part of the deposit are not available for term deposits!" << std::endl;
			return;
		}
		else {
			type = 3;
			d2 = dynamic_cast<currDeposit*>(dep);
			open = (*d2).getOpen();
		}

		std::cout << "Select an action: " << std::endl;
		std::cout << "1. Deposit money; 2. Take deposit; 3. Take percents;" << std::endl;

		int act;
		do {
			getNum(act);
		} while ((act < 1) || (act > 3));

		date now;
		try {
			std::cout << "Enter the current date... " << std::endl;
			std::cin >> now;
			if ((now.day <= 0) || (now.day > 31) ||
				(now.month <= 0) || (now.month > 12) ||
				(now.year < 2000) || (now.year > 2021) || (!(open < now))) {
				throw std::exception("Incorrect date value");
			}
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		double change_sum;
		double percents;

		switch (act) {
		case 1:
			std::cout << "How much money do you want to deposit? " << std::endl;
			getNum(change_sum);

			if (type == 1) {
				try {
					percents = (*d1).income(*d1, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}

				(*d1).changeSum(change_sum + percents, now);
				tab.replace(id, d1);
			}
			else if (type ==3) {
				try {
					 percents = (*d2).income(*d2, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}

				(*d2).changeSum(change_sum + percents, now);
				tab.replace(id, d2);
			}
			std::cout << "Success!" << std::endl;
			break;
		case 2:
			std::cout << "Enter sum which you want to get: ";
			getNum(change_sum);

			if (type == 1) {
				try {
					percents = (*d1).income(*d1, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}

				try {
					if (((*d1).getSum() + percents) < change_sum) {
						throw std::exception("There are not enough funds on your account");
					}
					(*d1).changeSum(percents - change_sum, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}
				tab.replace(id, d1);
			}
			else if (type == 3) {
				try {
					percents = (*d2).income(*d2, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}

				try {
					if (((*d2).getSum() + percents) < change_sum) {
						throw std::exception("There are not enough funds on your account");
					}
					(*d2).changeSum(percents - change_sum, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}
				tab.replace(id, d2);
			}
			std::cout << "Success!" << std::endl;
			break;
		case 3:
			if (type == 1) {
				try {
					percents = (*d1).income(*d1, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}

				(*d1).changeLast(now);
				tab.replace(id, d1);
				std::cout << "Your sum accrued from " << (*d1).getLast() << " : " << percents << std::endl;
			}
			else if (type == 3) {
				try {
					percents = (*d2).income(*d2, now);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return;
				}

				(*d2).changeLast(now);
				tab.replace(id, d2);
				std::cout << "Your sum accrued from " << (*d2).getLast() << " : " << percents << std::endl;
			}
			std::cout << "Success!" << std::endl;
			break;
		}
	}

	void Dialog_get_all_accounts(accTable& tab) {
		std::cout << tab;
	}
}

