#include <iostream>
#include <fstream>
#include<unordered_map>
#include <string>
#include <vector>

using std::unordered_map; 
using std::string;
using std::vector; 
using std::cin; 
using std::cout; 
using std::endl; 

string getAminoAcid(string protein, unordered_map<string, char> aminoAcids)
{
	const size_t sizeOfCodon = 3;

	string result; 

	size_t size = protein.size();
	int j, k; 

	for (int i = 0; i < size; i+=sizeOfCodon)
	{
		string currCodon; 
		currCodon.resize(sizeOfCodon);
		j = i; 
		k = 0;

		while (k != sizeOfCodon)
		{
			currCodon[k++] = protein[j++];
		}

		result += aminoAcids[currCodon];
	}

	return result; 
}

int main()
{
	string DNA; 
	unordered_map<unsigned long, string> proteins;
	unordered_map<string, char> aminoAcids; 

	string nameOfFile; 

	cin >> nameOfFile; 
	std::fstream fileDNA(nameOfFile, std::ios::in);

	if (!fileDNA)
	{
		cout << "Could not open this file!" << endl; 
		return 1; 
	}

	fileDNA >> DNA;

	fileDNA.close();

	cin >> nameOfFile; 
	std::fstream fileProt(nameOfFile, std::ios::in);

	if (!fileProt)
	{
		cout << "Could not open file!" << endl;
		return 1; 
	}

	unsigned long ID;
	string protein;

	while (!fileProt.eof())
	{
		fileProt >> ID >> protein;
		proteins[ID] = protein;
	}
	
	fileProt.close(); 

	cin >> nameOfFile; 
	std::fstream fileAmino(nameOfFile, std::ios::in);
	if (!fileAmino)
	{
		cout << "Could not open file!" << endl; 
		return 1; 
	}

	string codon;
	char amino; 
	while (!fileAmino.eof())
	{
		fileAmino >> codon >> amino;
		aminoAcids[codon] = amino; 
	}

	fileAmino.close(); 

	unsigned numberOfRequests; 
	cin >> numberOfRequests;

	vector<unsigned long> proteinID; 
	proteinID.resize(numberOfRequests);

	for (unsigned i = 0; i < numberOfRequests; i++)
	{
		cin >> proteinID[i]; 
	}

	for (unsigned i = 0; i < numberOfRequests; i++)
	{
		if (proteins.find(proteinID[i]) != proteins.end())
		{
			const size_t NOT_A_POS = -1;

			size_t firstApp = DNA.find(proteins[proteinID[i]]);

			if (firstApp != NOT_A_POS)
			{
				cout << "Yes " << firstApp << " " << getAminoAcid(proteins[proteinID[i]], aminoAcids) << endl;

			}
			else
			{
				cout << "No" << endl; 
			}
		}
		else
		{
			cout << "No protein in proteins.txt with id " << proteinID[i] << endl; 
		}
	}

	return 0; 
}