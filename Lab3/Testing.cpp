#include "pch.h"
#include "../laba3a/hex.cpp"
#include "gtest/gtest.h"
#include <sstream>


//
//������������ �������������
TEST(HexConstructors, DefaultConstructor) {
	Lab3a::Hex num;
	ASSERT_EQ(1, num.getLen());
	ASSERT_EQ('+', num.getSign());
	std::stringstream out;
	num.output(out);
	ASSERT_EQ("0\n", out.str());
}

TEST(HexConstructors, ConstConstructor) {
	Lab3a::Hex num1(0x0000023cb4);
	Lab3a::Hex num2(-0x41daa0);
	Lab3a::Hex num3(-0xAc);
	
	ASSERT_EQ(5, num1.getLen());
	ASSERT_EQ('+', num1.getSign());
	std::stringstream out1;
	num1.output(out1);
	ASSERT_EQ("23cb4\n", out1.str());

	ASSERT_EQ(6, num2.getLen());
	ASSERT_EQ('-', num2.getSign());
	std::stringstream out2;
	num2.output(out2);
	ASSERT_EQ("-41daa0\n", out2.str());

	ASSERT_EQ(2, num3.getLen());
	ASSERT_EQ('-', num3.getSign());
	std::stringstream out3;
	num3.output(out3);
	ASSERT_EQ("-ac\n", out3.str());
}

TEST(HexConstructors, StrConstructor) {
	Lab3a::Hex num1("+abc3ef");
	Lab3a::Hex num2("-29a");
	Lab3a::Hex num3("-00022");

	ASSERT_EQ(6, num1.getLen());
	ASSERT_EQ('+', num1.getSign());
	std::stringstream out1;
	num1.output(out1);
	ASSERT_EQ("abc3ef\n", out1.str());

	ASSERT_EQ(3, num2.getLen());
	ASSERT_EQ('-', num2.getSign());
	std::stringstream out2;
	num2.output(out2);
	ASSERT_EQ("-29a\n", out2.str());

	ASSERT_EQ(2, num3.getLen());
	ASSERT_EQ('-', num3.getSign());
	std::stringstream out3;
	num3.output(out3);
	ASSERT_EQ("-22\n", out3.str());

	ASSERT_THROW(Lab3a::Hex num5("ffffafbcde162737273773fff"), std::length_error);

	ASSERT_THROW(Lab3a::Hex num6("sss"), std::invalid_argument);
}

TEST(HexConstructors, CopyConstructor) {
	Lab3a::Hex num1(0x3cb4);
	Lab3a::Hex num2;
	num2 = num1;
	std::stringstream out1;
	num2.output(out1);
	ASSERT_EQ("3cb4\n", out1.str());
}

TEST(OtherMethods, Add) {
	Lab3a::Hex first("+1c52");
	Lab3a::Hex second("+891");
	Lab3a::Hex result = first.Add(second);
	std::stringstream out1;
	result.output(out1);
	ASSERT_EQ("24E3\n", out1.str());

	first = "+a5bfffffffffff";
	second = "+ffffffffffffc7";
	ASSERT_THROW(first.Add(second), std::exception);

	first = "+c5b";
	second = "-a7e";
	result = first.Add(second);
	std::stringstream out2;
	result.output(out2);
	ASSERT_EQ("1DD\n", out2.str());

	first = "-A59";
	second = "+1ba";
	result = first.Add(second);
	std::stringstream out3;
	result.output(out3);
	ASSERT_EQ("-89F\n", out3.str());

	first = "-5ac";
	second = "-c44e";
	result = first.Add(second);
	std::stringstream out4;
	result.output(out4);
	ASSERT_EQ("-C9FA\n", out4.str());

	first = "-a5bfffffffffff";
	second = "-ffffffffffffc7";
	ASSERT_THROW(first.Add(second), std::exception);
}

TEST(OtherMethods, Subtract) {
	Lab3a::Hex first("+43a");
	Lab3a::Hex second("+3fec");
	Lab3a::Hex result = first.Subtract(second);
	std::stringstream out1;
	result.output(out1);
	ASSERT_EQ("-3BB2\n", out1.str());
	
	first = "-bcef";
	second = "+42f";
	result = first.Subtract(second);
	std::stringstream out2;
	result.output(out2);
	ASSERT_EQ("-C11E\n", out2.str());

	first = "-a5bfffffffffff";
	second = "+ffffffffffffc7";
	ASSERT_THROW(first.Subtract(second), std::exception);
}

TEST(OtherMethods, Parity) {
	Lab3a::Hex first("+43a");
	Lab3a::Hex second("-3feb");
	Lab3a::Hex third("0");
	ASSERT_EQ(true, first.Parity());
	ASSERT_EQ(false, second.Parity());
	ASSERT_EQ(true, third.Parity());
}

TEST(OtherMethods, CompareAbs) {
	Lab3a::Hex first("+43a");
	Lab3a::Hex second("+3fec");
	ASSERT_EQ(-1, first.Compare(second, true));

	first = "-bcef";
	second = "+42f";
	ASSERT_EQ(1, first.Compare(second, true));

	first = "-aaa";
	second = "+aaa";
	ASSERT_EQ(0, first.Compare(second, true));
}

TEST(OtherMethods, Compare) {
	Lab3a::Hex first("+fa2a");
	Lab3a::Hex second("+3fec");
	ASSERT_EQ(1, first.Compare(second));

	first = "-bcef";
	second = "+42f";
	ASSERT_EQ(-1, first.Compare(second));

	first = "-abcd";
	second = "-abcd";
	ASSERT_EQ(0, first.Compare(second)); 
}

TEST(OtherMethods, MoveRight) {
	Lab3a::Hex a(0x5624f), b(0x56), c, e(-0x8902), f(-0x890);
	a.Move_right(3);
	ASSERT_EQ(0, a.Compare(b));
	a.Move_right(20);
	ASSERT_EQ(0, a.Compare(c));	
	e.Move_right(1);
	ASSERT_EQ(0, e.Compare(f));


	ASSERT_THROW(a.Move_right(-10), std::exception);
} 

TEST(OtherMethods, MoveLeft) {
	Lab3a::Hex d(0x5624f00);
	Lab3a::Hex a(0x5624f), b(0x56), c, e(-0x2451000), f(-0x2451);
	a.Move_left(2);
	ASSERT_EQ(0, a.Compare(d));
	b.Move_left(35);
	ASSERT_EQ(0, b.Compare(c));
	f.Move_left(3);
	ASSERT_EQ(0, f.Compare(e));

	ASSERT_THROW(a.Move_left(-10), std::exception);	
} 

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
} 