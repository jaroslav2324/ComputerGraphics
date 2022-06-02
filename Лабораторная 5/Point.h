#pragma once

struct Point {
	double x;
	double y;
	double z;
	void copyPointValues(Point& point);
	void sumPoints(Point& point);
	void decPoints(Point& point);
	void increaseX(double val);
	void increaseY(double val);
	void increaseZ(double val);
	void decreaseX(double val);
	void decreaseY(double val);
	void decreaseZ(double val);
};
