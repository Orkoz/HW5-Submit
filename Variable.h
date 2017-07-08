#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include<iostream>
#include<ostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ScriptExceptions.h"
#include "MySharedPtr.h"

class Scalar;
class Matrix;
class Variable;


typedef MySharedPtr<Variable> VarPtr;
typedef vector<int> IdxVec;

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs);

class Variable{
public:
	virtual ~Variable();

	virtual VarPtr Copy() const = 0;
	virtual VarPtr NumElems() const = 0;
	virtual VarPtr Size() const = 0;
	virtual VarPtr Size(int dim) const = 0;
	virtual VarPtr Conv(VarPtr rhs) const = 0; 
	virtual VarPtr Transpose() const = 0;
	virtual void Print(ostream& ro) const = 0;

	virtual int& operator[](int idx) = 0;
	virtual int& operator[](IdxVec v) = 0;
	
	virtual VarPtr operator+(const Variable&)  = 0;
	virtual VarPtr operator+(const Scalar&)  = 0;
	virtual VarPtr operator+(const Matrix&)  = 0;

	virtual VarPtr operator*(const Variable&)  = 0;
	virtual VarPtr operator*(const Scalar&)  = 0;
	virtual VarPtr operator*(const Matrix&)  = 0;

	virtual VarPtr operator<(const Variable&)  = 0;
	virtual VarPtr operator<(const Scalar&)  = 0;
	virtual VarPtr operator<(const Matrix&)  = 0;

	virtual VarPtr operator>(const Variable&)  = 0;
	virtual VarPtr operator>(const Scalar&)  = 0;
	virtual VarPtr operator>(const Matrix&)  = 0;

	virtual VarPtr operator==(const Variable&)  = 0;
	virtual VarPtr operator==(const Scalar&)  = 0;
	virtual VarPtr operator==(const Matrix&)  = 0;

	virtual VarPtr operator&&(const Variable&)  = 0;
	virtual VarPtr operator&&(const Scalar&)  = 0;
	virtual VarPtr operator&&(const Matrix&)  = 0;

	virtual VarPtr operator||(const Variable&)  = 0;
	virtual VarPtr operator||(const Scalar&)  = 0;
	virtual VarPtr operator||(const Matrix&)  = 0;

    friend ostream& operator<<(ostream& ro, const Variable& p);
	friend ostream& operator<<(ostream& ro, VarPtr& p);

	virtual int getValue()const;
	virtual int** getMatrix()const;

};

#endif // _VARIABLE_H_
