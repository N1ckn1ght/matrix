#pragma once
#include <vector>
#include <iostream>

typedef unsigned int unt;
using namespace std;

class MatrixException {};

template <class Type> class Matrix 
{
private:
	Type** ptr;
	unt n;
	unt m;
public:
	/* Basic methods */
	explicit Matrix(unt an);
	explicit Matrix(unt an, unt am, Type elem = (Type)0);
	explicit Matrix(vector <vector <Type>> vec);
	
	~Matrix();
	Matrix<Type>(const Matrix<Type>& A);
	Type get(unt i, unt j) const;
	void set(unt i, unt j, Type elem);
	Matrix<Type>& operator = (const Matrix<Type>& A);
	bool operator == (const Matrix<Type>& A) const;

	/* Matrix operators */
	Matrix<Type>& operator *= (const Type x);
	Matrix<Type> operator * (const Type x) const;
	Matrix<Type>& operator += (const Matrix<Type>& B);
	Matrix<Type> operator + (const Matrix<Type>& B) const;
	Matrix<Type>& operator *= (const Matrix<Type>& B);
	Matrix<Type> operator * (const Matrix<Type>& B) const;
	Matrix<Type> T();
	Matrix<Type> Minor(unt x, unt y);
	Type Det();
	bool isDegen();
	Matrix<Type> Inv();

	/* IO */
	template <class Type> friend ostream& operator << (ostream& out, const Matrix<Type>& A);
};

template <class Type> ostream& operator<<(ostream& out, const Matrix<Type>& A)
{
	for (unt i = 0; i < A.n; i++) {
		for (unt j = 0; j < A.m; j++)
			out << A.ptr[i][j] << "\t";
			out << endl;
	}
	return out;
}

template <class Type> Matrix<Type>::Matrix(unt an)
{
	*this = Matrix(an, an);
}

template <class Type> Matrix<Type>::Matrix(unt an, unt am, Type elem)
{
	n = an; m = am;

	ptr = new Type* [n];
	for (unt i = 0; i < n; i++)
		ptr[i] = new Type [m];

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = elem;
	}
}

template <class Type> Matrix<Type>::Matrix(vector <vector <Type>> vec)
{
	n = vec.size();
	if (n == 0) throw MatrixException();
	m = vec[0].size();

	ptr = new Type * [n];
	for (unt i = 0; i < n; i++)
		ptr[i] = new Type[m];

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = vec[i][j];
	}
}

template <class Type> Matrix<Type>::~Matrix()
{
	for (unt i = 0; i < n; i++)
		delete[] ptr[i];
	delete[] ptr;
}

template< class Type> Matrix<Type>::Matrix(const Matrix<Type>& A)
{
	n = A.n; m = A.m;

	ptr = new Type * [n];
	for (unt i = 0; i < n; i++)
		ptr[i] = new Type[m];

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = A.ptr[i][j];
	}
}

template <class Type> Type Matrix<Type>::get(unt i, unt j) const
{
	if (i < n && j < m) return ptr[i][j];
	else throw MatrixException();
}

template <class Type> void Matrix<Type>::set(unt i, unt j, Type elem)
{
	if (i < n && j < m) ptr[i][j] = elem;
	else throw MatrixException();
}

template <class Type> Matrix<Type>& Matrix<Type>::operator = (const Matrix& A)
{
	if (this == &A) return *this;
	if (n != A.n || m != A.m)
	{
		for (unt i = 0; i < n; i++)
			delete[] ptr[i];
		delete[] ptr;

		n = A.n;
		m = A.m;

		ptr = new Type * [n];
		for (unt i = 0; i < n; i++)
			ptr[i] = new Type[m];
	}
	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = A.ptr[i][j];
	}
	return *this;
}

template <class Type> bool Matrix<Type>::operator == (const Matrix<Type>& A) const
{
	if (n == A.n && m == A.m) {
		for (unt i = 0; i < n; i++) {
			for (unt j = 0; j < m; j++) {
				if (ptr[i][j] != A.ptr[i][j])
					return false;
			}
		}
		return true;
	}
	return false;
}

template <class Type> Matrix<Type>& Matrix<Type>::operator *= (const Type x)
{
	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] *= x;
	}
	return *this;
}

template <class Type> Matrix<Type> Matrix<Type>::operator * (const Type x) const
{
	Matrix A(*this);
	return (A *= x);
}

template <class Type> Matrix<Type>& Matrix<Type>::operator += (const Matrix<Type>& B)
{
	if (n != B.n || m != B.m) throw MatrixException();
	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] += B.ptr[i][j];
	}
	return *this;
}

template <class Type> Matrix<Type> Matrix<Type>::operator + (const Matrix<Type>& B) const
{
	Matrix A(*this);
	return (A += B);
}

template <class Type> Matrix<Type> Matrix<Type>::operator * (const Matrix<Type>& B) const
{
	if (m != B.n) throw MatrixException();
	Matrix A(n, B.m);
	for (unt i = 0; i < A.n; i++) {
		for (unt j = 0; j < A.m; j++) {
			for (unt k = 0; k < m; k++) {
				A.ptr[i][j] += ptr[i][k] * B.ptr[k][j];
			}
		}
	}
	return A;
}

template <class Type> Matrix<Type>& Matrix<Type>::operator *= (const Matrix<Type>& B)
{
	Matrix A(*this);
	A = A * B;
	*this = A;
	return *this;
}

template <class Type> Matrix<Type> Matrix<Type>::T()
{
	Matrix <Type> A(m, n);
	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++) {
			A.ptr[j][i] = ptr[i][j];
		}
	}
	return A;
}

template <class Type> Matrix<Type> Matrix<Type>::Minor(unt x, unt y)
{
	if (n < 2 || m < 2) throw MatrixException();
	Matrix <Type> A(n - 1, m - 1);
	bool fx = 0, fy;
	for (unt i = 0; i < n - 1; i++) {
		fy = 0;
		if (i == x) fx++;
		for (unt j = 0; j < m - 1; j++) {
			if (j == y) fy++;
			A.ptr[i][j] = ptr[i + fx][j + fy];
		}
	}
	return A;
}

template <class Type> Type Matrix<Type>::Det()
{
	if (n != m || n == 0) throw MatrixException();
	if (n == 1) return ptr[0][0];
	if (n == 2) return (ptr[0][0] * ptr[1][1] - ptr[0][1] * ptr[1][0]);
	
	Type det = 0;
	for (unt i = 0; i < n; i++)
	{
		if (ptr[0][i] == 0) continue;	
		Type tmp = this->Minor(0, i).Det() * ptr[0][i];
		if (i % 2 == 0) det += tmp;
		else det -= tmp;
	}

	return det;
}

template <class Type> bool Matrix<Type>::isDegen()
{
	if (this->Det() != 0) return false;
	return true;
}

template <class Type> Matrix<Type> Matrix<Type>::Inv()
{
	/* TODO: check if Type isn't double */
	Type det = this->Det();
	
	Matrix <Type> A = this->T();
	Matrix <Type> B(n);

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < n; j++) 
		{
			Type tmp = A.Minor(i, j).Det() / det;
			if ((i + j) % 2 == 0) B.ptr[i][j] = tmp;
			else B.ptr[i][j] = -tmp;
		}
	}

	return B;
}
