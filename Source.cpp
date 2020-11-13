#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
	Matrix <double> A({ {2, 5, 8}, {3, 6, 9}, {1, 4, 7} });
	Matrix <double> B({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

	cout << "Matrix A:\n" << A << "\nMatrix B:\n" << B << endl;
	A += B;
	cout << "Matrix A += B\n" << A << endl;
	B *= 2;
	cout << "Matrix B *= 2\n" << B << endl;
}