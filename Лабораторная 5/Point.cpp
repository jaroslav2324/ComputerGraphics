#include "Point.h"

void Point::copyPointValues(Point& point) {
	x = point.x;
	y = point.y;
	z = point.z;
}

void Point::sumPoints(Point& point) {

	x += point.x;
	y += point.y;
	z += point.z;
}

void Point::decPoints(Point& point) {

	x -= point.x;
	y -= point.y;
	z -= point.z;
}

void Point::increaseX(double val) {
	x += val;
}

void Point::increaseY(double val) {
	y += val;
}

void Point::increaseZ(double val) {
	z += val;
}

void Point::decreaseX(double val) {
	x -= val;
}

void Point::decreaseY(double val) {
	y -= val;
}

void Point::decreaseZ(double val) {
	z -= val;
}

