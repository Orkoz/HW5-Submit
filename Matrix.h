

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix : public Variable
{
public:
	Matrix(int row, int col, int val);
	Matrix(int startVal, int endVal);
    //Matrix(const Matrix& mat);
	~Matrix();
	VarPtr Copy() const;
	VarPtr NumElems() const;
	VarPtr Size() const;
	VarPtr Size(int dim) const;
	VarPtr Conv(VarPtr rhs) const; 
	VarPtr Transpose() const;
	void Print(ostream& ro) const;
	int** getMatrix()const;

	int& operator[](int idx);
	int& operator[](IdxVec v);
	int& operator[](IdxVec v) const;

	VarPtr operator+(const Variable&) ;
	VarPtr operator+(const Scalar&) ;
	VarPtr operator+(const Matrix&) ;

	VarPtr operator*(const Variable&) ;
	VarPtr operator*(const Scalar&) ;
	VarPtr operator*(const Matrix&) ;

	VarPtr operator<(const Variable&) ;
	VarPtr operator<(const Scalar&) ;
	VarPtr operator<(const Matrix&) ;

	VarPtr operator>(const Variable&) ;
	VarPtr operator>(const Scalar&) ;
	VarPtr operator>(const Matrix&) ;

	VarPtr operator==(const Variable&) ;
	VarPtr operator==(const Scalar&) ;
	VarPtr operator==(const Matrix&) ;

	VarPtr operator&&(const Variable&) ;
	VarPtr operator&&(const Scalar&) ;
	VarPtr operator&&(const Matrix&) ;

	VarPtr operator||(const Variable&) ;
	VarPtr operator||(const Scalar&) ;
	VarPtr operator||(const Matrix&) ;


private:
	int row_;
	int col_;
	int** matrix_;
};
#endif
