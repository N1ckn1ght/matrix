#pragma once
#include <vector>
#include <iostream>

typedef unsigned int unt;
using namespace std;

class MatrixException {};

template <class T> class Matrix 
{
private:
	T** ptr;
	unt n;
	unt m;
public:
	/* Basic methods */
	explicit Matrix(unt an, unt am, T elem = (T)0);
	// TODO: explicit Matrix(T**& _arr);
	explicit Matrix(vector <vector <T>> vec);
	
	~Matrix();
	Matrix<T>(const Matrix<T>& A);
	T get(unt i, unt j) const;
	void set(unt i, unt j, T elem);
	Matrix<T>& operator = (const Matrix<T>& A);
	bool operator == (const Matrix<T>& A) const;

	/* Matrix operators */
	Matrix<T>& operator *= (const T x);
	//Matrix<T>& operator * (const T x) const;
	Matrix<T>& operator += (const Matrix<T>& B);
	//Matrix<T>& operator + (const Matrix<T>& B) const;
	// TODO: other matrix operators

	/* IO */
	template <class T> friend ostream& operator << (ostream& out, const Matrix<T>& A);
};

template <class T> ostream& operator<<(ostream& out, const Matrix<T>& A)
{
	for (unt i = 0; i < A.n; i++) {
		for (unt j = 0; j < A.m; j++)
			out << A.ptr[i][j] << " ";
		out << endl;
	}
	return out;
}

template <class T> Matrix<T>::Matrix(unt an, unt am, T elem)
{
	n = an; m = am;

	ptr = new T* [n];
	for (unt i = 0; i < n; i++)
		ptr[i] = new T [m];

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = elem;
	}
}

template <class T> Matrix<T>::Matrix(vector <vector <T>> vec)
{
	n = vec.size();
	if (n == 0) throw MatrixException();
	m = vec[0].size();

	ptr = new T * [n];
	for (unt i = 0; i < n; i++)
		ptr[i] = new T[m];

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = vec[i][j];
	}
}

template <class T> Matrix<T>::~Matrix()
{
	for (unt i = 0; i < n; i++)
		delete[] ptr[i];
	delete[] ptr;
}

template< class T> Matrix<T>::Matrix(const Matrix<T>& A)
{
	n = A.n; m = A.m;

	ptr = new T * [n];
	for (unt i = 0; i < n; i++)
		ptr[i] = new T[m];

	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = A.ptr[i][j];
	}
}

template <class T> T Matrix<T>::get(unt i, unt j) const
{
	if (i < n && j < m) return ptr[i][j];
	else throw MatrixException();
}

template <class T> void Matrix<T>::set(unt i, unt j, T elem)
{
	if (i < n && j < m) ptr[i][j] = elem;
	else throw MatrixException();
}

template <class T> Matrix<T>& Matrix<T>::operator = (const Matrix& A)
{
	if (this == &A) return *this;
	if (n != A.n || m != A.m)
	{
		for (unt i = 0; i < n; i++)
			delete[] ptr[i];
		delete[] ptr;

		n = A.n;
		m = A.m;

		ptr = new T * [n];
		for (unt i = 0; i < n; i++)
			ptr[i] = new T[m];
	}
	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] = A.ptr[i][j];
	}
}

template <class T> bool Matrix<T>::operator == (const Matrix<T>& A) const
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

template <class T> Matrix<T>& Matrix<T>::operator *= (const T x)
{
	for (unt i = 0; i < n; i++) {
		for (unt j = 0; j < m; j++)
			ptr[i][j] *= x;
	}
	return *this;
}

//template <class T> Matrix<T>& Matrix<T>::operator * (const T x) const
//{
//	Matrix A(*this);
//	return (A *= x);
//}

template <class T> Matrix<T>& Matrix<T>::operator += (const Matrix<T>& B)
{
	if (n != B.n || m != B.m) throw MatrixException();
	for (unt i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			ptr[i][j] += B.ptr[i][j];
	}
	return *this;
}

//template <class T> Matrix<T>& Matrix<T>::operator + (const Matrix<T>& B) const
//{
//	Matrix A(*this);
//	return (A += B);
//}