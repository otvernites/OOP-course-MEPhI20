#include <iostream>
#include "../library2/Lemniscata.h"
#include <tchar.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int _tmain(int argc, _TCHAR* argv[]) {

	Figure::Lemniscata l(5);
	double rad, angle, a;

	std::cout << "---Lemniscata---" << std::endl;
	std::cout << "a = " << l.getA() << std::endl;
	std::cout << "Area: " << l.area() << std::endl;

	std::cout << "Enter the angle value in degrees: " << std::endl;
	Figure::getNum(angle);

	try {
		std::cout << "Distance: " << l.distance(angle) << std::endl;
		std::cout << "Radius of curvature versus angle: " << l.curvePhi(angle) << std::endl;
		std::cout << "Polar sector area: " << l.areaS(angle) << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cin.clear();
	std::cout << "Enter the polar radius: " << std::endl;
	Figure::getNum(rad);

	try {
		std::cout << "Radius of curvature versus polar radius: " << l.curveR(rad) << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cin.clear();
	std::cout << "Enter new parameter - a - to continue: " << std::endl;
	Figure::getNum(a);

	try {
		l.setA(a);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << "New a = " << l.getA() << std::endl;
	_CrtDumpMemoryLeaks();
	return 0;
}

