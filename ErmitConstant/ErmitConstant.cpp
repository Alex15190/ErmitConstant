// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;

const int N = 2;
const int MAXN = N * (N - 1) / 2;
double a[MAXN];

double* generateMatrix(int n, int m, int ind) {
	if (!n && !m)
	{
		double* tmp = a;
		return tmp;
	}

	if (n)
	{
		a[ind] = -0.5;
		generateMatrix(n - 1, m, ind + 1);
	}

	if (m)
	{
		a[ind] = 0.5;
		generateMatrix(n, m - 1, ind + 1);
	}
}

void recursiveGenVector(vector<int> v, int dim, vector<Matrix>* vm) {
	if (dim == 1) {
		for (int i = -1; i < 2; i++) {
			v.push_back(i);
			vm->push_back(Matrix(v));
			v.pop_back();
		}
	}
	else {
		for (int i = -1; i < 2; i++) {
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
		for (int i = -1; i < 2; i++) {
			v.push_back(i);
			recursiveGenVector(v, dim - 1, &vm);
			v.pop_back();
		}
		return vm;
	}
	else
		cerr << "dimention must be >= 2" << endl;
}

int matMult(Matrix vect, Matrix matr) {
	Matrix m1 = vect.transpost() * matr * vect;
	return m1.det();
}

double findAlpha(Matrix a, Matrix b) {
	double p = 1 - b.det();
	double q = a.det() - b.det();
	return p / q;
}



int main()
{
	vector<Matrix> startMatrix;

	vector<Matrix> higherOne;
	vector<Matrix> lowerOne;
	vector<Matrix> equallyOne;

	vector<Matrix> vectors;

	for (int i = 0; i <= N; i++) {
		int n = i, m = N - i;
		Matrix m1 = Matrix(N, generateMatrix(n, m, 0));
		startMatrix.push_back(m1);
	}

	vectors = generateVector(N);
	/*
	for (int i = 0; i < vectors.size(); i++) {
		cout << "vectors[" << i << "] = " << endl << vectors[i] << endl;
	}
	*/


	for (int i = 0; i < vectors.size(); i++) {
		for (int j = 0; j < startMatrix.size(); j++) {
			if (matMult(vectors[i], startMatrix[j]) > 1) {
				higherOne.push_back(startMatrix[j]);
			}
			else if (matMult(vectors[i], startMatrix[j]) == 1) {
				equallyOne.push_back(startMatrix[j]);
			}
			else if (matMult(vectors[i], startMatrix[j]) < 1) {
				lowerOne.push_back(startMatrix[j]);
			}
		}

		//потом делаем те, которые = 1
		for (int k = 0; k < higherOne.size(); k++) {
			for (int j = lowerOne.size() - 1; j >= 0; j--) {
				double alpha = findAlpha(lowerOne[j],higherOne[k]);
				Matrix tmp = alpha * lowerOne[j] + (1 - alpha) * higherOne[k];
				equallyOne.push_back(tmp);
			}
		}

		//чистим те, которые < 1
		lowerOne.clear();

		

	}

	//затем ищем мин определитель

	double minDet = higherOne[1].det();
	for (int i = 0; i < higherOne.size(); i++) {
		if (higherOne[i].det() < minDet) minDet = higherOne[i].det();
	}

	for (int i = 0; i < equallyOne.size(); i++) {
		if (equallyOne[i].det() < minDet) minDet = equallyOne[i].det();
	}

	cout << "Min det for N = " << N << " is: " << minDet << endl;

	return 0;
}
