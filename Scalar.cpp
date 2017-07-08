#include"Scalar.h"
#include"Matrix.h"
#include"Variable.h"
#include"ScriptExceptions.h"

using namespace std;


//*************************************************************************
//* Function name: Scalar::Conv
//* Description: Given by the staff of the course. 
//* Parameters:
//* Return Value: 
//*************************************************************************

VarPtr Scalar::Conv(VarPtr rhs) const {
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Scalar(0));
	VarPtr pRet = VarPtr(new Scalar(*this));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	(*pRet)[1] *= (*rhs)[rhsCenter];
	return pRet;
}

//*************************************************************************
//* Function name: Scalar::Scalar c-tor's, and d-tor
//* Description: creating a new scalar with value 'val' or 0 if not given.
//* Parameters: val (if given) an integer
//* Return Value: none
//*************************************************************************

Scalar::Scalar(int val): val_(val) {}

Scalar::Scalar(): val_(0) {}


//*************************************************************************
//* Function name: getVal
//* Description: returns the Scalar value.
//* Parameters: none.
//* Return Value: integer - the Scalar value.
//*************************************************************************

int Scalar::getValue() const{
	return val_;
}

//*************************************************************************
//* Function name: setVal
//* Description: sets internal integer to new integer
//* Parameters: int val
//* Return Value: none.
//*************************************************************************

void Scalar::setValue(int val) {
	val_ = val;
}

//*************************************************************************
//* Function name: Scalar::Copy()
//* Description: makes a new copy of the scalar
//* Parameters: none
//* Return Value: a VarPtr to the new object
//*************************************************************************

VarPtr Scalar::Copy() const {
	VarPtr scalar_c = VarPtr(new Scalar(val_));
	return scalar_c;
}

//*************************************************************************
//* Function name: Scalar::NumElems()
//* Description: returns 1 because it is a scalar with only one value
//* Parameters: none
//* Return Value: a new scalar with value 1
//*************************************************************************

VarPtr Scalar::NumElems() const {
	VarPtr scalar_c = VarPtr(new Scalar(1));
	return scalar_c;
}

//*************************************************************************
//* Function name: Scalar::Size()
//* Description: returns a new natrix with dim' 1x2 with values 1
//*              or if given a dim' than just giving back a scalar with value 1
//* Parameters: int dim
//* Return Value: a new scalar or matrix, filled with 1's
//*************************************************************************

VarPtr Scalar::Size() const {
	VarPtr size_matrix(new Matrix(1, 2, 1));
	return size_matrix;
}

VarPtr Scalar::Size(int dim) const {
	VarPtr scalar_size(new Scalar(1));
	return scalar_size;
}

//*************************************************************************
//* Function name: Scalar::Transpose()
//* Description: doing transpose to a scalars just copies the scalar
//* Parameters: none
//* Return Value: returns copies scalar
//*************************************************************************

VarPtr Scalar::Transpose() const {
	VarPtr scalar_t = this->Copy();
	return scalar_t;
}

//*************************************************************************
//* Function name: Scalar::Print
//* Description: print function for scalar
//* Parameters:out stream ro
//* Return Value: changes the out stream accordingly
//*************************************************************************

void Scalar::Print(ostream& ro) const {
	ro << val_;
}

//*************************************************************************
//* Function name: Scalar::operator+
//* Description: handles adding numbers. dealing separtadly with adding
//*              scalar and scalar, scalar and matrix (sends for operator 
//*              from class matrix) or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Scalar::operator+(const Variable & rhs)  {
	VarPtr to_be_added = rhs.Copy();
	return *(to_be_added.get()) + *this;
}

VarPtr Scalar::operator+(const Scalar & rhs)  {
	VarPtr sum = VarPtr(new Scalar( val_ + rhs.val_));
	return sum;
}

VarPtr Scalar::operator+(const Matrix & rhs)  {
	VarPtr to_be_added = rhs.Copy();
	return *(to_be_added.get()) + *this;
}

//*************************************************************************
//* Function name: Scalar::operator*
//* Description: handles multypling numbers. dealing separtadly with mul'
//*              scalar and scalar, scalar and matrix (sends for operator 
//*              from class matrix) or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Scalar::operator*(const Variable & rhs)  {
	VarPtr to_be_multiplied = rhs.Copy();
	return *(to_be_multiplied.get()) * (*this);
}

VarPtr Scalar::operator*(const Scalar & rhs)  {
	VarPtr multiply = VarPtr(new Scalar((val_) * (rhs.val_)));
	return multiply;
}

VarPtr Scalar::operator*(const Matrix & rhs)  {
	VarPtr to_be_multiplied = rhs.Copy();
	return *(to_be_multiplied.get()) * (*this);
}

