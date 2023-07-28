#include <iostream>
#include <vector>
#include <cmath>


//use only vectors if needed for tasks

using std::cin; 
using std::cout; 
using std::endl; 
using std::cerr; 
using std::vector; 

typedef vector<vector<int>> matrix; 

size_t matrixRows(matrix M)
{
	return M.size(); 
}

size_t matrixCols(matrix M)
{
	return M[0].size(); 
}


//find the sum of two matrices

matrix matrixSum(matrix M1, matrix M2)
{
	size_t rows = matrixRows(M1); 
	size_t cols = matrixCols(M1); 
	matrix result;

	if (rows != matrixRows(M2) || cols != matrixCols(M2))
	{
		cerr << "Incorrect dimensions" << endl; 
	}
	else
	{
		result.resize(rows);

		for (size_t i = 0; i < rows; i++)
		{
			result[i].resize(cols);

			for (size_t j = 0; j < cols; j++)
			{
				result[i][j] = M1[i][j] + M2[i][j];
			}
		}

		return result;
	}
}

//find the product of two matrices

matrix matrixMult(matrix M1, matrix M2)
{
	size_t colsM1 = matrixCols(M1); 
	size_t rowsM2 = matrixRows(M2); 

	if (colsM1 != rowsM2)
	{
		cerr << "Incorrect dimensions" << endl; 
	}
	else
	{
		//dimensions of resulting matrix -> nXm and mXp -> nXp 

		size_t rowsM1 = matrixRows(M1); 
		size_t colsM2 = matrixCols(M2);
		matrix result; 
		result.resize(rowsM1); 

		for (size_t i = 0; i < rowsM1; i++)
		{
			result[i].resize(colsM2);

			for (size_t j = 0; j < colsM2; j++)
			{
				result[i][j] = 0; 

				for (size_t k = 0; k < rowsM2; k++)
				{
					result[i][j] += M1[i][k] * M2[k][j]; 
				}
			}
		}

		return result; 
	}
}

//find the number of digits in a product of two numbers

int numOfDigitsProduct(int n1, int n2)
{
	if (n1 == 0 || n2 == 0)
	{
		return 1; 
	}
	return floor(log10(abs(n1)) + log10(abs(n2))) + 1; 

}

int main()
{
	/*
	matrix M1; 
	M1.resize(3);
	M1[0] = { 1,2,3 }; 
	M1[1] = {4, 5, 6}; 
	M1[2] = { 7, 8, 9 };

	
	matrix M2; 
	M2.resize(2); 
	M2[0] = { 1,2 };
	M2[1] = { 4, 5};
	matrix result = matrixMult(M1, M2); 

	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[0].size(); j++)
		{
			cout << result[i][j] << " "; 
		}
		cout << endl; 
	}
	*/

	return 0; 
}
