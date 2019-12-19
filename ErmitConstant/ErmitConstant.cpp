// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MutableMatrix.h"
using namespace std;

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

int main()
{
	/*Matrix mat = Matrix(3,1.0);
	cout << mat;
	double  matrix[3][3];
	matrix[0][0] = 1;
	double a11 = 7;
	double &reffa11 = a11;
	Matrix mat2 = Matrix(3, reffa11);
	a11 = 10;
	cout << mat2;
	a11 = 20;
	cout << mat2;
    cout << "Hello World!\n";*/

	//MutableMatrix matrix = MutableMatrix();
	// n - zero m - one

	// 3 = n(n-1)/2 при n = 3

	for (int i = 0; i <= N; i++) {
		int n = i, m = N - i;
		find(n, m, 0);
	}
	//int n = 2, m = 3;
	//find(n, m, 0);

	return 0;

	
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
