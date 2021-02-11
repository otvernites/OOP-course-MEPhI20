#pragma once
#include "Deposits.h"
#include <map>
#include <iostream>
#include <algorithm>

namespace Accs {

	class accTable {
	private:
		std::map<int, Deposit*> table;

	public:
		accTable() {}
		accTable(const accTable& new_tab);
		accTable(accTable&& tab2);
		accTable& operator = (const accTable& tab2);
		accTable& operator = (accTable&& tab2);
		~accTable();
		std::map<int, Deposit*>::iterator it_begin() {
			return table.begin();
		}
		std::map<int, Deposit*>::iterator it_end() {
			return table.end();
		}
		int addDeposit(int id, Deposit* dep);
		Deposit* findDeposit(int id) const;
		void removeDeposit(int id);
		int operator== (const accTable& tab2) const;
		friend std::ostream& operator << (std::ostream&, const accTable&);
	};
}