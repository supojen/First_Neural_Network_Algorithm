#include "Matrix.hpp"

//************************************************************
Matrix::Matrix()
{
	setMatrixSize(0,0);
}


//************************************************************
Matrix::Matrix(int rowCount, int colCount)
{
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
	auto iterRRow = this->matrix.begin();
	auto iterLRow = rightMatrix.matrix.begin();

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


Matrix& Matrix::operator=(const Matrix &mat)
{
	this->rowCount = mat.rowCount;
	this->colCount = mat.rowCount;
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
		os << left << setw(3) << "|";
		for (auto &element : row)
		{
			os << left << setw(3) << element;
		}
		os << "|"<< endl;
	}

	return os;
}

Matrix Matrix::transpose()
{
	vector<vector<float> > matrixHolder;
	matrixHolder.resize(this->colCount);
	for(auto &row : matrixHolder)
	{
		row.resize(this->rowCount);
	}


	for(int rowIndex = 0; rowIndex < this->rowCount; rowIndex++)
	{
		for(int colIndex = 0; colIndex < this->colCount; colIndex++)
		{
			matrixHolder[colIndex][rowIndex] = this->matrix[rowIndex][colIndex];
		}

	}

	*this = Matrix(matrixHolder);

	return *this;
}


void Matrix::setMatrixSize(int rowCount, int colCount)
{
	this->rowCount = rowCount;
	this->colCount = colCount;
	
	this->matrix.resize(this->colCount);
	for(auto &row : this->matrix)
	{
		row.resize(this->rowCount);
	}
	
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