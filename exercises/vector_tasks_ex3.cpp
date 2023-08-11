#include <iostream>
#include <vector>
#include <algorithm>

using std::vector; 
using std::cerr; 
using std::cout; 
using std::endl; 
using std::min_element; 
using std::iter_swap; 
using std::sort; 

typedef vector<int>::iterator iter;
typedef vector<int>::const_iterator const_iter; 
//we assume that for all the tasks will work with integers

//return iterator of elem in vector or end iterator if the element is not in the vector
iter findElem(vector<int>& vec, int elem)
{
	iter it; 

	for (it = vec.begin(); it != vec.end(); ++it)
	{
		if (*it == elem)
		{
			break; 
		}
	}

	return it; 
}

//return a copy of the vector but with reversed elements
vector<int> reverse(const vector<int>& vec)
{
	vector<int> result; 
	result.resize(vec.size());
	vector<int>::const_reverse_iterator it;

	for (it = vec.crbegin(); it != vec.crend(); ++it)
	{
		result.push_back(*it); 
	}

	return result; 
}

//checks if every element from the second vector is in the first 
bool contains(vector<int> first, vector<int> second)
{
	const_iter it; 
	for (it = second.begin(); it != second.end(); ++it)
	{
		if (findElem(first, *it) == first.end())
		{
			return false; 
		}
	}
	return true;
}

int plusOne(int num)
{
	return num + 1; 
}
//map - applies a function to every element of vector (for unary operations) 
vector<int> map(const vector<int>& vec, int(*funcptr)(int))
{
	vector<int> result; 

	const_iter it; 
	for (it = vec.begin(); it != vec.end(); ++it)
	{
		result.push_back(funcptr(*it)); 
	}

	return result; 

}

bool isEven(int num)
{
	return num % 2 == 0;
}
//leaves only the elements with specific property
vector<int> filter(const vector<int>& vec, bool(*funcptr)(int))
{
	const_iter it; 
	vector<int> result; 
	for (it = vec.begin(); it != vec.end(); ++it)
	{
		if (funcptr(*it))
		{
			result.push_back(*it); 
		}
	}
	return result; 
}

//return iterator to the kth smallest element of vector where k is a number between 1 and n
//the space complexity should be O(n) and the time complexity should be O(n*k)
iter kthSmallest(vector<int>& vec, unsigned k)
{
	if (k == 0 || k > vec.size())
	{
		cerr << "Invalid kth element\n";
		//throw some exception in order not to crash
	}
	vector<int> helper = vec; 

	for (size_t i = 0; i < k; i++)
	{
		iter curr = helper.begin() + i; 
		iter minCurr = min_element(curr, helper.end()); 
		iter_swap(curr, minCurr); 
	}

	return findElem(vec, helper[k - 1]); 
}

//return a vector containting only the unique elements of the given vector
//the time complexity should be O(n*log(n))

vector<int> unique(vector<int> vec)
{

	vector<int> result; 
	sort(vec.begin(), vec.end()); //O(n*log(n))

	result.push_back(vec.front()); 
	size_t size = vec.size();
	for (size_t i = 1; i < size; i++)
	{
		if (vec[i] != vec[i - 1])
		{
			result.push_back(vec[i]); 
		}
	}
	return result;
}
void printVector(const std::vector<int>& vec)
{
	for (int elem : vec)
		std::cout << elem << " ";
}
int main()
{
	return 0; 
}
