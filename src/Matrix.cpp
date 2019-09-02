#include "Matrix.hpp"

//************************************************************
Matrix::Matrix()
{
	setMatrixSize(0,0);
}


//************************************************************
Matrix::Matrix(int rowCount, int colCount)
{
	// Define the matrix size
	this->rowCount = rowCount;
	this->colCount = colCount;

	// Define the actually matrix size
	this->matrix.resize(rowCount);
	for(auto &row : this->matrix)
	{
		row.resize(colCount);
	}
}


//************************************************************
Matrix::Matrix(vector<vector<float>> matrix)
{
	int colCount;
	int rowCount;

	rowCount = matrix.size();
	colCount = matrix[0].size();

	
	//this is for checking if the matrix format is correct.
	for (auto &row : matrix)
	{
		if ((int)row.size() != colCount)
			throw "The size is incorrect";
	}
	
	
	this->matrix = matrix;
	this->rowCount = rowCount;
	this->colCount = colCount;
}





Matrix Matrix::operator*(Matrix & rightMatrix)
{ 
	if(this->colCount != rightMatrix.rowCount)
		throw "Left mat's col number is not equal to right mat's row...";

	vector<vector<float> > vectors;

	for(auto &rowForLeft : this->matrix)
	{
		vectors.push_back( this->LinearCombiVectorMatrix(rowForLeft, rightMatrix) );
	}

	return Matrix(vectors);
}


//************************************************************
Matrix Matrix::operator*(float scaler)
{
	Matrix result(this->rowCount, this->colCount);

	for (int rowCount = 0; rowCount < this->rowCount; rowCount++)
	{
		for (int colCount = 0; colCount < this->colCount; colCount++)
		{
			result.matrix[rowCount][colCount] = this->matrix[rowCount][colCount] * scaler;
		}
	}

	return result;
}

//************************************************************
Matrix operator*(float scaler, Matrix mat)
{
	Matrix result(mat.rowCount, mat.colCount);

	for (int rowCount = 0; rowCount < mat.rowCount; rowCount++)
	{
		for (int colCount = 0; colCount < mat.colCount; colCount++)
		{
			result.matrix[rowCount][colCount] = mat.matrix[rowCount][colCount] * scaler;
		}
	}

	return result;
}


//************************************************************
Matrix Matrix::operator+(Matrix & rightMatrix)
{
	Matrix result(this->rowCount, this->colCount);
	auto iterRRow = rightMatrix.matrix.begin();
	auto iterLRow = this->matrix.begin();

	for (int rowCount = 0; rowCount < this->rowCount; rowCount++)
	{
		for (int colCount = 0; colCount < this->colCount; colCount++)
		{
			result.matrix[rowCount][colCount] = (*iterRRow)[colCount] + (*iterLRow)[colCount];
		}
		iterRRow++;
		iterLRow++;
	}

	return result;
}


// I am debugging this function now 
//************************************************************
Matrix Matrix::operator-(Matrix &rightMatrix)
{
	Matrix result(this->rowCount, this->colCount);
	auto iterRRow = rightMatrix.matrix.begin();
	auto iterLRow = this->matrix.begin();

	for (int rowCount = 0; rowCount < this->rowCount; rowCount++)
	{
		for (int colCount = 0; colCount < this->colCount; colCount++)
		{
			result.matrix[rowCount][colCount] =  (*iterLRow)[colCount] - (*iterRRow)[colCount] ;
		}
		iterRRow++;
		iterLRow++;
	}

	return result;
}


Matrix& Matrix::operator=(const Matrix &mat)
{
	this->rowCount = mat.rowCount;
	this->colCount = mat.colCount;
	this->matrix = mat.matrix;

	return *this;
}

//************************************************************
Matrix::~Matrix()
{}





//************************************************************
ostream & operator<<(ostream & os, const Matrix & matrix)
{
	cout << "========== Display the Matrix ==========" << endl;
	for (auto &row : matrix.matrix)
	{
		cout << fixed << setprecision(3);
		os << "|";
		for (auto &element : row)
		{
			os << left << setw(Matrix::MARGINE_SIZE) << element;
		}
		os << "|"<< endl;
	}

	return os;
}


