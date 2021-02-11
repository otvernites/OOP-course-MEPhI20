#pragma once
#include "Deposits.h"
#include "MyMap.h"
#include <map>
#include <iostream>
#include <algorithm>

namespace Accs {

	class accTable {
	private:
		My_Map<int, Deposit*> table;

	public:
		accTable() {}
		~accTable();
		My_Map<int, Deposit*>::Iterator it_begin() {
			return table.begin();
		}
		My_Map<int, Deposit*>::Iterator it_end() {
			return table.end();
		}
		int addDeposit(int id, Deposit* dep);
		Deposit* findDeposit(int id) const;
		void removeDeposit(int id);
		int replace(int id, Deposit* new_deposit);
		int operator== (const accTable& tab2) const;
		friend std::ostream& operator << (std::ostream&, const accTable&);
	};
}