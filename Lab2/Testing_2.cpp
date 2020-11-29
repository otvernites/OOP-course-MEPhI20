#include <iostream>
#include "gtest/gtest.h"
#include "../library2/Lemniscata.h"
#include <tchar.h>

//тестирование конструкторов
TEST(LemniscataConstructor, DefaultConstructor)
{
	Figure::Lemniscata l;
	ASSERT_EQ(1.0, l.getA());
}

TEST(LemniscataConstructor, InitConstructors)
{
	Figure::Lemniscata l(90);
	ASSERT_EQ(90.0, l.getA());
}

TEST(LemniscataConstructor, TestException)
{
	ASSERT_ANY_THROW(Figure::Lemniscata(0));
	ASSERT_ANY_THROW(Figure::Lemniscata(-4));
}

//тестирование других методов
TEST(LemniscataMethods, Setters) {
	Figure::Lemniscata l;

	l.setA(5);
	ASSERT_EQ(5.0, l.getA());

	l.setA(103);
	ASSERT_EQ(103.0, l.getA());

	ASSERT_ANY_THROW(l.setA(0));
	ASSERT_ANY_THROW(l.setA(-5));
}

TEST(LemniscataMethods1, Parameters)
{
	Figure::Lemniscata l;
	const double error = 0.00001;

	ASSERT_NEAR(1.17869, l.distance(23), error);
	ASSERT_NEAR(0.0, l.distance(135), error);
	ASSERT_ANY_THROW(l.distance(88));
	ASSERT_ANY_THROW(l.distance(-20));

	ASSERT_NEAR(0.66667, l.curvePhi(30), error);
	ASSERT_ANY_THROW(l.curvePhi(45));
	ASSERT_ANY_THROW(l.curvePhi(110));
	ASSERT_ANY_THROW(l.curvePhi(-30));

	ASSERT_NEAR(1.33333, l.curveR(0.5), error);
	ASSERT_ANY_THROW(l.curveR(2));
	ASSERT_ANY_THROW(l.curveR(-4));

	ASSERT_NEAR(0.43301, l.areaS(30), error);
	ASSERT_NEAR(0, l.areaS(180), error);
	ASSERT_ANY_THROW(l.areaS(88));
	ASSERT_ANY_THROW(l.areaS(-70));

	ASSERT_EQ(0.5, l.area());
}

TEST(LemniscataMethods2, Parameters)
{
	Figure::Lemniscata l(10);
	const double error = 0.00001;

	ASSERT_NEAR(10.0, l.distance(30), error);
	ASSERT_NEAR(0.0, l.distance(45), error);
	ASSERT_ANY_THROW(l.distance(120));
	ASSERT_ANY_THROW(l.distance(-66));

	ASSERT_NEAR(5.06557, l.curvePhi(15), error);
	ASSERT_ANY_THROW(l.curvePhi(135));
	ASSERT_ANY_THROW(l.curvePhi(55));
	ASSERT_ANY_THROW(l.curvePhi(-60));

	ASSERT_NEAR(7.40741, l.curveR(9), error);
	ASSERT_ANY_THROW(l.curveR(224));
	ASSERT_ANY_THROW(l.curveR(-7));

	ASSERT_NEAR(45.67727, l.areaS(33), error);
	ASSERT_NEAR(0, l.areaS(0), error);
	ASSERT_ANY_THROW(l.areaS(70));
	ASSERT_ANY_THROW(l.areaS(-10));

	ASSERT_EQ(50.0, l.area());
}

int _tmain(int argc, _TCHAR* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

