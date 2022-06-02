#include <iostream>

#include "ArrrayOfPoints.h"


ArrayOfPoints::ArrayOfPoints() {

}

ArrayOfPoints::~ArrayOfPoints() {

	for (int i = 0; i < amountPoints; i++)
		delete pointArr[i];

	delete pointArr;
}

void  ArrayOfPoints::resizePointArr() {

	sizeArr += REALLOC_VAL;
	Point** newArr = new Point * [sizeArr];
	memset(newArr, 0, sizeArr * sizeof(Point*));
	memcpy(newArr, pointArr, (sizeArr - REALLOC_VAL) * sizeof(Point*));
	delete[] pointArr;
	pointArr = newArr;
	return;
}

void ArrayOfPoints::addPointToArr(int x, int y) {
	for (int i = 0; i < amountPoints; i++) {
		if (pointArr[i]->x == x && pointArr[i]->y == y)
			return;
	}
	Point* newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	pointArr[amountPoints] = newPoint;
	return;
}

bool ArrayOfPoints::ifPointInArr(int x, int y) {
	for (int i = 0; i < amountPoints; i++) {
		if (pointArr[i]->x == x && pointArr[i]->y == y)
			return true;
	}
	return false;
}
