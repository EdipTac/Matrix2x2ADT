#include "Matrix2x2.h"
/*
@author Edip Tac
@version 1.0
*/

const double Matrix2x2::epsilon = 0.000001;

Matrix2x2::Matrix2x2() {
	for (int i = 0; i < 4; ++i) {
		matrix[i] = 0.00;
	}
}

Matrix2x2::Matrix2x2(double a, double b, double c, double d) {
	matrix[0] = a;
	matrix[1] = b;
	matrix[2] = c;
	matrix[3] = d;
}


double Matrix2x2::determinant() {
	double det = matrix[0] * matrix[3];
	det -= matrix[1] * matrix[2];
	return det;
}

double Matrix2x2::trace() {
	double tr = matrix[0] + matrix[3];
	return tr;
}

bool Matrix2x2::isSymmetric() {
	return (matrix[1] == matrix[2]);
}

bool Matrix2x2::isSimilar(Matrix2x2& rhs) {
	return((this->determinant() == rhs.determinant()) && (this->trace() == rhs.trace()));

}

Matrix2x2 Matrix2x2::transpose() {
	Matrix2x2 other(*this);
	double temp = other.matrix[2];
	other.matrix[2] = other.matrix[1];
	other.matrix[1] = temp;
	return other;
}

Matrix2x2 Matrix2x2::inverse() {
	Matrix2x2 temp(*this);
	double ad = (matrix[0] * matrix[3]);
	double bc = (matrix[1] * matrix[2]);

	if ((ad - bc) == 0.0) {
		try {
			throw std::invalid_argument("Division by zero!");
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << std::endl;
		}
	}


	double fract = 1 / (ad - bc);
	double tempA = temp[0];
	temp.matrix[0] = temp.matrix[3];
	temp.matrix[3] = tempA;
	temp.matrix[1] = -temp.matrix[1];
	temp.matrix[2] = -temp.matrix[2];
	//was instead return (frac*temp);
	temp = fract * temp;
	return (temp);

}

Matrix2x2& Matrix2x2::operator += (const Matrix2x2& rhs) {

	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i] += rhs.matrix[i];
	}
	return *this;
}

Matrix2x2& Matrix2x2::operator += (double x) {

	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i] += x;
	}
	return *this;
}

Matrix2x2& Matrix2x2::operator -= (const Matrix2x2& rhs) {

	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i] -= rhs.matrix[i];
	}
	return *this;
}

Matrix2x2& Matrix2x2::operator -= (double x) {

	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i] -= x;
	}
	return *this;
}

Matrix2x2& Matrix2x2::operator *= (const Matrix2x2& rhs) {

	Matrix2x2 temp(*this);
	matrix[0] = (temp.matrix[0] * rhs.matrix[0]) + (temp.matrix[1] * rhs.matrix[2]);//(aa')+(bc')
	matrix[1] = (temp.matrix[0] * rhs.matrix[1]) + (temp.matrix[1] * rhs.matrix[3]);//(ab')+(bd')
	matrix[2] = (temp.matrix[2] * rhs.matrix[0]) + (temp.matrix[3] * rhs.matrix[2]);//(ca')+(dc')
	matrix[3] = (temp.matrix[2] * rhs.matrix[1]) + (temp.matrix[3] * rhs.matrix[3]);//(cb')+(dd')

	return *this;
}

Matrix2x2& Matrix2x2::operator *= (double x) {

	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i] *= x;
	}
	return *this;
}

Matrix2x2& Matrix2x2::operator /= (const Matrix2x2& rhs) {

	Matrix2x2 temp(rhs);
	temp.inverse();

	//return (M *= M'inversed)
	return(*this *= temp);
}

Matrix2x2& Matrix2x2::operator /= (double x) {

	if (x == 0) {
		try {
			throw std::invalid_argument("Division by zero condition!");
		}

		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << std::endl;
		}
	}


	else {
		x = (1 / x);
		return(*this *= x); //return (M*=x)
	}

}

Matrix2x2 operator + (const Matrix2x2& lhs, const Matrix2x2& rhs) {
	Matrix2x2 temp(lhs);
	temp += rhs;
	return temp;
}

Matrix2x2 operator - (const Matrix2x2& lhs, const Matrix2x2& rhs) {
	Matrix2x2 temp(lhs);
	temp -= rhs;
	return temp;
}

Matrix2x2 operator * (const Matrix2x2& lhs, const Matrix2x2& rhs) {
	Matrix2x2 temp(lhs);
	temp *= rhs;
	return temp;
}

Matrix2x2 operator / (const Matrix2x2& lhs, const Matrix2x2& rhs) {
	Matrix2x2 temp(lhs);
	temp /= rhs;
	return temp;
}
/////

Matrix2x2 operator + (const Matrix2x2& lhs, const double& val) {
	Matrix2x2 temp(lhs);
	temp += val;
	return temp;
}

Matrix2x2 operator - (const Matrix2x2& lhs, const double& val) {
	Matrix2x2 temp(lhs);
	temp -= val;
	return temp;
}

Matrix2x2 operator * (const Matrix2x2& lhs, const double& val) {
	Matrix2x2 temp(lhs);
	temp *= val;
	return temp;
}

