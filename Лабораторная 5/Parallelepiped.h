#pragma once

#include "Definitions.h"
#include "Point.h"
#include "Matrix.h"
#include "BresenhamAndFillingFunctions.h"

class Parallelepiped {
public:
	Parallelepiped();
	Parallelepiped(const Parallelepiped& par);
	~Parallelepiped();
	void rerenderParallelepipiped(SDL_Renderer* ren);
	void moveAlongAxis(char axis);
	void moveReverseAxis(char axis);
	void rotateClockwise(char axis);
	void rotateCounterclockwise(char axis);
	void incraseScale();
	void decreaseScale();
	void printCenterCoordZ();
	Parallelepiped* createParallelepipedWithIsometricalProjection();
	friend class QueueOfParallelepipedSurfaces;
private:
	Point point1, point2, point3, point4, point5, point6, point7, point8;
	Point centerPoint;
	Matrix* matrixOfPoints = nullptr;
	void findCenter();
	void moveToCenterCoords();
	void moveFromCenterCoords();
	Matrix* createMatrixOfPoints();
	void fillPointsWithMatrix(Matrix* matrix);

};