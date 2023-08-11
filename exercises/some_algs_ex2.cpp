#include <iostream>
#include <vector>

using std::cout; 
using std::endl; 
using std::vector; 

//use only vectors if needed for tasks

//prime factors 
vector<int> primeFactors(int num)
{
	if (num <= 1)
	{
		return vector<int>(); 
	}

	vector<int> result;
	while (num % 2 == 0)
	{
		num = num / 2;
		result.push_back(2); 
	}

	for (size_t i = 3; i <= sqrt(num); i += 2)
	{
		while (num % i == 0)
		{
			num = num / i; 
			result.push_back(i);
		}
	}

	if (num > 2)
	{
		result.push_back(num); 
	}

	return result; 
}

//print vector 
void printVector(vector<int> vec)
{
	size_t size = vec.size(); 
	for (size_t curr = 0; curr < size; curr++)
	{
		cout << vec[curr] << " "; 
	}
}

//only for integers greater than 1
unsigned sumDigits(int num)
{
	if (num <= 1)
	{
		return 0; 
	}
	unsigned sum = 0;

	while (num != 0)
	{
		sum += num % 10;
		num = num / 10; 
	}

	return sum; 

}

unsigned sumOfDigitsOfVec(vector<int> vec)
{
	unsigned sum = 0;
	size_t size = vec.size();
	for (size_t curr = 0; curr < size; curr++)
	{
		sum += sumDigits(vec[curr]);
	}
	return sum;
}
//check if a number is Smiths number
// if the sum of the digits is equal with the sum of the prime factors 
bool isSmithNumber(int num)
{
	return (sumDigits(num) == sumOfDigitsOfVec(primeFactors(num)));
}

unsigned sumOfDivisors(int num)
{
	if (num < 1)
	{
		return 0; 
	}
	if (num == 1)
	{
		return 1; 
	}
	unsigned sum = 1; //every number is divisible by 1
	for (unsigned i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
		{
			sum += i; 
		}
	}

	return sum; 
}
//check if a number is perfect
//if the number is equal to the sum of its proper divisors
bool isPerfectNumber(int num)
{
	if (num < 1)
	{
		return false; 
	}

	return (sumOfDivisors(num) == num); 
}
int main()
{
	/*tests for primeFactors (function works for natural numbers greater than 1)
		
		printVector(primeFactors(5));
		printVector(primeFactors(1));
		printVector(primeFactors(12));
		printVector(primeFactors(25));
		printVector(primeFactors(1208));

	*/
	/*tests for Smith Number
		isSmithNumber(666); 
		isSmithNumber(3);
		isSmithNumber(134);
	*/
	/* tests for perfect numbers
		isPerfectNumber(14); 
		isPerfectNumber(496);
	*/
	return 0; 
}
