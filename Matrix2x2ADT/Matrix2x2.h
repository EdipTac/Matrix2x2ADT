#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
/*

Purpose: Create a 2x2 Matrix ADT to practice operator overloading, ADT implementation, and function objects
@author Edip Tac
@version 1.0


NOTE: This ADT contains a matrix implemented as an std::array.
For the purposes of this assignment, a 2x2 matrix such as
|a   b|
|     |
|c   d|
is represented as (a b c d)

Furthermore, the following notations will be used in the comments
matrix[0] = a;
matrix[1] = b;
matrix[2] = c;
matrix[3] = d;

where ad - bc is indicating matrix[0] * matrix[3] + matrix[1] * matrix[2]
*/

class Matrix2x2 {
private:
	std::array<double, 4> matrix;
	static const double epsilon; //this is the epsilon value 1E-6 used for comparing doubles


public:

	//default constructor initializes the matrix to contain all 0s
	Matrix2x2();

	//normal constructor that initializes the a, b, c, d into the matrix array with the
	//indexes 0, 1, 2, and 3 respectively
	Matrix2x2(double a, double b, double c, double d);


	//no dynamic memory so default copy constructor is used
	Matrix2x2(const Matrix2x2 &other) = default;
	
	//default destructor is used
	~Matrix2x2() = default; 

	//once again no dynamic memory so default assignment operator is used
	Matrix2x2 & operator = (const Matrix2x2 & rhs) = default;


	/*
	Computes the determinant for the matrix and returns a double for ad - bc
	*/
	double determinant();

	/*
	Computes the trace of the matrix and returns a double for returns a double for a + d
	*/
	double trace();

	/*
	Boolean to determine if the matrix is symmetric by checking if b = c
	*/
	bool isSymmetric();

	/*
	Boolean to determine if two matrices are similar by checking checking if 
	determinant(M) = determinant(M') and trace(M) = trace(M')
	*/
	bool isSimilar(Matrix2x2 & rhs);

	/*
	Returns a matrix that is the tranpose of the invoking matrix.
	Computes and returns the matrix M^T = (a c b d)
	*/
	Matrix2x2 transpose();

	/*
	Returns a matrix that is the inverse of the invoking matrix.
	Computes and returns (1/(ad - bc)) * (d -b -c a) provided that ad - bc != 0
	*/
	Matrix2x2 inverse();

	/*
	The remaining methods are operator overloads performed to have a seamless integration
	of the ADT into the C++ language.
	*/


	/*
	Compound arithmetic assignment operators are overloaded first so that they can be used
	to implement the simple arithmetic operators and prevent clutter and facilitate code re-use.
	*/
	Matrix2x2& operator += (const Matrix2x2& rhs);
	Matrix2x2& operator += (double val);

	Matrix2x2& operator -= (const Matrix2x2& rhs);
	Matrix2x2& operator -= (double val);

	Matrix2x2& operator *= (const Matrix2x2& rhs);
	Matrix2x2& operator *= (double val);

	Matrix2x2& operator /= (const Matrix2x2& rhs);
	Matrix2x2& operator /= (double x);


	/*
	Simple arithmetic operator overloads taking into consideration different s
	(Matrix, Matrix), (Matrix, double), (double, Matrix)
	*/
	friend Matrix2x2 operator + (const Matrix2x2& lhs, const Matrix2x2& rhs);
	friend Matrix2x2 operator - (const Matrix2x2& lhs, const Matrix2x2& rhs);
	friend Matrix2x2 operator * (const Matrix2x2& lhs, const Matrix2x2& rhs);
	friend Matrix2x2 operator / (const Matrix2x2& lhs, const Matrix2x2& rhs);

	friend Matrix2x2 operator + (const Matrix2x2& lhs, const double& val);
	friend Matrix2x2 operator - (const Matrix2x2& lhs, const double& val);
	friend Matrix2x2 operator * (const Matrix2x2& lhs, const double& val);
	friend Matrix2x2 operator / (const Matrix2x2& lhs, const double& val);

	friend Matrix2x2 operator + (const double& val, const Matrix2x2& rhs);
	friend Matrix2x2 operator - (const double& val, const Matrix2x2& rhs);
	friend Matrix2x2 operator * (const double& val, const Matrix2x2& rhs);
	friend Matrix2x2 operator / (const double& val, const Matrix2x2& rhs);

	/*
	Unary operators
	*/
	Matrix2x2 operator+() const; //unary+
	Matrix2x2 operator-() const; //unary-

	Matrix2x2 operator++();//++M
	Matrix2x2 operator--();//--M

	Matrix2x2 operator++(int);//M++
	Matrix2x2 operator--(int); //M--

	friend bool operator ==(const Matrix2x2& lhs, const Matrix2x2& rhs); //M === M'
	friend bool operator !=(const Matrix2x2& lhs, const Matrix2x2& rhs);//M!=M'

	/*
	Subscript operator overload to provide easy access to the values stored within
	the matrix without having to call getters and setters
	*/
	double& operator [] (int i);
	const double& operator[](int i) const;

	/*
	Function objects to return the EigenValues of the matrix and the determinant
	of the matrix respectively
	*/
	std::vector<double> operator()(int x);
	double operator()();

	/*
	Output and Input operators overloaded to allow easy intialization and printing of the matrix
	*/
	friend std::istream& operator >> (std::istream &sin, Matrix2x2& target);
	friend std::ostream& operator << (std::ostream & sout, const Matrix2x2& source);

};


