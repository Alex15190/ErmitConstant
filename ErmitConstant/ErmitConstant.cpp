// ErmitConstant.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Matrix.h"
using namespace std;

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
	
}

double** initialMatrix()
{
	int dim;
	int temp;
	cout << "Enter dimention of matrix";
	cin >> dim;
	double** matrix = new double* [dim];
	for (int i = 0; i < dim; i++) {
		matrix[i] = new double[dim];
		for (int j = 0; j < dim; j++) {
			cout << "Enter element of matrix in index" << i + 1 << j + 1;
			cin >> temp;
			matrix[i][j] = temp;
			if (i = !j) matrix[j][i] = temp;
		}
	}
	return matrix;
}

double determinant(double** m)

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
