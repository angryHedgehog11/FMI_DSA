#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define min(x, y) ((x) < (y)) ? (x) : (y) //също е взето от упражнения 

using std::vector; 
using std::string; 
using std::cin; 
using std::cout; 
using std::endl; 

const int MAX_CHARS = 93; //максималният брой символи, които можем да имаме са толкова на брой ( от 33-ти до 126-ти )

bool isSame(vector<char> colors, char color)
{
	vector<char>::iterator it = colors.begin(); 

	while (it != colors.end())
	{
		if (*it == color)
		{
			return true;
		}
		++it; 
	}

	return false;
}

int getColorIndex(vector<char> colors, char color)
{
	int index = -1;
	for (int i = 0; i < colors.size(); i++)
	{
		if (colors[i] == color)
		{
			index = i; 
			break;
		}
	}
	return index; 
}
//първоначално запълваме целия граф с 0 по главния диагонал и максимална стойност на другите места
void generateGraph(int graph[][MAX_CHARS])
{
	for (int i = 0; i < MAX_CHARS; i++)
	{
		for (int j = 0; j < MAX_CHARS; j++)
		{
			if (i == j)
			{
				graph[i][j] = 0; 
			}
			else
			{
				graph[i][j] = INT_MAX; 
			}
		}
	}
}
//приемаме, че първата буква е "from" и се задава от колоните, а втората е "to" и се задава от редовете
void putWeight(int graph[][MAX_CHARS], int index1, int index2, int weight)
{
	graph[index2][index1] = weight;
}

//алгоритъмът е взет от упражнения
void floyd(int graph[][MAX_CHARS], int size) 
{
	for (size_t k = 0; k < size; k++)
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++) 
			{ 
				if (i == j)
				{
					continue;
				}
				
				if (graph[i][k] == INT_MAX || graph[k][j] == INT_MAX)
				{
					continue;
				}
				
				int old = graph[i][j];
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
} 

int minPathIndex(int graph[][MAX_CHARS], int& allTime, char from, char to, vector<char> colors)
{
	int index1 = getColorIndex(colors, from);
	int index2 = getColorIndex(colors, to);

	int currMinIndex = -1, currMinTime = 0; 
	//цикълът служи за намиране на най-малката сума от времената на всеки ред от съответните колони 
	for (int i = 0; i < colors.size(); i++)
	{
		int temp = 0;

		if (graph[i][index1] != INT_MAX && graph[i][index2] != INT_MAX)
		{
			temp = graph[i][index1] + graph[i][index2];

			if (temp < INT_MAX && (temp <= currMinTime || currMinTime == 0))
			{
				if (currMinTime == temp)
				{
					currMinIndex = index2;
				}
				else
				{
					currMinTime = temp;
					currMinIndex = i;
				}
			}
		}
		
		temp = 0;
	}
	
	if (currMinTime != -1)
	{
		allTime += currMinTime;
	}
	return currMinIndex;
}

void result(string str1, string str2, vector<char> colors, int graph[][MAX_CHARS])
{
	bool canRecolor = true; 
	string result; 
	int allTime = 0; 
	result.resize(str1.size(), ' ');
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == str2[i])
		{
			result[i] = str1[i];
		}
		else
		{
			int index = minPathIndex(graph, allTime, str1[i], str2[i], colors);
			if (index == -1)
			{
				canRecolor = false; 
				break;
			}
			else
			{
				result[i] = colors[index];
			}
		}
	}
	if (canRecolor == true)
	{
		cout << allTime << endl;
		cout << result;
	}
	else
	{
		cout << "-1\n" << "Not possible!" << endl;
	}
}

int main()
{
	string necklace1, necklace2;
	int len, changes;
	//използваме този вектор за запзване на последователността на различни симовли (може да се замени и от статичен масив с макс дъжина 93
	vector<char> colors; 
	int graph[MAX_CHARS][MAX_CHARS];
	generateGraph(graph);

	string filename; 
	cin >> filename;
	std::fstream file(filename, std::ios::in);

	if (!file)
	{
		cout << "File could not open!" << endl; 
		return 1; 
	}

	file >> len; 
	file >> changes;

	necklace1.resize(len, ' ');
	necklace2.resize(len, ' '); 
	
	file >> necklace1; 
	file >> necklace2;
	char color1, color2; 
	int weight; 
	for (int i = 0; i < changes; i++)
	{
		file >> color1;
		if (!isSame(colors, color1))
		{
			colors.push_back(color1);
		}
		file >> color2;
		if (!isSame(colors, color2))
		{
			colors.push_back(color2);
		}
		file >> weight; 
		putWeight(graph, getColorIndex(colors, color1), getColorIndex(colors, color2), weight); //слагаме определената цена на определеното място
	}

	file.close();

	floyd(graph, colors.size());
	
	result(necklace1, necklace2, colors, graph);

	return 0;
}