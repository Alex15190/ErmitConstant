#include "MutableMatrix.h"
#include <iostream>
#include <ctime>
using namespace std;

/*template <typename typed, size_t n> void size(typed(&a)[n])
{
	for (size_t q = 0; q < n; ++q)
		cout << a[q] << ' ';

	cout << '\n';
}*/

MutableMatrix::MutableMatrix()
{
	double temp = 0;
	cout << "Enter dimention of matrix ";
	cin >> this->dim;
	this->matrix = new double* [this->dim];
	for (size_t i = 0; i < this->dim; ++i) {
		this->matrix[i] = new double[this->dim];
	}

	//инициализация

	for (size_t i = 0; i < this->dim; ++i) {
		for (size_t j = 0; j <= i; ++j) {
			if (i == j) this->matrix[i][i] = 1;
			else {
				std::cout << "Matrix[" << i << "][" << j << "] = " << "Matrix[" << j << "][" << i << "] = ";
				double temp;
				std::cin >> temp;
				this->matrix[i][j] = temp;
				this->matrix[j][i] = temp;
			}
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

MutableMatrix::MutableMatrix(int dim, double* aij, bool special) {
	if (special) {
		int counter = 0;
		this->dim = dim;
		this->matrix = new double* [this->dim];
		for (int i = 0; i < this->dim; i++) {
			this->matrix[i] = new double[this->dim];
			for (int j = 0; j <= i; j++) {
				if (i == j) this->matrix[i][j] = 1;
				/*else if (j==0 && i == 2) {
					this->matrix[i][j] = (aij[counter] - 0.5)/2;
					this->matrix[j][i] = (aij[counter] - 0.5)/2;
				}*/
				else {
					this->matrix[i][j] = (aij[counter] - 0.5);
					this->matrix[j][i] = (aij[counter] - 0.5); 
				}
				counter++;
			}
		}
	}
	else MutableMatrix(dim, aij);
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
	for (size_t i = 0; i < this->dim; ++i) {
		delete[] this->matrix[i];
	}
	delete[] this->matrix;
}

double MutableMatrix::det()
{
	srand(time(NULL));
	return this->_det(*this);
	
}

double MutableMatrix::_det(MutableMatrix& m) {
	double det = 0;
	if (m.dim == 1) {
		det = m.matrix[0][0];
	}
	else if (m.dim == 2) {
		det = m.matrix[0][0] * m.matrix[1][1] - m.matrix[0][1] * m.matrix[1][0];
	}
	else {
		bool isRow = rand() % 2;
		if (isRow) {
			int row = rand() % m.dim;
			for (int i = 0; i < m.dim; i++) {
				if (m.matrix[row][i] != 0) {
					MutableMatrix s = m.sub(row, i);
					int n = (i + row) % 2 == 0 ? 1 : -1;
					det += n * m.matrix[row][i] * m._det(s);
				}
			}
		}
		else {
			int col = rand() % m.dim;
			for (int i = 0; i < m.dim; i++) {
				if (m.matrix[i][col] != 0) {
					MutableMatrix s = m.sub(i, col);
					int n = (i + col) % 2 == 0 ? 1 : -1;
					det += n * m.matrix[i][col] * m._det(s);
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


void MutableMatrix::print() {
	for (int i = 0; i < this->dim; i++) {
		for (int j = 0; j < this->dim; j++) {
			cout << this->matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
