#include"Matrix.h"
#include"ScriptExceptions.h"
using namespace std;


//*************************************************************************
//* Function name: Constructor by Value
//* Description: initialized new matrix(rowXcol) with val
//* Parameters:
//*		row – the number of rows in the new matrix.
//*		col – the number of columns in the new matrix.
//*		val – the value in each cell of the new matrix.
//* Return Value: Matrix pointer.
//*************************************************************************

Matrix::Matrix(int row, int col, int val) : row_(row), col_(col){
	matrix_ = new int*[row_];
    int i, j;
	for (i = 0; i < row_; i++) {
		matrix_[i] = new int[col_];
		for (j = 0; j < col_; j++)
			matrix_[i][j] = val;
	}
}


//*************************************************************************
//* Function name: Constructor by Value
//* Description: initialized new matrix(1XendVal - startVal) with startVal in the first cell increasing in 1 for each cell to the end.
//* Parameters:
//*		startVal – start value.
//*		endVal – end value.
//* Return Value: Matrix pointer.
//*************************************************************************

Matrix::Matrix(int startVal, int endVal) : row_(1), col_ (endVal - startVal + 1) {
    col_ = (col_ < 0) ? 0 : col_;
    matrix_ = new int*[row_];
    matrix_[row_-1] = new int[col_];
	int val = startVal;
    int i;
	for (i = 0; i < col_; i++, val++) {
		matrix_[row_-1][i] = val;
	}
}


//*************************************************************************
//* Function name: Destructor
//* Description:
//* Parameters: none.
//* Return Value: none.
//*************************************************************************

Matrix::~Matrix() {
    int i;
	for (i = 0; i < row_; i++)
		delete[] matrix_[i];
	delete[] matrix_;
}


//*************************************************************************
//* Function name: Copy
//* Description: creates a copy of the Matrix.
//* Parameters: none.
//* Return Value: MySharedPtr<Variable> object containing the new Matrix.
//*************************************************************************

VarPtr Matrix::Copy() const {
	VarPtr mat_c = VarPtr(new Matrix(row_, col_, 0));
	int** mat_c_pointer = mat_c->getMatrix();
    int i, j;
	for (i = 0; i < row_; i++) {
		for (j = 0; j < col_; j++) {
			mat_c_pointer[i][j] = matrix_[i][j];
		}
	}
    return mat_c;
}


//*************************************************************************
//* Function name: NumElems
//* Description: returns the number of cells in the Matrix.
//* Parameters: none.
//* Return Value: MySharedPtr<Variable> object containing Scaler object with the value.
//*************************************************************************

VarPtr Matrix::NumElems() const {
    int num = row_ * col_;
	return VarPtr(new Scalar(num));
}


//*************************************************************************
//* Function name: Size
//* Description: returns matrix(1X2) with the rows size at the first cell and the columns size  //*		in the second.
//* Parameters: none.
//* Return Value: MySharedPtr<Variable> object containing Matrix object with the values.
//*************************************************************************

VarPtr Matrix::Size() const {
	Matrix* new_matrix = new Matrix(1, 2, 0);
	new_matrix->matrix_[0][0] = row_;
	new_matrix->matrix_[0][1] = col_;
	return VarPtr(new_matrix);
}


//*************************************************************************
//* Function name: Size
//* Description: returns the size of the given dimension.
//* Parameters:
//*		dim – the dimension that its size will be returned.
//* Return Value: MySharedPtr<Variable> object containing Scalar object with the value.
//*************************************************************************

VarPtr Matrix::Size(int dim) const {
    if (dim == 1) {
        return VarPtr(new Scalar(row_));
    }else if (dim == 2){
        return VarPtr(new Scalar(col_));
    }

    throw BAD_INPUT;
}


//*************************************************************************
//* Function name: Scalar::Conv
//* Description: Given by the staff of the course.
//* Parameters:
//* Return Value:
//*************************************************************************

VarPtr Matrix::Conv(VarPtr rhs) const {
	if ((*NumElems())[1] == 0)
		return VarPtr(new Matrix(*this));
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Matrix(row_, col_, 0));

	VarPtr pRet = VarPtr(new Matrix(row_, col_, 0));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	int maxRowShift = rhsRows - rhsCenter[0];
	int minRowShift = 1 - rhsCenter[0];
	int maxColShift = rhsCols - rhsCenter[1];
	int minColShift = 1 - rhsCenter[1];
	for (int resRow = 1; resRow <= row_; ++resRow)
		for (int resCol = 1; resCol <= col_; ++resCol)
		{
			IdxVec resIdx = { resRow,resCol };
			for (int rowShift = minRowShift; rowShift <= maxRowShift; ++rowShift)
				for (int colShift = minColShift; colShift <= maxColShift; ++colShift)
				{
					try
					{
						(*pRet)[resIdx] += ((*this)[resIdx + IdxVec{ -rowShift,-colShift }] * (*rhs)[rhsCenter + IdxVec{rowShift,colShift}]);
					}
					catch (...)
					{
						// convolution is zero padded (no action required)
					}
				}
		}
	return pRet;
}


