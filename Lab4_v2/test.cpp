#include "pch.h"
#include "gtest/gtest.h"
#include "AccTable.h"


TEST(commonDeposit, empty_constructor) {
	Accs::commonDeposit dep;
	ASSERT_EQ(dep.getSum(), 0.0);
	ASSERT_EQ(dep.get_percent(), 0.0);
	ASSERT_EQ(dep.get_open_date().day, 0);
	ASSERT_EQ(dep.get_open_date().month, 0);
	ASSERT_EQ(dep.get_open_date().year, 0);
	ASSERT_EQ(dep.get_last_date().day, 0);
	ASSERT_EQ(dep.get_last_date().month, 0);
	ASSERT_EQ(dep.get_last_date().year, 0);
}
TEST(commonDeposit, initilize_constructor) {
	Accs::date open_d(2, 3, 2003);
	Accs::commonDeposit dep(1000.0, open_d, 6.0, open_d);
	ASSERT_EQ(dep.getSum(), 1000.0);
	ASSERT_EQ(dep.get_percent(), 6.0);
	ASSERT_EQ(dep.get_open_date().day, open_d.day);
	ASSERT_EQ(dep.get_open_date().month, open_d.month);
	ASSERT_EQ(dep.get_open_date().year, open_d.year);
	ASSERT_EQ(dep.get_last_date().day, open_d.day);
	ASSERT_EQ(dep.get_last_date().month, open_d.month);
	ASSERT_EQ(dep.get_last_date().year, open_d.year);
}

TEST(commonDeposit, changeLast) {
	Accs::date open_d(2, 3, 2003);
	Accs::commonDeposit dep(1000.0, open_d, 6.0, open_d);
	Accs::date last_d(4, 5, 2005);

	dep.changeLast(last_d);		//check this function
	ASSERT_EQ(dep.getSum(), 1000.0);
	ASSERT_EQ(dep.get_percent(), 6.0);
	ASSERT_EQ(dep.get_open_date().day, open_d.day);
	ASSERT_EQ(dep.get_open_date().month, open_d.month);
	ASSERT_EQ(dep.get_open_date().year, open_d.year);
	ASSERT_EQ(dep.get_last_date().day, last_d.day);
	ASSERT_EQ(dep.get_last_date().month, last_d.month);
	ASSERT_EQ(dep.get_last_date().year, last_d.year);
}

TEST(commonDeposit, changeSum) {
	Accs::commonDeposit dep(1000.0);
	Accs::date last_d(4, 5, 2005);
	dep.changeSum(2500.0, last_d);	//check this function

	ASSERT_EQ(dep.getSum(), 3500.0);

	ASSERT_EQ(dep.get_last_date().day, last_d.day);
	ASSERT_EQ(dep.get_last_date().month, last_d.month);
	ASSERT_EQ(dep.get_last_date().year, last_d.year);
	ASSERT_EQ(dep.get_open_date().day, 0);
	ASSERT_EQ(dep.get_open_date().month, 0);
	ASSERT_EQ(dep.get_open_date().year, 0);
}

TEST(commonDeposit, getLast) {
	Accs::commonDeposit dep;
	Accs::date last_d(4, 5, 2005);
	dep.changeLast(last_d);

	ASSERT_EQ(dep.getLast().day, last_d.day);
	ASSERT_EQ(dep.getLast().month, last_d.month);
	ASSERT_EQ(dep.getLast().year, last_d.year);
}
TEST(commonDeposit, getOpen) {
	Accs::date open_d(1, 3, 2002);
	Accs::date last_d(2, 4, 2003);
	Accs::commonDeposit dep(1000.0, open_d, 6.0, last_d);

	ASSERT_EQ(dep.getOpen().day, open_d.day);
	ASSERT_EQ(dep.getOpen().month, open_d.month);
	ASSERT_EQ(dep.getOpen().year, open_d.year);
}
TEST(commonDeposit, income) {
	Accs::date open_d(1, 3, 2001);
	Accs::date last_d(2, 4, 2003);
	Accs::commonDeposit dep(1000.0, open_d, 6.0, last_d);

	Accs::date next_d(1, 6, 2003);
	double money = dep.income(dep, next_d); //check this function
	ASSERT_NEAR(118.06, money, 0.001);

	Accs::date next_d2(2, 9, 2004);
	double money2 = dep.income(dep, next_d2); //check this function
	ASSERT_NEAR(1020.0, money2, 0.001);
}
TEST(commonDeposit, income_exception) {
	Accs::date open_d(1, 3, 2001);
	Accs::date last_d(2, 4, 2003);
	Accs::commonDeposit dep(1000.0, open_d, 6.0, last_d);
	Accs::date next_d(1, 1, 2003);
	ASSERT_THROW(dep.income(dep, next_d), std::exception);
}

