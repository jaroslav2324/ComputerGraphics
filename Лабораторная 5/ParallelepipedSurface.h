#pragma once

#include "Definitions.h"
#include "Point.h"
#include "ArrrayOfPoints.h"

struct ParallelepipedSurface {
	ParallelepipedSurface(Point& p1, Point& p2, Point& p3, Point& p4);
	~ParallelepipedSurface();
	void drawSurface(SDL_Renderer* ren, ArrayOfPoints* arrOfPoints);
	void findCenterZvalue();
	Point* point1, * point2, * point3, * point4;
	double centerZvalue;
	char R;
	char G;
	char B;
	char A;
};