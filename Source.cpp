#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество неизвестных: ";
	unsigned int n;
	cin >> n;
	cout << "Введите коэффициенты при неизвестных и ответ (n столбцов, n + 1 чисел через пробел):" << endl;
	cout << "(Формат: ax + by + ... = c)" << endl;
	Matrix <double> A(n);
	Matrix <double> R(n, 1);
	double tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> tmp;
			A.set(i, j, tmp);
		}
		cin >> tmp;
		R.set(i, 0, tmp);
	}
	cout << "Ответ:\n" << (A.Inv() * R);


	/* DEBUG
	
	Matrix <double> A({ {2, 5, 8}, {3, 6, 9}, {1, 4, 7} });
	Matrix <double> B({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

	cout << "Matrix A:\n" << A << "\nMatrix B:\n" << B << endl;
	A += B;
	cout << "Matrix A += B\n" << A << endl;
	B *= 2;
	cout << "Matrix B *= 2\n" << B << endl;
	cout << "A + B\n" << A + B << endl;

	Matrix <double> C({ {1, -1}, {2, 0}, {3, 0} });
	Matrix <double> D({ {1, 1}, {2, 0} });
	cout << "Matrix C:\n" << C << "\nMatrix D:\n" << D << endl;
	A = C * D;
	cout << "Matrix A = C * D\n" << A << endl;
	C *= D;
	cout << "Matrix C *= D\n" << C << endl;
	cout << "Is A == C? " << (A == C) << ", is B == D? " << (B == D) << endl;
	cout << "\nA^T\n" << A.T() << endl;

	Matrix <double> E({{ 5, 2 }, { 4, 3 }});
	cout << "Matrix E:\n" << E << endl;
	cout << "E^T\n" << E.T() << endl;
	cout << "(E^T)^T\n" << (E.T()).T() << endl;
	cout << "(D*E)^T\n" << (D * E).T() << endl;
	cout << "D^T * E^T\n" << D.T() * E.T() << endl;

	Matrix <int> Test(2);
	cout << "Debug:\n" << Test << endl;
	
	Matrix <int> F({ { 1, 3, 4 }, { 0, 2, 1 }, { 1, 5, -1 } });
	cout << "Matrix F:\n" << F << "\nDet(F) = " << F.Det() << endl;
	Matrix <int> G({ {2, -2, 3, 1}, {3, 0, 1, 5}, {1, 3, 4, -2}, {4, 2, 2, 1} });
	cout << "\nMatrix G:\n" << G << "\nDet(G) = " << G.Det() << endl;
	cout << "\nG.isDegen()? " << G.isDegen() << endl;
	cout << "\nG.Inv() (int Type!)\n" << G.Inv() << endl;

	Matrix <double> H({ {3, 1, 0}, {1, 2, 1}, {2, 4, 3} });
	cout << "Matrix H:\n" << H << endl;
	cout << "H.Inv()\n" << H.Inv() << endl;*/
}
