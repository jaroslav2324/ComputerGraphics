#include "iostream"

#include "QueueOfParallelepipedSurfaces.h"
#include "Parallelepiped.h"

using std::invalid_argument;
using std::cout;
using std::endl;

Parallelepiped::Parallelepiped() {

	point1.x = 50;
	point1.y = 250;
	point1.z = 250;

	point2.x = 250;
	point2.y = 250;
	point2.z = 250;

	point3.x = 250;
	point3.y = 0;
	point3.z = 250;

	point4.x = 50;
	point4.y = 0;
	point4.z = 250;

	point5.x = 50;
	point5.y = 250;
	point5.z = 50;

	point6.x = 250;
	point6.y = 250;
	point6.z = 50;

	point7.x = 250;
	point7.y = 0;
	point7.z = 50;

	point8.x = 50;
	point8.y = 0;
	point8.z = 50;

	findCenter();
	createMatrixOfPoints();
}

/*copy costructor*/
Parallelepiped::Parallelepiped(const Parallelepiped& par) {

	point1 = par.point1;
	point2 = par.point2;
	point3 = par.point3;
	point4 = par.point4;
	point5 = par.point5;
	point6 = par.point6;
	point7 = par.point7;
	point8 = par.point8;

	centerPoint = par.centerPoint;

	matrixOfPoints = new Matrix(par.matrixOfPoints->sizeRows, par.matrixOfPoints->sizeColumns, par.matrixOfPoints->matrix);

}

Parallelepiped::~Parallelepiped() {

	delete(matrixOfPoints);
}

void Parallelepiped::rerenderParallelepipiped(SDL_Renderer* ren) {

	SDL_RenderClear(ren);

	QueueOfParallelepipedSurfaces queue(*this);
	ArrayOfPoints* arrOfPoints;

	arrOfPoints = new ArrayOfPoints;
	SDL_SetRenderDrawColor(ren, queue.arr[0]->R, queue.arr[0]->G, queue.arr[0]->B, queue.arr[0]->A);

	queue.arr[0]->drawSurface(ren, arrOfPoints);
	fillParallelepiped(ren, queue.arr[0], arrOfPoints);
	SDL_RenderPresent(ren);

	delete arrOfPoints;


	arrOfPoints = new ArrayOfPoints;
	SDL_SetRenderDrawColor(ren, queue.arr[1]->R, queue.arr[1]->G, queue.arr[1]->B, queue.arr[1]->A);

	queue.arr[1]->drawSurface(ren, arrOfPoints);
	fillParallelepiped(ren, queue.arr[1], arrOfPoints);
	SDL_RenderPresent(ren);

	delete arrOfPoints;


	arrOfPoints = new ArrayOfPoints;
	SDL_SetRenderDrawColor(ren, queue.arr[2]->R, queue.arr[2]->G, queue.arr[2]->B, queue.arr[2]->A);

	queue.arr[2]->drawSurface(ren, arrOfPoints);
	fillParallelepiped(ren, queue.arr[2], arrOfPoints);
	SDL_RenderPresent(ren);

	delete arrOfPoints;


	arrOfPoints = new ArrayOfPoints;
	SDL_SetRenderDrawColor(ren, queue.arr[3]->R, queue.arr[3]->G, queue.arr[3]->B, queue.arr[3]->A);

	queue.arr[3]->drawSurface(ren, arrOfPoints);
	fillParallelepiped(ren, queue.arr[3], arrOfPoints);
	SDL_RenderPresent(ren);

	delete arrOfPoints;


	arrOfPoints = new ArrayOfPoints;
	SDL_SetRenderDrawColor(ren, queue.arr[4]->R, queue.arr[4]->G, queue.arr[4]->B, queue.arr[4]->A);

	queue.arr[4]->drawSurface(ren, arrOfPoints);
	fillParallelepiped(ren, queue.arr[4], arrOfPoints);
	SDL_RenderPresent(ren);

	delete arrOfPoints;


	arrOfPoints = new ArrayOfPoints;
	SDL_SetRenderDrawColor(ren, queue.arr[5]->R, queue.arr[5]->G, queue.arr[5]->B, queue.arr[5]->A);

	queue.arr[5]->drawSurface(ren, arrOfPoints);
	fillParallelepiped(ren, queue.arr[5], arrOfPoints);
	SDL_RenderPresent(ren);

	delete arrOfPoints;


	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	SDL_RenderPresent(ren);

	return;
}

void Parallelepiped::findCenter() {

	centerPoint.x = (point1.x + point2.x + point3.x + point4.x + point5.x + point6.x + point7.x + point8.x) / 8;
	centerPoint.y = (point1.y + point2.y + point3.y + point4.y + point5.y + point6.y + point7.y + point8.y) / 8;
	centerPoint.z = (point1.z + point2.z + point3.z + point4.z + point5.z + point6.z + point7.z + point8.z) / 8;
}