//*************************************************************************
//* Function name: Scalar::operator<
//* Description: handles logic <. dealing separtadly with logic between
//*              scalar and scalar, scalar and matrix (sends for operator 
//*              from class matrix) or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to do the logic with
//* Return Value: the new scalar or matrix with result of logic function
//*************************************************************************

VarPtr Scalar::operator<(const Variable & rhs)  {
	VarPtr to_be_checked = rhs.Copy();
	return *(to_be_checked.get()) > (*this);
}

VarPtr Scalar::operator<(const Scalar & rhs)  {
	if (val_ < rhs.val_)
        return VarPtr(new Scalar(1));

    return VarPtr(new Scalar(0));

}

VarPtr Scalar::operator<(const Matrix & rhs)  {
	VarPtr logic_answer = rhs.Copy();
	return *(logic_answer.get()) > (*this);
}

//*************************************************************************
//* Function name: Scalar::operator>
//* Description: handles logic >. dealing separtadly with logic between
//*              scalar and scalar, scalar and matrix (sends for operator 
//*              from class matrix) or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to do the logic with
//* Return Value: the new scalar or matrix with result of logic function
//*************************************************************************

VarPtr Scalar::operator>(const Variable & rhs)  {
	VarPtr to_be_checked = rhs.Copy();
	return *(to_be_checked.get()) < (*this);
}

VarPtr Scalar::operator>(const Scalar & rhs)  {
    if (val_ > rhs.val_)
        return VarPtr(new Scalar(1));

    return VarPtr(new Scalar(0));
}

VarPtr Scalar::operator>(const Matrix & rhs)  {
	VarPtr logic_answer = rhs.Copy();
	return *(logic_answer.get()) < (*this);
}

//*************************************************************************
//* Function name: Scalar::operator==
//* Description: handles logic ==. dealing separtadly with logic between
//*              scalar and scalar, scalar and matrix (sends for operator 
//*              from class matrix) or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to do the logic with
//* Return Value: the new scalar or matrix with result of logic function
//*************************************************************************

VarPtr Scalar::operator==(const Variable & rhs)  {
	VarPtr to_be_checked = rhs.Copy();
	return *(to_be_checked.get()) == (*this);
}

VarPtr Scalar::operator==(const Scalar & rhs)  {
	if (val_ == rhs.val_)
        return VarPtr(new Scalar(1));

    return VarPtr(new Scalar(0));

}

VarPtr Scalar::operator==(const Matrix & rhs)  {
	VarPtr logic_answer = rhs.Copy();
	return *(logic_answer.get()) == (*this);
}

//*************************************************************************
//* Function name: Scalar::operator&&
//* Description: handles logic &&. dealing separtadly with logic between
//*              scalar and scalar, scalar and matrix (throws exception)
//*              or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to do the logic with
//* Return Value: the new scalar or matrix with result of logic function
//*************************************************************************

VarPtr Scalar::operator&&(const Variable & rhs)  {
	VarPtr to_be_checked = rhs.Copy();
	return *(to_be_checked.get()) && (*this);

}

VarPtr Scalar::operator&&(const Scalar & rhs)  {
	if ((val_ == 1) && (rhs.val_ == 1))
		return VarPtr(new Scalar(1));

    return VarPtr(new Scalar(0));

}

VarPtr Scalar::operator&&(const Matrix & rhs)  {
	throw BAD_INPUT;
}

//*************************************************************************
//* Function name: Scalar::operator||
//* Description: handles logic ||. dealing separtadly with logic between
//*              scalar and scalar, scalar and matrix (throws exception)
//*              or scalar and variable, changes the
//*              order so the dynamic type could take control.
//* Parameters: variable & rhs to do the logic with
//* Return Value: the new scalar or matrix with result of logic function
//*************************************************************************

VarPtr Scalar::operator||(const Variable & rhs)  {
	VarPtr to_be_checked = rhs.Copy();
	return *(to_be_checked.get()) || (*this);
}

VarPtr Scalar::operator||(const Scalar & rhs)  {
	if ((val_ == 0) && (rhs.val_ == 0))
        return VarPtr(new Scalar(0));

    return VarPtr(new Scalar(1));

}

VarPtr Scalar::operator||(const Matrix & rhs)  {
	throw BAD_INPUT;
}

//*************************************************************************
//* Function name:  Scalar::operator[]
//* Description: returns the value of the specific index
//*              because it is a scalar, only index is 1 so throws exception
//*              otherwise. returns by reference or by value
//* Parameters: int idx or IdxVec (index vector)
//* Return Value: the value.
//*************************************************************************

int & Scalar::operator[](int idx){
	if (idx != 1)
		throw INDEX_OUT_OF_RANGE;

    return val_;

}

int & Scalar::operator[](IdxVec v) {
	if ((v[0] != 1) && (v[1] != 1))
		throw INDEX_OUT_OF_RANGE;
	return val_;
}



