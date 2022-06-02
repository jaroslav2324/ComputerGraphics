#include <iostream>
#include <exception>
#include <math.h>
#include <conio.h>
#include <cstring>
#include <SDL.h>

#define SHIFT_VALUE 10
#define ROTATE_VALUE double(3) / 180 * M_PI
#define ADD_SCALE 0.2

using namespace std;



struct point {
	double x;
	double y;
	double z;
	void sumPoints(point& point);
	void decPoints(point& point);
	void increaseX(double val);
	void increaseY(double val);
	void increaseZ(double val);
	void decreaseX(double val);
	void decreaseY(double val);
	void decreaseZ(double val);
};

void point::sumPoints(point& point) {

	x += point.x;
	y += point.y;
	z += point.z;
}

void point::decPoints(point& point) {

	x -= point.x;
	y -= point.y;
	z -= point.z;
}

void point::increaseX(double val) {
	x += val;
}

void point::increaseY(double val) {
	y += val;
}

void point::increaseZ(double val) {
	z += val;
}

void point::decreaseX(double val) {
	x -= val;
}

void point::decreaseY(double val) {
	y -= val;
}

void point::decreaseZ(double val) {
	z -= val;
}



class Matrix {
public:
	Matrix(int sizeRows, int sizeColumns);
	Matrix(int sizeRows, int sizeColumns, double* initialisationMatrix);
	~Matrix();
	void fillMatrix(int sizeRows, int sizeColumns, double* initialisationMatrix);
	void print();
	Matrix* operator* (Matrix& m2);
	friend class Parallelepiped;
private:
	double* matrix;
	int sizeRows;
	int sizeColumns;

};

/*matrix of zeros*/
Matrix::Matrix(int sizeRows, int sizeColumns) {

	matrix = new double[sizeRows * sizeColumns];
	this->sizeColumns = sizeColumns;
	this->sizeRows = sizeRows;
	for (int i = 0; i < sizeColumns * sizeRows; i++)
		matrix[i] = 0;
}

/*custom matrix*/
Matrix::Matrix(int sizeRows, int sizeColumns, double* initialisationMatrix) {

	matrix = new double[sizeRows * sizeColumns];
	this->sizeColumns = sizeColumns;
	this->sizeRows = sizeRows;
	for (int i = 0; i < sizeColumns * sizeRows; i++)
		matrix[i] = initialisationMatrix[i];
}

Matrix::~Matrix() {

	delete[] matrix;
}

void Matrix::fillMatrix(int sizeRows, int sizeColumns, double* initialisationMatrix) {

	if (sizeRows != this->sizeRows || sizeColumns != this->sizeColumns)
		throw std::invalid_argument("Wrong initialisation matrix! Are you sure you enter correct size?");

	for (int i = 0; i < sizeRows * sizeColumns; i++)
		matrix[i] = initialisationMatrix[i];
}

Matrix* Matrix::operator* (Matrix& m2) {

	double* newMatrix = new double[sizeRows * m2.sizeColumns];
	int newMatrixIndex = 0;
	/*muliply matrixes*/
	for (int i = 0; i < sizeRows; i++) {
		for (int j = 0; j < m2.sizeColumns; j++) {
			double result = 0;
			int m = i * sizeColumns, n = j;
			for (int k = 0; k < sizeColumns; k++, m++, n += m2.sizeColumns)
				result += matrix[m] * m2.matrix[n];
			newMatrix[newMatrixIndex] = result;
			newMatrixIndex++;
		}
	}

	/*create new matrix*/
	Matrix* M = new Matrix(sizeRows, m2.sizeColumns, newMatrix);
	/*delete newMatrix*/

	delete[] newMatrix;

	return M;
}

void Matrix::print() {

	for (int i = 0; i < sizeRows; i++) {
		for (int j = 0; j < sizeColumns; j++) {
			cout << matrix[i * sizeColumns + j] << ' ';
		}
		cout << endl;
	}
}



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
private:
	point point1, point2, point3, point4, point5, point6, point7, point8;
	point centerPoint;
	Matrix* matrixOfPoints = nullptr;
	void findCenter();
	void moveToCenterCoords();
	void moveFromCenterCoords();
	Matrix* createMatrixOfPoints();
	void fillPointsWithMatrix(Matrix* matrix);

};

/*default values*/
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

	SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);

	SDL_RenderDrawLine(ren, point1.x, point1.y, point2.x, point2.y);
	SDL_RenderDrawLine(ren, point2.x, point2.y, point3.x, point3.y);
	SDL_RenderDrawLine(ren, point3.x, point3.y, point4.x, point4.y);
	SDL_RenderDrawLine(ren, point1.x, point1.y, point4.x, point4.y);

	SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);

	SDL_RenderDrawLine(ren, point1.x, point1.y, point5.x, point5.y);
	SDL_RenderDrawLine(ren, point2.x, point2.y, point6.x, point6.y);
	SDL_RenderDrawLine(ren, point3.x, point3.y, point7.x, point7.y);
	SDL_RenderDrawLine(ren, point4.x, point4.y, point8.x, point8.y);

	SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);

	SDL_RenderDrawLine(ren, point5.x, point5.y, point6.x, point6.y);
	SDL_RenderDrawLine(ren, point6.x, point6.y, point7.x, point7.y);
	SDL_RenderDrawLine(ren, point7.x, point7.y, point8.x, point8.y);
	SDL_RenderDrawLine(ren, point5.x, point5.y, point8.x, point8.y);

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



int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}

	SDL_Window* win = SDL_CreateWindow("lab4", 20, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
		std::cout << "Error with window";
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
		std::cout << "Error with renderer";

	Parallelepiped par;
	Parallelepiped* isPar;

	while (1) {

		isPar = par.createParallelepipedWithIsometricalProjection();
		isPar->rerenderParallelepipiped(ren);
		delete(isPar);

		char c = _getch();
		std::cout << c;

		switch (c) {
		case 'w':
			par.moveReverseAxis('y');
			break;
		case 's':
			par.moveAlongAxis('y');
			break;
		case 'd':
			par.moveAlongAxis('x');
			break;
		case 'a':
			par.moveReverseAxis('x');
			break;
		case 'e':
			par.moveReverseAxis('z');
			par.printCenterCoordZ();
			break;
		case 'q':
			par.moveAlongAxis('z');
			par.printCenterCoordZ();
			break;
		case 'x':
			par.incraseScale();
			break;
		case 'z':
			par.decreaseScale();
			break;
		case 'i':
			par.rotateCounterclockwise('x');
			break;
		case 'o':
			par.rotateClockwise('x');
			break;
		case 'k':
			par.rotateCounterclockwise('y');
			break;
		case 'l':
			par.rotateClockwise('y');
			break;
		case 'n':
			par.rotateClockwise('z');
			break;
		case 'm':
			par.rotateCounterclockwise('z');
			break;
		case '1':
			return 0;
		default:
			std::cout << std::endl << "Wrong key!" << std::endl;
		}
	}

	return 0;
}	
