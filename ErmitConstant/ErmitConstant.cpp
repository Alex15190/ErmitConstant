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
		Matrix m = Matrix(N, temp);
		/*
		cout << endl;
		for (int i = 0; i < ind; ++i)
			cout << a[i] << " ";
		cout << endl;
		cout << m;
		cout << endl;
		cout << "det = " << m.det() << endl;
		cout << "_______________________________________" << endl;
		*/
		return m;
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


int main()
{
	vector<Matrix> startVector;
	vector<Matrix> higherOne;
	vector<Matrix> lowerOne;
	vector<Matrix> equallyOne;

	for (int i = 0; i <= N; i++) {
		int n = i, m = N - i;
		startVector.push_back(generateMatrix(n, m, 0));
	}
	return 0;
}
