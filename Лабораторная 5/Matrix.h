#pragma once

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