void Parallelepiped::moveToCenterCoords() {

	point1.decPoints(centerPoint);
	point2.decPoints(centerPoint);
	point3.decPoints(centerPoint);
	point4.decPoints(centerPoint);
	point5.decPoints(centerPoint);
	point6.decPoints(centerPoint);
	point7.decPoints(centerPoint);
	point8.decPoints(centerPoint);

}

void Parallelepiped::moveFromCenterCoords() {


	point1.sumPoints(centerPoint);
	point2.sumPoints(centerPoint);
	point3.sumPoints(centerPoint);
	point4.sumPoints(centerPoint);
	point5.sumPoints(centerPoint);
	point6.sumPoints(centerPoint);
	point7.sumPoints(centerPoint);
	point8.sumPoints(centerPoint);
}

/*also returns pointer to this matrix*/
Matrix* Parallelepiped::createMatrixOfPoints() {

	if (matrixOfPoints != nullptr)
		delete matrixOfPoints;

	double matrixArray[32] = { point1.x, point1.y, point1.z, 1,
							   point2.x, point2.y, point2.z, 1,
							   point3.x, point3.y, point3.z, 1,
							   point4.x, point4.y, point4.z, 1,
							   point5.x, point5.y, point5.z, 1,
							   point6.x, point6.y, point6.z, 1,
							   point7.x, point7.y, point7.z, 1,
							   point8.x, point8.y, point8.z, 1 };
	matrixOfPoints = new Matrix(8, 4, matrixArray);

	return matrixOfPoints;
}

/*matrix 8x4 with x, y, z, 1 columns*/
void Parallelepiped::fillPointsWithMatrix(Matrix* matrix) {

	point1.x = matrix->matrix[0];
	point1.y = matrix->matrix[1];
	point1.z = matrix->matrix[2];

	point2.x = matrix->matrix[4];
	point2.y = matrix->matrix[5];
	point2.z = matrix->matrix[6];

	point3.x = matrix->matrix[8];
	point3.y = matrix->matrix[9];
	point3.z = matrix->matrix[10];

	point4.x = matrix->matrix[12];
	point4.y = matrix->matrix[13];
	point4.z = matrix->matrix[14];

	point5.x = matrix->matrix[16];
	point5.y = matrix->matrix[17];
	point5.z = matrix->matrix[18];

	point6.x = matrix->matrix[20];
	point6.y = matrix->matrix[21];
	point6.z = matrix->matrix[22];

	point7.x = matrix->matrix[24];
	point7.y = matrix->matrix[25];
	point7.z = matrix->matrix[26];

	point8.x = matrix->matrix[28];
	point8.y = matrix->matrix[29];
	point8.z = matrix->matrix[30];
}

/*axis - x, y or z*/
void Parallelepiped::moveAlongAxis(char axis) {

	switch (axis) {
	case 'x':
		point1.increaseX(SHIFT_VALUE);
		point2.increaseX(SHIFT_VALUE);
		point3.increaseX(SHIFT_VALUE);
		point4.increaseX(SHIFT_VALUE);
		point5.increaseX(SHIFT_VALUE);
		point6.increaseX(SHIFT_VALUE);
		point7.increaseX(SHIFT_VALUE);
		point8.increaseX(SHIFT_VALUE);
		break;
	case 'y':
		point1.increaseY(SHIFT_VALUE);
		point2.increaseY(SHIFT_VALUE);
		point3.increaseY(SHIFT_VALUE);
		point4.increaseY(SHIFT_VALUE);
		point5.increaseY(SHIFT_VALUE);
		point6.increaseY(SHIFT_VALUE);
		point7.increaseY(SHIFT_VALUE);
		point8.increaseY(SHIFT_VALUE);
		break;
	case 'z':
		point1.increaseZ(SHIFT_VALUE);
		point2.increaseZ(SHIFT_VALUE);
		point3.increaseZ(SHIFT_VALUE);
		point4.increaseZ(SHIFT_VALUE);
		point5.increaseZ(SHIFT_VALUE);
		point6.increaseZ(SHIFT_VALUE);
		point7.increaseZ(SHIFT_VALUE);
		point8.increaseZ(SHIFT_VALUE);
		break;
	default:
		throw invalid_argument("Wrong axis to move!");
	}

	findCenter();
	createMatrixOfPoints();
}

