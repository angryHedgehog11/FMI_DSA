#include <iostream>
#include <stack>
#include <string>

using std::string; 
using std::cout; 
using std::stack; 
using std::stoi; 

const char LEFTBRACKET = '(';
const char RIGHTBRACKET = ')';
const char LEFTCURLYBRACKET = '{';
const char RIGHTCURLYBRACKET = '}';
const char LEFTSQUAREBRACKET = '[';
const char RIGHTSQUAREBRACKET = ']';

bool isNum(char ch)
{
	return (ch >= '0' && ch <= '9');
}

bool isOp(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int calculateOp(char op, int left, int right)
{
	if (op == '+')
	{
		return left + right;
	}
	if (op == '-')
	{
		return left - right;
	}
	if (op == '*')
	{
		return left * right;
	}
	if (op == '/' && right != 0)
	{
		return left / right;
	}
	if (op == '^')
	{
		return pow(left, right);
	}
}

//reverse a string using stack
string reversed(const string& expr)
{
	stack<char> helper; 
	string result = "";
	size_t len = expr.length(); 
	for (size_t curr = 0; curr < len; curr++)
	{
		helper.push(expr.at(curr)); 
	}
	while (!helper.empty())
	{
		result += helper.top(); 
		helper.pop(); 
	}
	
	return result; 
}

//check if an expression has correct parentheses
bool checkBracketsMatch(const char left, const char right)
{
	return (left == LEFTBRACKET && right == RIGHTBRACKET) ||
		(left == LEFTCURLYBRACKET && right == RIGHTCURLYBRACKET) ||
		(left == LEFTSQUAREBRACKET && right == RIGHTSQUAREBRACKET);
}
bool correctPar(const string& expr)
{

	stack<char> bracketStack;
	size_t len = expr.length(); 
	for (size_t curr = 0; curr < len; curr++)
	{
		char current = expr[curr];

		if (current == LEFTBRACKET || current == LEFTCURLYBRACKET || current == LEFTSQUAREBRACKET)
		{
			bracketStack.push(current);
		}
		else if (current == RIGHTBRACKET || current == RIGHTCURLYBRACKET || current == RIGHTSQUAREBRACKET)
		{
			//if the stack is empty or there is a mismatch between types of brackets, it means that the expression is not correct 
			//in any other case the subexpression is correct so we pop the top element of the stack

			if (bracketStack.empty() || !checkBracketsMatch(bracketStack.top(), current))
			{
				return false;
			}

			bracketStack.pop();
		}
	}

	//if the stack is not empty it means that there were more left brackets than right brackets
	//it covers test cases like "(" or "(()"
	//if it is empty, it means that the expression is correct

	bool isCorrectExpr = bracketStack.empty();
	return isCorrectExpr;
}

//realize a simple postfix calculator(working only with one digit positive integers and operations + - * \ ^)
//we will do Dijkstra's two stack algorithm
//we will skip the validations for this function (for example we can not divide by zero and we should throw exception)
unsigned calculate(const string& expr)
{
	stack<unsigned> operands;

	size_t len = expr.length(); 

	for (size_t curr = 0; curr < len; curr++)
	{
		char current = expr[curr]; 
		if (isNum(current))
		{
			operands.push((current - '0'));
		}
		else if (isOp(current))
		{
			int right = operands.top();
			operands.pop();
			int left = operands.top();
			operands.pop();

			int result = calculateOp(current, left, right);

			operands.push(result);
		}
	}
	return operands.top();
}

//sort a stack using only stack for helper and the time and spaces complexity does not matter 

stack<int> sortStack(stack<int> st)
{
	stack<int> result;

	while (!st.empty())
	{
		int temp = st.top(); 
		st.pop(); 

		while (!result.empty() && result.top() > temp)
		{
			st.push(result.top()); 
			result.pop(); 
		}
		result.push(temp);
	}
	return result; 
}

int main()	
{
	return 0; 
}
