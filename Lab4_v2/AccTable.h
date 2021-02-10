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

		int addDeposit(int id, Deposit* dep);
		Deposit* findDeposit(int id) const;
		void removeDeposit(int id);
		int replace(int id, Deposit* new_deposit);
		friend std::ostream& operator << (std::ostream&, const accTable&);
	};
}