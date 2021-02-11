#include "pch.h"
#include "AccTable.h"
#include <map>
#include <iostream>


namespace Accs {

	accTable::~accTable() {
		My_Map <int, Deposit*>::Iterator it(table.begin());
		for (; it != table.end(); it++) {
			delete (*it)->second;
		}
	}

	int accTable::addDeposit(int id, Deposit* dep) {
		int ret = table.insert(new MyPair<int, Deposit*>(id, dep->copy()));
		return ret;
	}

	Deposit* accTable::findDeposit(int id) const {
		My_Map<int, Deposit*>::Iterator res = table.find(id);
		if (res == table.end()) {
			throw std::exception("Object does not exist");
		}
		return (*res)->second->copy();
	}

	void accTable::removeDeposit(int id) {
		My_Map<int, Deposit*>::Iterator res = table.find(id);
		res = table.find(id);
		if (res == table.end()) {
			throw std::exception("Object does not exist");
			return;
		}
		table.erase(id);
	}
	int accTable::operator== (const accTable& tab2) const {
		My_Map<int, Deposit*>::Iterator it1 = tab2.table.begin(), it2 = tab2.table.begin();
		for (; it1 != tab2.table.end(), it2 != tab2.table.end(); it1++, it2++) {
			if ((*it1) != (*it2)) {
				return false;
			}
		}
		return true;
	}
	int accTable::replace(int account_number, Deposit* new_deposit) {
		My_Map<int, Deposit*>::Iterator res = table.find(account_number);
		if (res == table.end()) {
			throw std::exception("Account don't exist!");
			return 0;
		}
		else {
			table.erase(account_number);
			table.insert(new MyPair<int, Deposit*>(account_number, new_deposit->copy()));
		}
	}
	std::ostream& operator << (std::ostream& out, const accTable& tab) {
		My_Map<int, Deposit*>::Iterator it(tab.table.begin());
		for (it = tab.table.begin(); it != tab.table.end(); it++) {
			out << "Account number: " << (*it)->first << "\n"
				<< *(*it)->second << "\n" << "-----------------" << "\n";
		}
		return out;
	}
}