vector<float>& Matrix::operator[](int index)
{
	return this->matrix[index];
}


//需要修改
Matrix& Matrix::transpose()
{

	Matrix transposeMatrix;
	transposeMatrix.setMatrixSize(this->colCount,this->rowCount);

	for(int rowIndex = 0; rowIndex < this->rowCount; rowIndex++)
	{
		for(int colIndex = 0; colIndex < this->colCount; colIndex++)
		{
			transposeMatrix[colIndex][rowIndex] = this->matrix[rowIndex][colIndex];
		}

	}
	this->setMatrix(transposeMatrix.matrix);

	return *this;
}


/**
 * @brief : 
 * 		set the matrix's size
 * 
 * @param rowCount : 
 * 		representing the matrix 's row number
 * @param colCount :
 * 		representing the matrix 's col number
 */
void Matrix::setMatrixSize(int rowCount, int colCount)
{
	this->rowCount = rowCount;
	this->colCount = colCount;
	
	this->matrix.resize(this->rowCount);
	for(auto &row : this->matrix)
	{
		row.resize(this->colCount);
	}
	
}

void Matrix::setMatrix(vector<vector<float> > matrix)
{
	this->matrix = matrix;
	this->rowCount = this->matrix.size();
	this->colCount = this->matrix[0].size();
}


vector<float> Matrix::getVector()
{
	if(this->colCount == 1)
	{
		transpose();
	}
	return this->matrix[0];
}



int Matrix::getRowCount()
{
	return this->rowCount;
}

int Matrix::getColCount()
{
	return this->colCount;
}

// Correspond Multiplication for Vector and Vector
Matrix Matrix::corresＭutiVV(Matrix vec1, Matrix vec2)
{
	vector<float> outVec;
	int colCount;

	if(vec1.getColCount() == 1)
		vec1.transpose();
	if(vec2.getColCount() == 1)
		vec2.transpose();
	
	colCount = vec1.getColCount();
	
	for(int index = 0 ; index < colCount; index++)
	{
		outVec.push_back(vec1[0][index] * vec2[0][index]);
	}
	

	return Matrix(vector<vector<float> > {outVec});
}


Matrix operator-(int number, Matrix &vecMat)
{
	vector<float> vecToBeMinused;
	vector<float> resultVec;
	Matrix resultMat;
	
	// Initialize the two vector
	vecToBeMinused = vecMat.getVector();
	resultVec.resize(vecToBeMinused.size());

	// Minus the vector
	for(int index = 0; index < (int)vecToBeMinused.size(); index++)
	{
		resultVec[index] = number - vecToBeMinused[index];
	}

	// Use the result vector to set the result matrix
	resultMat.setMatrix(vector<vector<float> >{resultVec});
	
	return resultMat;
}



// For vector addition
vector<float> Matrix::addVector(vector<float> v1, vector<float> v2)
{
	vector<float> outputVec;


	if(v1.size() != v2.size())
		throw "The two vectors cannot be added!!";

	for(auto index = 0; index < (int)v1.size(); index++)
	{
		outputVec.push_back(v1[index]  + v2[index]);
	}

	return outputVec;
}

// For vector multiplication
vector<float> Matrix::multiplyVector(vector<float> vec, float scale)
{
	vector<float> outputVec;

	for(auto &element: vec)
	{
		outputVec.push_back(element * scale);
	}

	return outputVec;
}


// For linear combination
vector<float> Matrix::LinearCombiVectorMatrix(vector<float> vec,const Matrix& mat)
{

	vector<float> outputVec(mat.colCount);

	for(auto index = 0; index < (int)vec.size(); index++ )
	{
		outputVec = addVector(outputVec ,multiplyVector(mat.matrix[index], vec[index]));
	}

	return outputVec;
}


void Matrix::displayMatrixSize()
{
	cout << "Matrix size: " << 
		 this->rowCount << " * " << this->colCount << endl;
	cout << "Actually matrix size: "
		 << this->matrix.size() << " * " << this->matrix[0].size() << endl;
}




vector<vector<float> >& Matrix::getMatrixValue()
{
	return this->matrix;
}
