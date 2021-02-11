#include "pch.h"
#include "AccTable.h"
#include <map>
#include <iostream>


namespace Accs {
	accTable::accTable(const accTable& new_tab) {
		for (auto it = new_tab.table.begin(); it != new_tab.table.end(); ++it) {
			table[it->first] = it->second->copy();
		}
	}

	accTable::accTable(accTable&& tab2) : table(tab2.table) {}

	accTable& accTable::operator = (accTable&& tab2) {
			if (tab2.table != table) {
				std::map <int, Deposit*>::const_iterator it;
				for (it = table.begin(); it != table.end(); it++) {
					delete (*it).second;
				}
				table.clear();
				table = tab2.table;
			}
			return *this;
	}
	accTable& accTable::operator = (const accTable& tab2) {
		//проверка, что элементы не равны
		if (tab2.table != table) {
			//удаление объекта слева от присваивания
			std::map <int, Deposit*>::const_iterator it;
			for (it = table.begin(); it != table.end(); it++) {
				delete (*it).second;
			}
			table.clear();
			//копирование объекта справа в объект слева
			for (auto it = tab2.table.begin(); it != tab2.table.end(); ++it) {
				table[it->first] = it->second->copy();
			}
		}
		return *this;
	}
	
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
	int accTable::operator== (const accTable& tab2) const {
		std::map<int, Deposit*>::const_iterator it1,it2;
		for (it1 = tab2.table.begin(), it2 = tab2.table.begin(); it1 != tab2.table.end(), it2 != tab2.table.end(); it1++,it2++) {
			if ((*it1) != (*it2)) {
				return false;
			}
		}
		return true;
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