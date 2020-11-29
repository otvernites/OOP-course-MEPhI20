#pragma once

#ifndef _LEMNISCATA_H_
#define _LEMNISCATA_H_
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

namespace Figure {

	template <class T>
	double getNum(T& a) {
		std::cin >> a;
		while (!std::cin.good()) {
			std::cin.clear();
			std::cout << "Invalid input, try again: \n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			std::cin >> a;
		}
		return 1;
	}

	class Lemniscata {
	private:
		double a;
	public:
		//пустой и инициализирующий конструктор
		Lemniscata(double arg = 1);
		Lemniscata& setA(double a0); 
		double getA() const { return a; }  
		//другие методы
		double distance(double angle) const; 
		double curvePhi(double angle) const; 
		double curveR(double r) const; 
		double areaS(double angle) const; 
		double area() const { return a * a / 2; } //площадь лемнискаты
		double degToRad(const double& angle) const { return (angle * M_PI) / 180; }  //перевод градусов в радианы
	};
}
#endif 

