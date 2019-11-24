#include "MutableMatrix.h"
#include <iostream>
#include <ctime>
using namespace std;

MutableMatrix::MutableMatrix()
{
	double temp;
	cout << "Enter dimention of matrix";
	cin >> this->dim;
	this->matrix = new double* [this->dim];
	for (int i = 0; i < this->dim; i++) {
		this->matrix[i] = new double[this->dim];
		for (int j = 0; j <= i ; j++) {
			if (i = !j) {
				cout << "Enter element of matrix in index" << i + 1 << j + 1;
				cin >> temp;
				this->matrix[i][j] = (double)temp;
				this->matrix[j][i] = (double)temp;
			}
			else this->matrix[i][j] = 1;
		}
	}
}

MutableMatrix::MutableMatrix(int dim, double* aij)
{
	int counter = 0;
	this->dim = dim;
	this->matrix = new double* [this->dim];
	for (int i = 0; i < this->dim; i++) {
		this->matrix[i] = new double[this->dim];
		for (int j = 0; j <= i; j++) {
			if (i == j) this->matrix[i][j] = 1;
			else {
				this->matrix[i][j] = aij[counter];
				this->matrix[j][i] = aij[counter];
			}
			counter++;
		}
	}
}

MutableMatrix::MutableMatrix(int dim, double** matrix) {
	if (dim < 1) {
		cerr << "[Matrix(int, double&)] invalid argument exception: dim must be positive" << endl;
		throw "[Matrix(int, double&)] invalid argument exception: dim must be positive";
	}
	
	this->dim = dim;
	this->matrix = new double* [dim];
	for (int i = 0; i < this->dim; i++) {
		this->matrix[i] = new double[dim];
		for (int j = 0; j < this->dim; j++) {
			this->matrix[i][j] = matrix[i][j];
		}
	}
}

MutableMatrix::~MutableMatrix()
{
	for (int i = 0; i < this->dim; i++)
		delete this->matrix[i];
	delete this->matrix;
}

double MutableMatrix::det()
{
	srand(time(NULL));
	double det = 0;
	if (this->dim == 1 ) {
		det = this->matrix[0][0];
	}
	else if (this->dim == 2) {
		det = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
	}
	else {
		bool isRow = rand() % 2;
		if (isRow) {
			int row = rand() % this->dim;
			for (int i = 0; i < this->dim; i++) {
				if (this->matrix[row][i] != 0) {
					MutableMatrix s = this->sub(row, i);
					int n = (i + row) % 2 == 0 ? 1 : -1;
					det += n * this->matrix[row][i] * this->det(s);
				}
			}
		}
		else {
			int col = rand() % this->dim;
			for (int i = 0; i < this->dim; i++) {
				if (this->matrix[i][col] != 0) {
					MutableMatrix s = this->sub(i, col);
					int n = (i + col) % 2 == 0 ? 1 : -1;
					det += n * this->matrix[i][col] * this->det(s);
				}
			}
		}
	}
	return det;
}

MutableMatrix MutableMatrix::sub(int row, int col) {
	if (this->dim == 1 ) {
		cerr << "[Matrix sub] invalid matrix exception: matrix must have more than one rows and cols" << endl;
		throw "[Matrix sub] invalid matrix exception: matrix must have more than one rows and cols";
	}
	if (row < 0 || col < 0 || row >= this->dim || col >= this->dim) {
		cerr << "[Matrix sub] invalid argument exception: invalid row or col" << endl;
		throw "[Matrix sub] invalid argument exception: invalid row or col";
	}
	double** m = new double* [this->dim - 1];
	for (int i = 0, k = 0; i < this->dim; i++) {
		if (i != row) {
			m[k] = new double[this->dim - 1];
			for (int j = 0, l = 0; j < this->dim; j++) {
				if (j != col) {
					m[k][l] = this->matrix[i][j];
					l++;
				}
			}
			k++;
		}
	}
	return MutableMatrix(this->dim - 1, m);
}