#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix
{
	private:
		vector< vector<float> > matrix;          //CALC & OUT  - All the transactions from the csv file
		int rowCount;
		int colCount;
	public:
		Matrix();  
		Matrix(int rowCount, int colCount);
		Matrix(vector< vector<float> > matrix);


		Matrix operator*(Matrix &rightMatrix);
		Matrix operator*(float scaler);
		friend Matrix operator*(float scaler, Matrix mat);
		Matrix operator+(Matrix &rightMatrix);
		Matrix& operator=(const Matrix &mat);

		friend ostream& operator<<(ostream& os,const Matrix &matrix);

		Matrix transpose();
		void setMatrixSize(int rowCount, int colCount);
		
		//these are the function which helping us to do the multiplication of matrix
		static vector<float> addVector(vector<float>, vector<float>);
		static vector<float> multiplyVector(vector<float>, float);
		static vector<float> LinearCombiVectorMatrix(vector<float>,const Matrix&);


		~Matrix();
};