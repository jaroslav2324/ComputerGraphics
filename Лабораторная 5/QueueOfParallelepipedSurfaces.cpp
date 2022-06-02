
#include "QueueOfParallelepipedSurfaces.h"

QueueOfParallelepipedSurfaces::QueueOfParallelepipedSurfaces(Parallelepiped& par) {

	arr = new ParallelepipedSurface * [6];

	arr[0] = new ParallelepipedSurface(par.point1, par.point2, par.point3, par.point4);
	arr[1] = new ParallelepipedSurface(par.point1, par.point2, par.point6, par.point5);
	arr[2] = new ParallelepipedSurface(par.point1, par.point4, par.point8, par.point5);
	arr[3] = new ParallelepipedSurface(par.point3, par.point4, par.point8, par.point7);
	arr[4] = new ParallelepipedSurface(par.point2, par.point3, par.point7, par.point6);
	arr[5] = new ParallelepipedSurface(par.point5, par.point6, par.point7, par.point8);

	arr[0]->R = 255;
	arr[0]->G = 255;
	arr[0]->B = 0;
	arr[0]->A = 255;
		
	arr[1]->R = 0;
	arr[1]->G = 255;
	arr[1]->B = 255;
	arr[1]->A = 255;

	arr[2]->R = 255;
	arr[2]->G = 0;
	arr[2]->B = 255;
	arr[2]->A = 255;

	arr[3]->R = 0;
	arr[3]->G = 0;
	arr[3]->B = 255;
	arr[3]->A = 255;

	arr[4]->R = 255;
	arr[4]->G = 0;
	arr[4]->B = 0;
	arr[4]->A = 255;

	arr[5]->R = 0;
	arr[5]->G = 255;
	arr[5]->B = 0;
	arr[5]->A = 255;
	sortSurfacesByZcoord();
}

QueueOfParallelepipedSurfaces::~QueueOfParallelepipedSurfaces() {

	for (int i = 0; i < 6; i++)
		delete arr[i];

	delete arr;
}

void QueueOfParallelepipedSurfaces::sortSurfacesByZcoord() {

	ParallelepipedSurface* ptrSurface;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (arr[j]->centerZvalue < arr[j + 1]->centerZvalue) {
				ptrSurface = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = ptrSurface;
			}
}
