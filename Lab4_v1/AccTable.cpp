#include "pch.h"
#include "AccTable.h"
#include <map>
#include <iostream>


namespace Accs {
	
	accTable::~accTable() {
		std::map<int, Deposit*>::iterator it;
		for (it = table.begin(); it != table.end(); ++it) {
			delete (*it).second;
		}
		table.clear();
	}

	int accTable::addDeposit(int id, Deposit* dep) {
		std::pair<std::map<int, Deposit*>::iterator, bool> ret = table.insert(std::pair<int, Deposit*>(id, dep));
		return ret.second;
	}

	Deposit* accTable::findDeposit(int id) const {
		std::map<int, Deposit*>::const_iterator it;
		it = table.find(id);
		if (it == table.end()) {
			throw std::exception("Object does not exist");
		}
		return it->second;
	}

	void accTable::removeDeposit(int id) {
		std::map<int, Deposit*>::const_iterator it;
		it = table.find(id);
		if (it == table.end()) {
			throw std::exception("Object does not exist");
		}
		table.erase(id);
	}

	std::ostream& operator << (std::ostream& out, const accTable& tab) {
		std::map<int, Deposit*>::const_iterator it;
		for (it = tab.table.begin(); it != tab.table.end(); ++it) {
			out << "Account number: " << it->first << "\n"
				<< *(it->second) << "\n" << "-----------------" << "\n";
		}
		return out;
	}
}