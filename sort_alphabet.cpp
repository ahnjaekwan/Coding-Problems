
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	vector<int> count(26,0); //create a vector which stores number of each alphabet

	char c;
	int charNum;
	while (!fin.eof()) //using while loop, count how many times each alphabet has been appeard from input text
	{
		fin >> c;
		charNum = c - 'A';
		count[charNum]++;
	}
	count[charNum]--; //make sure that the last character is counted twice incorrectly
	
	vector<int> order; //this vector 'order' is going to represent characters in order of increasing number of uses

	for (int i = 0; i < count.size(); i++) //get rid of alphabets which are never used
	{
		if (count[i] != 0)
			order.push_back(i);
	}

	for (int i = 0; i < order.size(); i++) //in this double for loop, make alphabets in increasing counted number
		for (int j = i + 1; j < order.size(); j++)
		{
			if (count[order[i]] > count[order[j]])
			{
				int temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
			else if (count[order[i]] == count[order[j]]) //if two alphabets are used in same number, then make them in alphabetical order 
			{
				if (order[i] > order[j])
				{
					int temp = order[i];
					order[i] = order[j];
					order[j] = temp;
				}
			}
		}

	char b;
	for (int i = 0; i < order.size(); i++) //finally, put those ordered alphabets in output file
	{
		b = 'A' + order[i];
		for (int j = 0; j < count[order[i]]; j++)
			fout << b;
	}

	fin.close();
	fout.close();
	return 0;
}