TEST(termDeposit, empty_constructor) {
	Accs::termDeposit dep;
	ASSERT_EQ(dep.getSum(), 0.0);
	ASSERT_EQ(dep.get_percent(), 0.0);
	ASSERT_EQ(dep.get_open_date().day, 0);
	ASSERT_EQ(dep.get_open_date().month, 0);
	ASSERT_EQ(dep.get_open_date().year, 0);
	ASSERT_EQ(dep.getTerm(), 0);
}
TEST(termDeposit, initialize_constructor) {
	Accs::date open_d(2, 3, 2003);
	Accs::termDeposit dep(3000.0, open_d, 7.0, 400);
	ASSERT_EQ(dep.getSum(), 3000.0);
	ASSERT_EQ(dep.get_percent(), 7.0);
	ASSERT_EQ(dep.get_open_date().day, open_d.day);
	ASSERT_EQ(dep.get_open_date().month, open_d.month);
	ASSERT_EQ(dep.get_open_date().year, open_d.year);
	ASSERT_EQ(dep.getTerm(), 400);
}
TEST(commonDeposit, getLast_and_getTerm) {
	Accs::date open_d(19, 2, 2021);
	Accs::termDeposit dep(3500, open_d, 12, 250);

	ASSERT_EQ(dep.getTerm(), 250);
	ASSERT_EQ(dep.getLast().day, open_d.day);
	ASSERT_EQ(dep.getLast().month, open_d.month);
	ASSERT_EQ(dep.getLast().year, open_d.year);
}

TEST(currDeposit, empty_constructor) {
	Accs::currDeposit dep;
	ASSERT_EQ(dep.getSum(), 0.0);
	ASSERT_EQ(dep.get_percent(), 0.0);
	ASSERT_EQ(dep.get_open_date().day, 0);
	ASSERT_EQ(dep.get_open_date().month, 0);
	ASSERT_EQ(dep.get_open_date().year, 0);
	ASSERT_EQ(dep.get_curr(), 1);
	ASSERT_EQ(dep.get_rate(), 1.0);
	ASSERT_EQ(dep.getLast().day, 0);
	ASSERT_EQ(dep.getLast().month, 0);
	ASSERT_EQ(dep.getLast().year, 0);
}
TEST(currDeposit, initialize_constructor) {
	Accs::date open_d(2, 3, 2003);
	Accs::currDeposit dep(3000.0, open_d, 11.0, 2, open_d, 74.0);
	ASSERT_EQ(dep.getSum(), 3000.0);
	ASSERT_EQ(dep.get_percent(), 11.0);
	ASSERT_EQ(dep.get_open_date().day, 2);
	ASSERT_EQ(dep.get_open_date().month, 3);
	ASSERT_EQ(dep.get_open_date().year, 2003);
	ASSERT_EQ(dep.get_curr(), 2);
	ASSERT_EQ(dep.get_rate(), 74.0);
	ASSERT_EQ(dep.getLast().day, 2);
	ASSERT_EQ(dep.getLast().month, 3);
	ASSERT_EQ(dep.getLast().year, 2003);
}

TEST(accTable, addDeposit_findDeposit) {
	Accs::accTable tab;
	Accs::date open_d(19, 2, 2021);
	Accs::termDeposit dep(3500, open_d, 12, 250);
	tab.addDeposit(2304, dep.copy());
	Accs::Deposit* f_dep = tab.findDeposit(2304);
	//проверка, что найденный элемент соответствует вставленному
	Accs::termDeposit* term_dep = dynamic_cast<Accs::termDeposit*>(f_dep);
	ASSERT_EQ(term_dep->getSum(), 3500);
	ASSERT_EQ(term_dep->get_percent(), 12);
	ASSERT_EQ(term_dep->getTerm(), 250);
	ASSERT_EQ(term_dep->getOpen().day, 19);
	ASSERT_EQ(term_dep->getOpen().month, 2);
	ASSERT_EQ(term_dep->getOpen().year, 2021);
}
TEST(accTable, removeDeposit) {
	Accs::accTable tab;
	Accs::date open_d(19, 2, 2021);
	Accs::termDeposit dep(3500, open_d, 12, 250);
	Accs::date open_d2(2, 3, 2003);
	Accs::currDeposit dep2(3000.0, open_d2, 11.0, 2, open_d2, 74.0);
	Accs::date open_d3(2, 3, 2003);
	Accs::commonDeposit dep3(1000.0, open_d3, 6.0, open_d3);
	tab.addDeposit(2304, dep.copy());
	tab.addDeposit(1205, dep2.copy());
	tab.addDeposit(3001, dep3.copy());

	Accs::accTable Restab;
	Accs::termDeposit dep4(3500, open_d, 12, 250);
	Restab.addDeposit(2304, dep4.copy());

	tab.removeDeposit(1205);
	tab.removeDeposit(3001);

	ASSERT_TRUE(Restab == tab);
}

TEST(accTable, findDeposit_exception) {
	Accs::accTable tab;
	Accs::date open_d(19, 2, 2021);
	Accs::termDeposit dep(3500, open_d, 12, 250);
	tab.addDeposit(2304, dep.copy());
	ASSERT_THROW(tab.findDeposit(1004), std::exception);
}
TEST(accTable, removeDeposit_exception) {
	Accs::accTable tab;
	Accs::date open_d2(2, 3, 2003);
	Accs::currDeposit dep2(3000.0, open_d2, 11.0, 2, open_d2, 74.0);
	Accs::date open_d3(2, 3, 2003);
	Accs::commonDeposit dep3(1000.0, open_d3, 6.0, open_d3);
	tab.addDeposit(1205, dep2.copy());
	tab.addDeposit(3001, dep3.copy());

	ASSERT_THROW(tab.removeDeposit(5034), std::exception);

}
int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}