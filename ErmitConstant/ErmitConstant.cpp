// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;

/*

const int N = 4;
const int MAXN = N*(N-1)/2;
double a[MAXN];

//int min(*a)

int find (int n, int m, int ind)
{
	if (!n && !m)
	{
		
		// cout << size(a) << endl;
		double* temp = a;
		//cout << "ind = " << ind << endl;
		MutableMatrix m = MutableMatrix((double)N, temp, true);

		cout << endl;
		//if (m.det() != 0.0) {
			for (int i = 0; i < ind; ++i)
				cout << a[i] << " ";
			cout << endl;
			m.print();
			cout << endl;
			cout << "det = " << m.det() << endl;
			cout << "_______________________________________" << endl;
		//}
		
		// вот тут уже сформированный набор.
		return 0;
	}

	if (n)
	{
		a[ind] = 0;
		find(n - 1, m, ind + 1);
	}

	if (m)
	{
		a[ind] = 1;
		find(n, m - 1, ind + 1);
	}
}
*/

const int N = 2;
const int MAXN = N * (N - 1) / 2;
double a[MAXN];

Matrix generateMatrix(int n, int m, int ind) {
	if (!n && !m)
	{
		cout << "in !n && !m" << endl;
		double* temp = a;
		Matrix m = Matrix(N, temp);

		cout << endl;
		for (int i = 0; i < ind; ++i)
			cout << a[i] << " ";
		cout << endl;
		cout << m;
		cout << endl;
		cout << "det = " << m.det() << endl;
		cout << "_______________________________________" << endl;

		cout << "out !n && !m" << endl;
		return m;
	}

	if (n)
	{
		cout << "in n" << endl;

		a[ind] = -0.5;
		generateMatrix(n - 1, m, ind + 1);

		cout << "out n" << endl;
	}

	if (m)
	{
		cout << "in m" << endl;

		a[ind] = 0.5;
		generateMatrix(n, m - 1, ind + 1);

		cout << "out m" << endl;
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
