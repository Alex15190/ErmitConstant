#pragma once

class MutableMatrix
{
private:
	double** matrix;
	int dim;
	double _det(MutableMatrix& m);
public:
	MutableMatrix();
	MutableMatrix(int dim, double* aij);
	MutableMatrix(int dim, double** matrix);
	MutableMatrix(int dim, double* aij, bool special);
	~MutableMatrix();
	double det();
	MutableMatrix sub(int row, int col);
	//friend double minDet(MutableMatrix m);
	void print();

};