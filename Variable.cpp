#include<iostream>
#include"Variable.h"
#include"ScriptExceptions.h"

using namespace std;


//*************************************************************************
//* Function name: operator<<
//* Description: an operator<< to override default operator to call our 
//*              print function within each variable
//* Parameters: ro - the out stream, p - variable type
//* Return Value:  ro - the updated out stream
//*************************************************************************

ostream& operator<< (ostream& ro, const Variable& p) {
	p.Print(ro);
	return ro;
}

ostream& operator<<(ostream& ro, VarPtr& p) {
	(*p).Print(ro);
	return ro;
}

//*************************************************************************
//* Function name: operator+
//* Description: Given by the staff of the course
//*              
//* Parameters:
//* Return Value: 
//*************************************************************************

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs) {
	if (lhs.size() != rhs.size())
		throw ScriptException("IdxVec operator+, vector sizes mismatch.");
	IdxVec res = lhs;
	int resSize = res.size();
	int ii;
	for (ii = 0;ii < resSize;++ii)
		res[ii] += rhs[ii];
	return res;
}

Variable::~Variable() {}

//*************************************************************************
//* Function name: getVal
//* Description: default func to get value of variable
//* Parameters: 
//* Return Value:  0
//*************************************************************************

int Variable::getValue() const {
	return 0;
}

//*************************************************************************
//* Function name: getMat
//* Description: default func to get pointer for matrix
//* Parameters:
//* Return Value:  nullptr
//*************************************************************************

int ** Variable::getMatrix() const {
	return nullptr;
}