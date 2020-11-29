#include "pch.h"
#include "Lemniscata.h"
#include <exception>

namespace Figure {

	Lemniscata::Lemniscata(double arg) {
		if (arg <= 0)
			throw std::exception("Incorrect parameter value.");
		a = arg;
	}

	//устанавливает новое значение параметра "а"
	Lemniscata& Lemniscata::setA(double a0) {
		if (a0 <= 0)
			throw std::exception("Incorrect parameter value.");
		a = a0;
		return *this;
	}

	//возвращает полярный радиус
	double Lemniscata::distance(double angle) const {
		double phi = degToRad(angle);

		if (angle < 0)
			throw std::exception("Incorrect angle.");

		if ((sin(phi) < (-sqrt(2) / 2)) || (sin(phi) > (sqrt(2) / 2)))
			throw std::exception("Distance: incorrect angle."
							" Such a point doesn't exist.");

		if (round(cos(2*phi)) == 0)
			return 0;

		return a * sqrt(2 * cos(2 * phi));
	}

	//возвращает радиус кривизны в зависимости от угла 
	double Lemniscata::curvePhi(double angle) const {
		double phi = degToRad(angle);

		if (angle < 0)
			throw std::exception("Incorrect angle.");

		if ((sin(phi) < (-sqrt(2) / 2)) || (sin(phi) > (sqrt(2) / 2)))
			throw std::exception("Radius of curvature versus angle:" 
							" incorrect angle. Such a point doesn't exist.");

		if (round(cos(2 * phi)) == 0) {
			throw std::exception("Radius of curvature versus angle:"
							" incorrect angle value.");
		}
		return sqrt(2) * a / (3 * sqrt(cos(2 * phi)));
	}

	//возвращает радиус кривизны в зависимости от полярного радиуса
	double Lemniscata::curveR(double r) const {
		double rad = r;
		if ((rad <= 0) || (rad > (a * sqrt(2))))
			throw std::exception("Radius of curvature versus polar radius:"
							" incorrect radius value. Such a point doesn't exist.");
		return (2 * a * a) / (3 * rad);
	}

	//возвращает площадь полярного сектора в зависимости от угла 
	double Lemniscata::areaS(double angle) const {
		double phi = degToRad(angle);

		if (angle < 0)
			throw std::exception("Incorrect angle.");

		if ((sin(phi) < (-sqrt(2) / 2)) || (sin(phi) > (sqrt(2) / 2)))
			throw std::exception("Polar sector area: incorrect angle."
							" Such a point doesn't exist.");

		if (round(sin(2 * phi)) == 0)
			return 0;

		return a * a * sin(2 * phi) / 2;
	}

}