void Parallelepiped::moveReverseAxis(char axis) {

	switch (axis) {
	case 'x':
		point1.decreaseX(SHIFT_VALUE);
		point2.decreaseX(SHIFT_VALUE);
		point3.decreaseX(SHIFT_VALUE);
		point4.decreaseX(SHIFT_VALUE);
		point5.decreaseX(SHIFT_VALUE);
		point6.decreaseX(SHIFT_VALUE);
		point7.decreaseX(SHIFT_VALUE);
		point8.decreaseX(SHIFT_VALUE);
		break;
	case 'y':
		point1.decreaseY(SHIFT_VALUE);
		point2.decreaseY(SHIFT_VALUE);
		point3.decreaseY(SHIFT_VALUE);
		point4.decreaseY(SHIFT_VALUE);
		point5.decreaseY(SHIFT_VALUE);
		point6.decreaseY(SHIFT_VALUE);
		point7.decreaseY(SHIFT_VALUE);
		point8.decreaseY(SHIFT_VALUE);
		break;
	case 'z':
		point1.decreaseZ(SHIFT_VALUE);
		point2.decreaseZ(SHIFT_VALUE);
		point3.decreaseZ(SHIFT_VALUE);
		point4.decreaseZ(SHIFT_VALUE);
		point5.decreaseZ(SHIFT_VALUE);
		point6.decreaseZ(SHIFT_VALUE);
		point7.decreaseZ(SHIFT_VALUE);
		point8.decreaseZ(SHIFT_VALUE);
		break;
	default:
		throw invalid_argument("Wrong axis to move!");
	}

	findCenter();
	createMatrixOfPoints();
}

void Parallelepiped::rotateClockwise(char axis) {

	moveToCenterCoords();
	createMatrixOfPoints();

	switch (axis) {
	case 'x':
	{
		double matrixArray[16] = { 1,   0,                 0,                0,
								   0,  cos(ROTATE_VALUE), sin(ROTATE_VALUE), 0,
								   0, -sin(ROTATE_VALUE), cos(ROTATE_VALUE), 0,
								   0,   0,                 0,                1 };
		Matrix* M = new Matrix(4, 4, matrixArray);
		Matrix* newMatrix = *matrixOfPoints * *M;
		fillPointsWithMatrix(newMatrix);
		delete M;
		break;
	}
	case 'y':
	{
		double matrixArray[16] = { cos(ROTATE_VALUE), 0, sin(ROTATE_VALUE), 0,
									0,				  1,  0,				0,
								  -sin(ROTATE_VALUE), 0, cos(ROTATE_VALUE), 0,
									0,				  0,  0,                1 };
		Matrix* M = new Matrix(4, 4, matrixArray);
		Matrix* newMatrix = *matrixOfPoints * *M;
		fillPointsWithMatrix(newMatrix);
		delete M;
		break;
	}
	case 'z':
	{
		double matrixArray[16] = { cos(ROTATE_VALUE), sin(ROTATE_VALUE), 0, 0,
								  -sin(ROTATE_VALUE), cos(ROTATE_VALUE), 0,	0,
									0,				   0,				 1, 0,
									0,				   0,				 0, 1 };
		Matrix* M = new Matrix(4, 4, matrixArray);
		Matrix* newMatrix = *matrixOfPoints * *M;
		fillPointsWithMatrix(newMatrix);
		delete M;
		break;
	}
	default:
		throw invalid_argument("Wrong rotation axis!");
	}

	moveFromCenterCoords();
	createMatrixOfPoints();
	findCenter();
}

void Parallelepiped::rotateCounterclockwise(char axis) {

	moveToCenterCoords();
	createMatrixOfPoints();

	switch (axis) {
	case 'x':
	{
		double matrixArray[16] = { 1,   0,                 0,                0,
								   0, cos(ROTATE_VALUE), -sin(ROTATE_VALUE), 0,
								   0, sin(ROTATE_VALUE),  cos(ROTATE_VALUE), 0,
								   0,   0,                 0,                1 };
		Matrix* M = new Matrix(4, 4, matrixArray);
		Matrix* newMatrix = *matrixOfPoints * *M;
		fillPointsWithMatrix(newMatrix);
		delete M;
		break;
	}
	case 'y':
	{
		double matrixArray[16] = { cos(ROTATE_VALUE), 0, -sin(ROTATE_VALUE), 0,
									0,				  1,  0,				 0,
								   sin(ROTATE_VALUE), 0,  cos(ROTATE_VALUE), 0,
									0,				  0,  0,                 1 };
		Matrix* M = new Matrix(4, 4, matrixArray);
		Matrix* newMatrix = *matrixOfPoints * *M;
		fillPointsWithMatrix(newMatrix);
		delete M;
		break;
	}
	case 'z':
	{
		double matrixArray[16] = { cos(ROTATE_VALUE), -sin(ROTATE_VALUE), 0, 0,
								   sin(ROTATE_VALUE),  cos(ROTATE_VALUE), 0, 0,
									0,				   0,				  1, 0,
									0,				   0,				  0, 1 };
		Matrix* M = new Matrix(4, 4, matrixArray);
		Matrix* newMatrix = *matrixOfPoints * *M;
		fillPointsWithMatrix(newMatrix);
		delete M;
		break;
	}
	default:
		throw invalid_argument("Wrong rotation axis!");
	}

	moveFromCenterCoords();
	createMatrixOfPoints();
	findCenter();
}

