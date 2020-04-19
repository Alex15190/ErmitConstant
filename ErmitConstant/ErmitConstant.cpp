// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <set>
#include "Matrix.h"
using namespace std;

const int N = 4;
const int MAXN = N * (N - 1) / 2;
const int nForVector = 2;  //using for generate vectors
double a[MAXN];

void generateMatrix(int n, int m, int ind, set<Matrix>* globMatr) {
	if (!n && !m)
	{
		//for (int i = 0; i < MAXN; i++) {
		//	cout << "a[" << i << "] = " << a[i] << endl;
		//}
		//cout << endl;
		globMatr->insert(Matrix(N, a));
		return;
	}

	if (n)
	{
		a[ind] = -0.5;
		generateMatrix(n - 1, m, ind + 1, globMatr);
	}

	if (m)
	{
		a[ind] = 0.5;
		generateMatrix(n, m - 1, ind + 1, globMatr);
	}
}

void recursiveGenVector(vector<int> v, int dim, vector<Matrix>* vm) {
	if (dim == 1) {
		for (int i = (-1) * nForVector; i < 0; i++) {
			v.push_back(i);
			vm->push_back(Matrix(v));
			v.pop_back();
		}
	}
	else {
		for (int i = (-1) * nForVector; i < 1 * nForVector; i++) {
			v.push_back(i);
			recursiveGenVector(v, dim - 1, vm);
			v.pop_back();
		}
	}

}

vector<Matrix> generateVector(int dim) {
	if (dim >= 2) {
		vector<Matrix> vm;
		vector<int> v;
		for (int i = (-1) * nForVector; i < 1 * nForVector; i++) {
			v.push_back(i);
			recursiveGenVector(v, dim - 1, &vm);
			v.pop_back();
		}
		return vm;
	}
	else
		cerr << "dimention must be >= 2" << endl;
}

double matMult(Matrix vect, Matrix matr) {
	Matrix m1 = (vect.transpost() * matr) * vect;
	cout << "x^T*F*x = " << endl << vect.transpost() << " * " << endl << matr << " * " << endl << vect << " = " << endl << m1.det() << endl;
	return m1.det();
}

double findAlpha(double a, double b) {
	double p = 1 - b;
	double q = a - b;
	return p / q;
}

Matrix calculateNewMatrix(Matrix f, Matrix h, Matrix vector) {

	double fx = matMult(vector, f);
	double hx = matMult(vector, h);
	double c1 = 1 / (fx - hx);
	double c2 = 1 - hx;
	double c3 = fx - 1;
	Matrix tmp = c1 * ((c2 * f) + (c3 * h));
	return tmp;
	
	/*
	double alpha = findAlpha(matMult(vector, h), matMult(vector, f));
	cout << "alpha = " << alpha << endl;
	Matrix a = alpha * h;
	//cout << "A in tmp = " << endl << a << endl;
	Matrix b = (1 - alpha) * f;
	//cout << "B in tmp = " << endl << b << endl;
	Matrix tmp = (a + b);
	//cout << "i = " << i << " det tmp ("<<j<<" "<<k<<") must be = 1 but his = " << matMult(vectors[i],tmp) << endl;
	return tmp;
	*/
}



Matrix findMinMatrix(set<Matrix>* matrixs) {
	Matrix min;
	double minDet;
	for (Matrix m : *matrixs) {
		if (min.isNull()) {
			min = m;
			minDet = m.det();
		}
		else {
			if ((m.det() < minDet) && (m.det() > 0)) {
				min = m;
				minDet = m.det();
			}
		}
		
	}
	return min;
}

int main()
{
	set<Matrix> startMatrix;

	vector<Matrix> vectors;

	cout << "Start" << endl;
	
	for (int i = 0; i <= MAXN; i++) {
		int n = i, m = MAXN - i;
		generateMatrix(n, m, 0, &startMatrix);
	}

	for (Matrix startMatr : startMatrix) {
		cout << "StartMatrix = " << endl << startMatr << endl;
	}

	vectors = generateVector(N);

	set<Matrix> A; // > 1
	set<Matrix> B; // < 1
	set<Matrix> C; // = 1


	Matrix firstMatrix = findMinMatrix(&startMatrix);
	cout << "Matrix with minimal determinant is: " << endl << firstMatrix << endl;
	for (Matrix vect : vectors) {
		double result = matMult(vect, firstMatrix);
		if (result > 1) {
			A.insert(firstMatrix);
		}
		else if (result == 1) {
			C.insert(firstMatrix);
		}
		else if (result < 1) {
			B.insert(firstMatrix);
		}
	}

	if (B.empty()) {
		cout << "First try" << endl;
		cout << "Min det for N = " << N << " is: " << firstMatrix.det() << endl;
		return 0;
	}


	A.clear();
	B.clear();
	C.clear();

	while (true) {
		cout << "Количество матриц с каждой иттерации = " << startMatrix.size() << endl;

		for (Matrix matr : startMatrix) {
			for (Matrix vect : vectors) {
				double result = matMult(vect, matr);
				if (result > 1) {
					A.insert(matr);
				}
				else if (result == 1) {
					C.insert(matr);
				}
				else if (result < 1) {
					B.insert(matr);
				}
			}

			//убрать лишнюю матрицу 

			if (B.empty()) {
				//если список матриц кончился, то все нашли
				continue;
			}
			else {
				for (Matrix vect : vectors) {
					for (Matrix a : A) {
						for (Matrix b : B) {
							Matrix tmp = calculateNewMatrix(a, b, vect);
							cout << endl << "New matrix = " << endl << tmp;
							C.insert(tmp);
						}
					}
				}
				startMatrix.clear();
				startMatrix.insert(A.begin(), A.end());
				startMatrix.insert(C.begin(), C.end());
				A.clear();
				B.clear();
				C.clear();
			}

		}
	}

	/*
	for (Matrix matr : startMatrix) {
		for (Matrix vect : vectors) {
			double result = matMult(vect, matr);
			if (result > 1) {
				A.insert(matr);
			}
			else if (result == 1) {
				C.insert(matr);
			}
			else if (result < 1) {
				B.insert(matr);
			}
		}

		//убрать лишнюю матрицу 

		if (B.empty()) {
			//если список матриц кончился, то все нашли
			continue;
		} else {
			for (Matrix vect : vectors) {
				for (Matrix a : A) {
					for (Matrix b : B) {
						Matrix tmp = calculateNewMatrix(a, b, vect);
						cout << endl << "New matrix = " << endl << tmp;
						C.insert(tmp);
					}
				}
			}
			startMatrix.clear();
			startMatrix.insert(A.begin(), A.end());
			startMatrix.insert(C.begin(), C.end());
			A.clear();
			B.clear();
			C.clear();
		}

	}
	/*
	if (B.empty()) {
		Matrix min = findMinMatrix(&startMatrix);
		cout << "Min det for N = " << N << " is: " << min.det() << endl;
		return 0;
	}

	else {
		for (Matrix vect : vectors) {
			for (Matrix a : A) {
				for (Matrix b : B) {
					Matrix tmp = calculateNewMatrix(a, b, vect);
					cout << endl << "New matrix = " << endl << tmp;
					C.insert(tmp);
				}
			}
		}
	}
	*/

	Matrix min = findMinMatrix(&startMatrix);
	cout << "Min det for N = " << N << " is: " << min.det() << endl;
	return 0;
}
