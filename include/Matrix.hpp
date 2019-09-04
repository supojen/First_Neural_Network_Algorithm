#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <exception>
using namespace std;

class Matrix
{
	private:
		static const int MARGINE_SIZE = 15;      // Const       - This variable is for printing the matrix, representing that we have the maximam 10 digits
		vector< vector<float> > matrix;          // CALC & OUT  - All the transactions from the csv file
		int rowCount;
		int colCount;
	public:
		Matrix();  
		Matrix(int rowCount, int colCount);
		Matrix(vector< vector<float> > matrix);

		// About matrix multiply matrix
		Matrix operator*(Matrix &rightMatrix);


		Matrix operator*(float scaler);
		friend Matrix operator*(float scaler, Matrix mat);
		Matrix operator+(Matrix &rightMatrix);
		Matrix operator-(Matrix &rightMatrix);
		Matrix& operator=(const Matrix &mat);
		vector<float>& operator[](int);



		friend ostream& operator<<(ostream& os,const Matrix &matrix);

		Matrix& transpose();

		// The following two function is for helping updating the weight of feed forward AI
		static Matrix corresＭutiVV(Matrix vec1, Matrix vec2); 
		friend Matrix operator-(int number, Matrix &vecMat);

		void setMatrixSize(int rowCount, int colCount);
		void setMatrix(vector<vector<float> >);

		vector<float> getVector();
		int getRowCount();
		int getColCount();
		vector<vector<float> >& getMatrixValue();
		
		
		//these are the function which helping us to do the multiplication of matrix
		static vector<float> addVector(vector<float>, vector<float>);
		static vector<float> multiplyVector(vector<float>, float);
		static vector<float> LinearCombiVectorMatrix(vector<float>,const Matrix&);

		//for testing
		void displayMatrixSize();

		~Matrix();
};