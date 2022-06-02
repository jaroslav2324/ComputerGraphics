#include <iostream>

#include "Matrix.h"

using std::cout;
using std::endl;

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