Matrix2x2 operator / (const Matrix2x2& lhs, const double& val) {
	Matrix2x2 temp(lhs);
	temp /= val;
	return temp;
}

Matrix2x2 operator + (const double& val, const Matrix2x2& rhs) {
	return(rhs + val);
}

Matrix2x2 operator - (const double& val, const Matrix2x2& rhs) {
	return(-(rhs - val));
}

Matrix2x2 operator * (const double& val, const Matrix2x2& rhs) {
	return(rhs * val);
}

Matrix2x2 operator / (const double& val, const Matrix2x2& rhs) {
	Matrix2x2 temp(rhs);
	temp = temp.inverse();
	return(val * temp);
}

//unary operators
Matrix2x2 Matrix2x2::operator+()const {
	return *this;
}

//
Matrix2x2 Matrix2x2::operator-() const {
	Matrix2x2 temp(*this);
	for (int i = 0; i < temp.matrix.size(); ++i) {
		if (temp.matrix[i] == 0) {
			temp.matrix[i] = temp.matrix[i];
		}
		else {
			temp.matrix[i] = -temp.matrix[i];
		}

	}
	return temp;

}

Matrix2x2 Matrix2x2::operator++() {
	*this += 1;
	return *this;
}

Matrix2x2 Matrix2x2::operator--() {
	return(*this -= 1);
}

Matrix2x2 Matrix2x2::operator++(int) {
	Matrix2x2 temp(*this);
	*this += 1;
	return temp;
}

Matrix2x2 Matrix2x2::operator--(int) {
	Matrix2x2 temp(*this);
	*this -= 1;
	return temp;
}

bool operator == (const Matrix2x2& lhs, const Matrix2x2& rhs) {

	if (lhs.matrix.size() != rhs.matrix.size()) {
		return false;
	}
	//CHECK TO SEE IF THIS WORKS
	for (int i = 0; i < lhs.matrix.size(); ++i) {
		if (std::abs(lhs.matrix[i] - rhs.matrix[i]) > Matrix2x2::epsilon) {
			return false;
		}
	}
	return true;
}

bool operator != (const Matrix2x2& lhs, const Matrix2x2& rhs) {
	return !(lhs == rhs);
}

double& Matrix2x2::operator [] (int i) {

	if (i < 0 || i >= matrix.size()) {
		try {
			throw std::invalid_argument("Index out of bounds");
		}

		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << std::endl;
		}
	}
	return matrix[i];
}

const double& Matrix2x2::operator [] (int i) const {
	if (i < 0 || i >= matrix.size()) {
		try {
			throw std::invalid_argument("Index out of bounds");
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << std::endl;
		}
	}
	return matrix[i];
}

std::vector<double> Matrix2x2::operator()(int x) {

	if (x != 1 && x != 2) {
		try {
			throw std::invalid_argument("invalid argument");
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "Invalid argument: " << ia.what() << std::endl;
		}
	}
	std::vector<double> eigenvals;
	double tr = (*this).trace();
	double trsqrd = tr * tr;
	double det = (*this).determinant();
	double delta = trsqrd - (4 * det);
	if (x == 1) {
		if (delta >= 0.0) {
			eigenvals.push_back((tr + sqrt(delta)) / 2);
		}
		else {
			eigenvals.push_back(tr / 2);
			eigenvals.push_back(sqrt(-delta) / 2);
		}
	}
	if (x == 2) {
		if (delta >= 0.0) {
			eigenvals.push_back((tr - sqrt(delta)) / 2);
		}
		else {
			eigenvals.push_back(tr / 2);
			eigenvals.push_back(-(sqrt(-delta) / 2));
		}
	}
	return eigenvals;
}

double Matrix2x2::operator()() {
	return ((*this).determinant());
}


std::istream& operator >> (std::istream &sin, Matrix2x2& target) {
	std::cout << "To create the following 2x2 matrix:\n"
		<< std::left << std::setw(5) << "|a\t"
		<< std::right << std::setw(5) << "b|\n"
		<< std::left << std::setw(5) << "|\t"
		<< std::right << std::setw(4) << "|\n"
		<< std::left << std::setw(5) << "|c\t"
		<< std::right << std::setw(5) << "d|\n"
		<< "enter four numbers a, b, c, d, in that order:\n";

	for (int i = 0; i < target.matrix.size(); ++i) {
		sin >> target.matrix[i];
	}
	return sin;

}

std::ostream& operator << (std::ostream & sout, const Matrix2x2& source) {

	//sout << std::left << "|" << source.matrix[0] << "\t"
	sout << std::fixed << std::setprecision(2) << std::left << "|" << source.matrix[0] << "\t"
		<< std::right << std::setw(7) << source.matrix[1] << "|\n"//changed from 5
		<< std::left << std::setw(7) << "|\t" //changed from 5
		<< std::right << std::setw(4) << "|\n"//this is left at 4
											  //<< std::left << std::setw(5) << "|" << source.matrix[2] << "\t"
		<< std::left << "|" << source.matrix[2] << "\t"
		<< std::right << std::setw(7) << source.matrix[3] << "|\n"; //changed from 5
	return sout;
}
