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
		//accTable(const accTable&);
		~accTable();

		int addDeposit(int id, Deposit* dep);
		Deposit* findDeposit(int id) const;
		void removeDeposit(int id);
		
		friend std::ostream& operator << (std::ostream&, const accTable&);
	};
}