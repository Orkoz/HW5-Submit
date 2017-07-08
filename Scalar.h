#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"
#include"Matrix.h"

class Scalar : public Variable 
{
public:

	Scalar();
	Scalar(int val);
	//~Scalar();

	VarPtr Size() const;
	VarPtr Size(int d) const;
	VarPtr Copy() const;
	VarPtr NumElems() const;
	VarPtr Transpose() const;
	void Print(ostream& ro) const;
	int getValue() const;
	void setValue(int val);

	VarPtr operator+(const Variable&)   ;
	VarPtr operator+(const Scalar&)   ;
	VarPtr operator+(const Matrix&)   ;

	VarPtr operator*(const Variable&)   ;
	VarPtr operator*(const Scalar&)   ;
	VarPtr operator*(const Matrix&)   ;

	VarPtr operator<(const Variable&)   ;
	VarPtr operator<(const Scalar&)   ;
	VarPtr operator<(const Matrix&)   ;

	VarPtr operator>(const Variable&)   ;
	VarPtr operator>(const Scalar&)   ;
	VarPtr operator>(const Matrix&)   ;

	VarPtr operator==(const Variable&)   ;
	VarPtr operator==(const Scalar&)   ;
	VarPtr operator==(const Matrix&)   ;

	VarPtr operator&&(const Variable&)   ;
	VarPtr operator&&(const Scalar&)   ;
	VarPtr operator&&(const Matrix&)   ;

	VarPtr operator||(const Variable&)   ;
	VarPtr operator||(const Scalar&)   ;
	VarPtr operator||(const Matrix&)   ;


	int& operator[](int idx);
	int& operator[](IdxVec v) ;

	VarPtr Conv(VarPtr rhs) const;

private:
	int val_;
};

#endif // _SCALAR_H_