//*************************************************************************
//* Function name: Transpose
//* Description: creates a transposed copy of the Matrix.
//* Parameters: none.
//* Return Value: MySharedPtr<Variable> object containing the new Matrix.
//*************************************************************************

VarPtr Matrix::Transpose() const {
	Matrix* tranpose_matrix = new Matrix(col_, row_, 0);
    int i, j;
	for (i = 0; i < row_; i++)
		for (j = 0; j < col_; j++)
            tranpose_matrix->matrix_[j][i] = matrix_[i][j];

	return VarPtr(tranpose_matrix);
}


//*************************************************************************
//* Function name: Print
//* Description: prints the matrix cell on the screen on a ‘matrix’ formation.
//* Parameters:
//*		ro – an ostream object.
//* Return Value: none.
//*************************************************************************

void Matrix::Print(ostream &ro) const {
    int i, j;
	for (i = 0; i < row_; i++) {
		for (j = 0; j < col_; j++)
			ro << matrix_[i][j] << "\t";
		if (i != (row_-1))
			ro << "\t\n";
	}
}

//*************************************************************************
//* Function name: getValue and getMatix 
//* Description: returns pointer to variable
//* Parameters:
//* Return Value: int** or 0
//*************************************************************************


int** Matrix::getMatrix() const {
	return matrix_;
}


//*************************************************************************
//* Function name: operator[]
//* Description: returns the value of the given index by column major.
//* Parameters:
//*		idx – given index by column major.
//* Return Value: the value of the cell.
//*************************************************************************

int& Matrix::operator[](int idx) {
	if ((col_*row_) < idx || idx < 1){
		throw INDEX_OUT_OF_RANGE;
	}

	int col = (idx-1) / row_; //  idx mod row_;
	int row = idx - col*row_ - 1;
	return matrix_[row][col];

}

//*************************************************************************
//* Function name: operator[]
//* Description: returns the value of the given index.
//* Parameters:
//*		v – a vector of matrix indices.
//* Return Value: the value of the cell.
//*************************************************************************

int& Matrix::operator[](IdxVec v) {
	if (v.size() != 2 || v[0] > row_ || v[0] <1 || v[1] > col_ || v[1] < 1){
		throw INDEX_OUT_OF_RANGE;
	}
	
	return matrix_[v[0]-1][v[1]-1];  // '-1' to adjust index to array
}

int& Matrix::operator[](IdxVec v) const {
    if (v.size() != 2 || v[0] > row_ || v[0] <1 || v[1] > col_ || v[1] < 1){
        throw INDEX_OUT_OF_RANGE;
    }

    return matrix_[v[0]-1][v[1]-1]; // '-1' to adjust index to array
}


//*************************************************************************
//* Function name: operator+
//* Description: handles adding numbers. dealing separately with adding
//*              scalar and scalar (sends for operator from class matrix),
//*              scalar and matrix or scalar and variable (changes the
//*              order so the dynamic type could take control).
//* Parameters: variables to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Matrix::operator+(const Variable& variable) {
    VarPtr new_obj = variable.Copy();
    return *(new_obj.get()) + *this;
}
VarPtr Matrix::operator+(const Scalar& scalar) {
    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = matrix_[i][j] + scalar.getValue();

    return VarPtr(new_matrix);
}
VarPtr Matrix::operator+(const Matrix& matrix) {
    if (row_ != matrix.row_ || col_ != matrix.col_)
        throw BAD_MAT_DIMS("+");

    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = matrix_[i][j] + matrix.matrix_[i][j];

    return VarPtr(new_matrix);
}