void Parallelepiped::incraseScale() {

	moveToCenterCoords();

	point1.x *= 1 + ADD_SCALE;
	point1.y *= 1 + ADD_SCALE;
	point1.z *= 1 + ADD_SCALE;

	point2.x *= 1 + ADD_SCALE;
	point2.y *= 1 + ADD_SCALE;
	point2.z *= 1 + ADD_SCALE;

	point3.x *= 1 + ADD_SCALE;
	point3.y *= 1 + ADD_SCALE;
	point3.z *= 1 + ADD_SCALE;

	point4.x *= 1 + ADD_SCALE;
	point4.y *= 1 + ADD_SCALE;
	point4.z *= 1 + ADD_SCALE;

	point5.x *= 1 + ADD_SCALE;
	point5.y *= 1 + ADD_SCALE;
	point5.z *= 1 + ADD_SCALE;

	point6.x *= 1 + ADD_SCALE;
	point6.y *= 1 + ADD_SCALE;
	point6.z *= 1 + ADD_SCALE;

	point7.x *= 1 + ADD_SCALE;
	point7.y *= 1 + ADD_SCALE;
	point7.z *= 1 + ADD_SCALE;

	point8.x *= 1 + ADD_SCALE;
	point8.y *= 1 + ADD_SCALE;
	point8.z *= 1 + ADD_SCALE;

	moveFromCenterCoords();
	findCenter();
	createMatrixOfPoints();
}

void Parallelepiped::decreaseScale() {

	moveToCenterCoords();

	point1.x *= 1 - ADD_SCALE;
	point1.y *= 1 - ADD_SCALE;
	point1.z *= 1 - ADD_SCALE;

	point2.x *= 1 - ADD_SCALE;
	point2.y *= 1 - ADD_SCALE;
	point2.z *= 1 - ADD_SCALE;

	point3.x *= 1 - ADD_SCALE;
	point3.y *= 1 - ADD_SCALE;
	point3.z *= 1 - ADD_SCALE;

	point4.x *= 1 - ADD_SCALE;
	point4.y *= 1 - ADD_SCALE;
	point4.z *= 1 - ADD_SCALE;

	point5.x *= 1 - ADD_SCALE;
	point5.y *= 1 - ADD_SCALE;
	point5.z *= 1 - ADD_SCALE;

	point6.x *= 1 - ADD_SCALE;
	point6.y *= 1 - ADD_SCALE;
	point6.z *= 1 - ADD_SCALE;

	point7.x *= 1 - ADD_SCALE;
	point7.y *= 1 - ADD_SCALE;
	point7.z *= 1 - ADD_SCALE;

	point8.x *= 1 - ADD_SCALE;
	point8.y *= 1 - ADD_SCALE;
	point8.z *= 1 - ADD_SCALE;

	moveFromCenterCoords();
	findCenter();
	createMatrixOfPoints();
}

void Parallelepiped::printCenterCoordZ() {

	cout << "Current z coordinate of center: " << centerPoint.z << endl;
	return;
}

Parallelepiped* Parallelepiped::createParallelepipedWithIsometricalProjection() {

	Parallelepiped* newParallelepiped = new Parallelepiped(*this);

	newParallelepiped->findCenter();

	newParallelepiped->moveToCenterCoords();
	newParallelepiped->createMatrixOfPoints();

	double theta = (double)45 / 180 * M_PI;
	double fi = (double)45 / 180 * M_PI;

	double matrixArray[16] = { cos(theta), sin(theta) * sin(fi), -sin(theta) * cos(fi), 0,
								  0,	           cos(fi),		          sin(fi),      0,
							  sin(theta),  -cos(theta) * sin(fi), cos(theta) * cos(fi), 0,
								  0,				 0,						 0,			1 };

	Matrix* M = new Matrix(4, 4, matrixArray);
	Matrix* newMatrix = *matrixOfPoints * *M;
	newParallelepiped->fillPointsWithMatrix(newMatrix);
	delete M;

	newParallelepiped->moveFromCenterCoords();
	newParallelepiped->createMatrixOfPoints();
	newParallelepiped->findCenter();

	return newParallelepiped;
}


