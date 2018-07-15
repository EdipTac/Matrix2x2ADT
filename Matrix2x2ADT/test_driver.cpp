#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "Matrix2x2.h"
using namespace std;

/*
Tests class Matrix2x2. Specifically, tests constructors, compound assignment
operator overloads, basic arithmetic operator overloads, unary +, unary -,
pre/post-increment/decrement, subscripts, function objects, eigenvalues,
input/output operators, isSymetric, isSimilar, determinant, trace, and
equality relational operators.

The test starts with matrix

|2.00 -1.00|
|          |
|1.00  2.00|

with these two complex eigenvalues:
root 1: 2 +1i
root 2: 2 -1i

@return 0 to indicate success.
*/

/*
Free function to print the EigenValues
*/
void printEigenvalues(const std::vector<double> &eigenvals, int x) {
	if (x == 1) {
		std::cout << "root " << x << ": " << eigenvals[0] << "+" << eigenvals[1] << "i" << std::endl;
	}

	if (x == 2) {
		//check if - sign has to be added manually or something
		std::cout << "root " << x << ": " << eigenvals[0] << eigenvals[1] << "i" << std::endl;
	}

}
int main()
{
	Matrix2x2 m1(2, -1, 1, 2); // test constructor
	cout << "m1\n" << m1 << endl;    // operator<<, the output operator

	Matrix2x2  m1Inv = m1.inverse();    // inverse
	cout << "m1.invers()\n" << m1Inv << endl;

	Matrix2x2 m1Inv_times_m1 = m1Inv*m1;
	cout << "m1 * m1.invers()\n" << m1Inv_times_m1 << endl;
	// the inverse of any 2x2 multiplied by the 2x2 itself must give the identity 2x2 
	assert(m1Inv_times_m1 == Matrix2x2(1, 0, 0, 1));

	Matrix2x2 m1_times_m1Inv = m1 * m1Inv;
	cout << "m1.invers() * m1\n" << m1_times_m1Inv << endl;
	// any 2x2 multiplied by its inverse must give the identity 2x2 
	assert(m1_times_m1Inv == Matrix2x2(1, 0, 0, 1));

	cout << "det(m1) =   " << m1.determinant() << "\n";
	cout << "trace(m1) = " << m1.trace() << "\n\n";

	// test function object, operator()(int)
	std::vector<double > root1 = m1(1); // real = 2.0, imag = 1
	assert(std::abs(root1[0] - 2) < 1.e-6);
	assert(std::abs(root1[1] - 1) < 1.e-6);
	// implement this free function to print a given eigenvalue (see output)
	printEigenvalues(root1, 1);    // root 1: 2 +1i

								   // test function object, operator()(int)
	std::vector<double > root2(m1(2)); // real = 2.0, imag = -1
	assert(std::abs(root2[0] - 2) < 1.e-6);
	assert(std::abs(root2[1] - (-1)) < 1.e-6);
	// implement this free function to print a given eigenvalue
	printEigenvalues(root2, 2);   // root 2: 2 -1i

	cout << "\n";

	Matrix2x2 m2 = m1 + 1;  // Mat + int, and assignment op=
	assert(m2 == Matrix2x2(3, 0, 2, 3));
	cout << "m2\n" << m2 << endl;

	m2 = 1 + m1;  // op=, int + Mat
	assert(m2 == Matrix2x2(3, 0, 2, 3));

	Matrix2x2 m3 = m2 - 1;  // Mat -int
	assert(m3 == m1);
	cout << "m3\n" << m3 << endl;

	Matrix2x2 m4 = 1 - m3; // int - Mat 
	cout << "m4\n" << m4 << endl;
	assert(m4 == Matrix2x2(-1, 2, 0, -1));


	Matrix2x2 m5 = m4 * 5; // Mat * int
	cout << "m5\n" << m5 << endl;
	assert(m5 == Matrix2x2(-5, 10, 0, -5));

	Matrix2x2 m6 = 10 * m5; // int * Mat
	cout << "m6\n" << m6 << endl;
	assert(m6 == Matrix2x2(-50, 100, 0, -50));
	assert(m6 / 10 == m5);  // Mat / int
	assert(10 / m6 == 10 * m6.inverse());  // int / Mat, inverse
	assert(5 * m4 * 10 == m6);  // int * Mat * int == Mat

	Matrix2x2 m7 = m1++;
	cout << "m1\n" << m1 << endl;
	cout << "m7\n" << m7 << endl;
	assert(m7 == m1 - Matrix2x2(1, 1, 1, 1));

	Matrix2x2 m8 = --m1;  // --Mat
	cout << "m1\n" << m1 << endl;
	cout << "m8\n" << m8 << endl;
	assert(m8 == m1);
	m8--;  // Mat--
	cout << "m8\n" << m8 << endl;
	assert(m1 == 1 + m8);
	assert(m1 - 1 == m8);
	assert(-m1 + 1 == -m8);
	assert(2 * m1 == m8 + m1 + 1);
	assert(m1 * m1 == m1 *(1 + m8));
	cout << "m8 is " << (m8.isSymmetric() ? "" : "not") << " symmetric\n";
	Matrix2x2 m9(123, 6, 6, 4567.89);
	cout << "m9\n" << m9 << endl;
	cout << "m9 is " << (m9.isSymmetric() ? "" : "not") << " symmetric\n";

	// subscripts (non-const)
	m9[0] = 3;
	m9[1] = 1;
	m9[2] = 7;
	m9[3] = 4;
	cout << "m9\n" << m9 << endl;
	assert(m9 == Matrix2x2(3, 1, 7, 4));
	cout << "det(m1) =   " << m1() << "\ntrace(m1) = " << m1.trace() << "\n\n";
	cout << "det(m9) =   " << m9() << "\ntrace(m9) = " << m9.trace() << "\n\n";
	cout << "m9 is " << (m9.isSimilar(m1) ? "" : "not") << " similar to m1\n";

	// subscripts (const version)
	const Matrix2x2 cm9{ m9 };
	cout << "cm9\n" << cm9 << endl;

	m9 += m9;
	cout << "m9\n" << m9 << endl;
	assert(m9 == 2 * Matrix2x2(3, 1, 7, 4));

	Matrix2x2 m10;
	m10 += (m9 / 2);
	cout << "m10\n" << m10 << endl;
	assert(m10 == Matrix2x2(3, 1, 7, 4));

	m10 *= 2;
	cout << "m10\n" << m10 << endl;
	assert(m10 == m9);

	m10 /= 2;
	cout << "m10\n" << m10 << endl;
	assert(m10 == m9 / 2);

	m10 += 10;
	cout << "m10\n" << m10 << endl;
	assert(m10 == (m9 + 20) / 2);

	m10 -= 10;
	cout << "m10\n" << m10 << endl;
	assert(m10 == 0.5 * m9);

	// testing transpose()
	Matrix2x2 m11 = m10.transpose();
	cout << "m11\n" << m11 << endl;
	assert(m10 == m11.transpose());

	//testing operator>>
	Matrix2x2 m12;

	cout << "In response to the following prompt, \n";
	cout << "enter the numbers 10, 20, 30, 40, in that order\n\n";

	cin >> m12;
	cout << "\nm12\n" << m12 << endl;
	assert(m12 == Matrix2x2(10, 20, 30, 40));

	// testing unary operators + and -
	Matrix2x2 m13 = -m11;
	cout << "m13\n" << m13 << endl;
	assert(+m11 == -m13);

	cout << "Test completed successfully!" << endl;
	system("pause");
	return 0;
}