//*************************************************************************
//* Function name: operator*
//* Description: handles multiplication numbers. dealing separately with adding
//*              scalar and scalar (sends for operator from class matrix),
//*              scalar and matrix or scalar and variable (changes the
//*              order so the dynamic type could take control).
//* Parameters: variables to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Matrix::operator*(const Variable& variable) {
    VarPtr new_obj = variable.Copy();
    return *(new_obj.get()) * (*this);
}
VarPtr Matrix::operator*(const Scalar& scalar) {
    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = matrix_[i][j] * scalar.getValue();

    return VarPtr(new_matrix);
}
VarPtr Matrix::operator*(const Matrix& first_matrix) {
    if (row_ != first_matrix.col_)
        throw BAD_MAT_PROD;

    Matrix* new_matrix = new Matrix(first_matrix.row_, col_, 0);
    int k, i, j;
    for (k = 0; k < first_matrix.row_; ++k) {
        for (i = 0; i <  col_; i++) {
            int mul_sum = 0;
            for (j = 0; j < row_; j++)
                mul_sum = mul_sum + (matrix_[j][i]*first_matrix.matrix_[k][j]);
            new_matrix->matrix_[k][i] = mul_sum;
        }
    }

    return VarPtr(new_matrix);
}


//*************************************************************************
//* Function name: operator<
//* Description: handles logic <. dealing separately with adding
//*              scalar and scalar (sends for operator from class matrix),
//*              scalar and matrix or scalar and variable (changes the
//*              order so the dynamic type could take control).
//* Parameters: variables to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Matrix::operator<(const Variable& variable) {
    VarPtr new_obj = variable.Copy();
    return *(new_obj.get()) > *this;
}
VarPtr Matrix::operator<(const Scalar& scalar) {
    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = (int)(matrix_[i][j]<scalar.getValue());

    return VarPtr(new_matrix);
}
VarPtr Matrix::operator<(const Matrix& matrix) {
    if (row_ != matrix.row_ || col_ != matrix.col_)
        throw BAD_MAT_DIMS("> / <");

    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = (matrix_[i][j] < matrix.matrix_[i][j]);

    return VarPtr(new_matrix);
}


//*************************************************************************
//* Function name: operator>
//* Description: handles logic >. dealing separately with adding
//*              scalar and scalar (sends for operator from class matrix),
//*              scalar and matrix or scalar and variable (changes the
//*              order so the dynamic type could take control).
//* Parameters: variables to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Matrix::operator>(const Variable& variable) {
    VarPtr new_obj = variable.Copy();
    return *(new_obj.get()) < *this;
}
VarPtr Matrix::operator>(const Scalar& scalar) {
    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = (int)(matrix_[i][j]>scalar.getValue());

    return VarPtr(new_matrix);
}
VarPtr Matrix::operator>(const Matrix& matrix) {
    if (row_ != matrix.row_ || col_ != matrix.col_)
        throw BAD_MAT_DIMS("> / <");

    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = (matrix_[i][j] > matrix.matrix_[i][j]);

    return VarPtr(new_matrix);
}


//*************************************************************************
//* Function name: operator==
//* Description: handles logic ==. dealing separately with adding
//*              scalar and scalar (sends for operator from class matrix),
//*              scalar and matrix or scalar and variable (changes the
//*              order so the dynamic type could take control).
//* Parameters: variables to be added
//* Return Value: the new scalar or matrix
//*************************************************************************

VarPtr Matrix::operator==(const Variable& variable) {
    VarPtr new_obj = variable.Copy();
    return *(new_obj.get()) == *this;
}
VarPtr Matrix::operator==(const Scalar& scalar) {
    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = (int)(matrix_[i][j]==scalar.getValue());

    return VarPtr(new_matrix);
}
VarPtr Matrix::operator==(const Matrix& matrix) {
    if (row_ != matrix.row_ || col_ != matrix.col_)
        throw BAD_MAT_DIMS("==");

    Matrix* new_matrix = new Matrix(row_, col_, 0);
    int i, j;
    for (i = 0; i < row_; i++)
        for (j = 0; j < col_; j++)
            new_matrix->matrix_[i][j] = (matrix_[i][j] == matrix.matrix_[i][j]);

    return VarPtr(new_matrix);
}


//*************************************************************************
//* Function name: operator&&
//* Description: invalid operation.
//* Parameters:
//* Return Value: throw BAD_INPUT exception;
//*************************************************************************

VarPtr Matrix::operator&&(const Variable& variable) {
    throw BAD_INPUT;
}
VarPtr Matrix::operator&&(const Scalar& scalar) {
    throw BAD_INPUT;
}
VarPtr Matrix::operator&&(const Matrix& matrix) {
    throw BAD_INPUT;
}


//*************************************************************************
//* Function name: operator||
//* Description: invalid operation.
//* Parameters:
//* Return Value: throw BAD_INPUT exception;
//*************************************************************************

VarPtr Matrix::operator||(const Variable& variable) {
    throw BAD_INPUT;
}
VarPtr Matrix::operator||(const Scalar& scalar) {
    throw BAD_INPUT;
}
VarPtr Matrix::operator||(const Matrix& matrix) {
    throw BAD_INPUT;
}
