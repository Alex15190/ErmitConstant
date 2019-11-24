#pragma once

class MutableMatrix
{
private:
	double** matrix;
	int dim;
public:
	MutableMatrix();
	MutableMatrix(int dim, double* aij);
	MutableMatrix(int dim, double** matrix);
	~MutableMatrix();
	double det();
	MutableMatrix sub(int row, int col);


};