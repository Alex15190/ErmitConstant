// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;

const int N = 2;
const int MAXN = N * (N - 1) / 2;
double a[MAXN];

Matrix generateMatrix(int n, int m, int ind) {
	if (!n && !m)
	{
		double* temp = a;
		Matrix matr = Matrix(N, temp);
		
		cout << endl;
		for (int i = 0; i < ind; ++i)
			cout << a[i] << " ";
		cout << endl;
		cout << matr;
		cout << endl;
		cout << "det = " << matr.det() << endl;
		cout << "_______________________________________" << endl;
		
		return matr;
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
		}
	}
	else {
		for (int i = -1; i < 2; i++) {
			v.push_back(i);
			recursiveGenVector(v, dim - 1, vm);
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
			//m.insert(end(m),begin(m1),end(m1));
		}
		return vm;
	}
	else
		cerr << "dimention must be >= 2" << endl;
}




int main()
{
	vector<Matrix> startVector;
	vector<Matrix> higherOne;
	vector<Matrix> lowerOne;
	vector<Matrix> equallyOne;

	//vector<Matrix> vectors = generateVector(N);

	for (int i = 0; i <= N; i++) {
		int n = i, m = N - i;
		Matrix m1 = generateMatrix(n, m, 0);
		startVector.push_back(m1);
	}
	return 0;
}
