// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;

const int N = 6;
const int MAXN = N * (N - 1) / 2;
double a[MAXN];

;

void generateMatrix(int n, int m, int ind, vector<Matrix>* globMatr) {
	if (!n && !m)
	{
		for (int i = 0; i < MAXN; i++) {
			cout << "a[" << i << "] = " << a[i] << endl;
		}
		cout << endl;
		globMatr->push_back(Matrix(N, a));
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
		for (int i = -1; i < 0; i++) {
			v.push_back(i);
			vm->push_back(Matrix(v));
			v.pop_back();
		}
	}
	else {
		for (int i = -1; i < 1; i++) {
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
		for (int i = -1; i < 1; i++) {
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
	Matrix m1 = vect.transpost() * matr * vect;
	//cout << "matMult det = " << m1.det() << endl;
	return m1.det();
}

double findAlpha(double a, double b) {
	double p = 1 - b;
	double q = a - b;
	return p / q;
}



int main()
{
	vector<Matrix> startMatrix;

	vector<Matrix> higherOne;
	vector<Matrix> lowerOne;
	vector<Matrix> equallyOne;

	vector<Matrix> vectors;

	cout << "Start" << endl;
	
	for (int i = 0; i <= N; i++) {
		int n = i, m = N - i;
		generateMatrix(n, m, 0, &startMatrix);
	}

	//startMatrix = globMatr;

	for (int i = 0; i < startMatrix.size(); i++) {
		cout << "StartMatrix[" << i << "] = " << endl << startMatrix[i] << endl;
	}

	vectors = generateVector(N);

	for (int i = 0; i < vectors.size(); i++) {
		//cout << "i = " << i << " _________________" << endl;
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
			for (int j = 0; j < lowerOne.size(); j++) {
				double alpha = findAlpha(matMult(vectors[i], lowerOne[j]), matMult(vectors[i], higherOne[k]));
				cout << "alpha = " << alpha << endl;
				Matrix a = alpha * lowerOne[j];
				//cout << "A in tmp = " << endl << a << endl;
				Matrix b = (1 - alpha) * higherOne[k];
				//cout << "B in tmp = " << endl << b << endl;
				Matrix tmp = (a + b);
				//cout << "i = " << i << " det tmp ("<<j<<" "<<k<<") must be = 1 but his = " << matMult(vectors[i],tmp) << endl;
				equallyOne.push_back(tmp);
			}
		}

		//чистим те, которые < 1

		startMatrix.clear();
		startMatrix = higherOne;
		startMatrix.insert(end(startMatrix),begin(equallyOne),end(equallyOne));

		higherOne.clear();
		equallyOne.clear();
		lowerOne.clear();

		

	}

	//затем ищем мин определитель
	cout << "startMatrix size = " << startMatrix.size() << endl;


	double minDet = startMatrix[0].det();

	for (int i = 0; i < startMatrix.size(); i++) {
		//cout << "startMatrix[" << i << "] : " << endl << startMatrix[i] << endl;
		if ((startMatrix[i].det() < minDet)&&( startMatrix[i].det() > 0)) minDet = startMatrix[i].det();
		//else if ((startMatrix[i].det()*(-1) < minDet) && (startMatrix[i].det() < 0)) minDet = (-1)*startMatrix[i].det();
	}

	cout << "Min det for N = " << N << " is: " << minDet << endl;

	return 0;
}
