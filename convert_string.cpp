#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int conversion(char c) //make a function gives the order number of each character
{
	if (c == 'J')
		return 1;
	if (c == 'E')
		return 2;
	if (c == 'N')
		return 3;
	if (c == 'I')
		return 4;
	if (c == 'F')
		return 5;
	if (c == 'R')
		return 6;
	if (c == 'S')
		return 7;
	if (c == 'O')
		return 8;
	if (c == 'T')
		return 9;
	return 0;
}

int main()
{
	ofstream fout("output.txt");
	ifstream fin("input.txt");

	char answer[12] = { 'J','E','N','N','I','F','E','R','S','O','F','T' }; //make a char array of answer
	int totalNum = 0;
	vector<char> jennifer;
	char c;
	while(fin.get(c))
		jennifer.push_back(c);
	
	//find matched characters and put them in vector 'match'
	vector<char> match;
	for (int i = 0; i < jennifer.size(); i++)
	{
		if (jennifer[i] == 'J' || jennifer[i] == 'E' || jennifer[i] == 'N' || jennifer[i] == 'I'
			|| jennifer[i] == 'F' || jennifer[i] == 'R' || jennifer[i] == 'S' || jennifer[i] == 'O'
			|| jennifer[i] == 'T')
			match.push_back(jennifer[i]);
	}
	
	////////////////////////////////////////////////////////////////////
	//find max order number
	
	int maxCount = 0;
	vector<char> maxOrder;
	/*
	maxOrder.push_back('I');
	maxOrder.push_back('R');
	maxOrder.push_back('S');
	maxOrder.push_back('O');
	maxOrder.push_back('F');
	maxOrder.push_back('T');
	*/
	
	for (int i = 0; i < match.size() - 1; i++)
	{
		int count = 0;
		vector<char> temp;
		temp.push_back(match[i]);
		int prevTemp = i;
		for (int j = i+1; j < match.size(); j++)
		{
			if (conversion(match[prevTemp]) < conversion(match[j]))
			{
				count++;
				temp.push_back(match[j]);
				prevTemp = j;
			}
			else if (match[prevTemp] == 'N' && match[j] == 'N')
			{
				count++;
				temp.push_back(match[j]);
				prevTemp = j;
			}
			else if (match[j] == 'F' && match[prevTemp] != 'T')
			{
				count++;
				temp.push_back(match[j]);
				prevTemp = j;
			}
			else if (match[j] == 'E' && conversion(match[prevTemp]) < 6)
			{
				count++;
				temp.push_back(match[j]);
				prevTemp = j;
			}
		}
		if (count > maxCount)
		{
			maxCount = count;
			//save maxOrder
			maxOrder = temp;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////

	//change one char according to the function above: max number of continuously ordered characters	
	int prevPosInAns = 0;
	int prevPosInJen = 0;
	int posInAns;
	int startPos = 0;
	for (posInAns = startPos; posInAns < 12; posInAns++) //for each character from maxOrder, figure out which position it matches with the answer 
	{
		if (maxOrder[startPos] == answer[posInAns])
			break;
	}

	int posInJen;
	for (posInJen = startPos; posInJen < jennifer.size(); posInJen++) //for each character from maxOrder, figure out which position it matches with the given string
	{
		if (maxOrder[startPos] == jennifer[posInJen])
			break;
	}

	int termInAns = posInAns - prevPosInAns; //comparing two characters, count how many characters should be placed in order to be completed
	int termInJen = posInJen - prevPosInJen; //comparing two characters, count how many characters are available to be changed
	while (termInJen > 0 && termInAns > 0) //until both two above conditions are still satisfied
	{
		//change char
		jennifer[prevPosInJen] = answer[prevPosInAns];
		//update maxOrder
		maxOrder.push_back(maxOrder.back()); //push back a new vector
		for (int j = maxOrder.size() - 1; j > startPos; j--)
		{
			maxOrder[j] = maxOrder[j - 1]; //from the end, copy previous character and paste back to next position until it reaches position of missing character
		}
		maxOrder[startPos] = answer[prevPosInAns];

		totalNum++; //count
		startPos++; //update all variables
		prevPosInJen++;
		prevPosInAns++;
		termInJen--;
		termInAns--;
	}
	prevPosInAns = posInAns; //update previous positions in both vectors
	prevPosInJen = posInJen;
	
	for (; startPos < maxOrder.size(); startPos++)
	{
		for (posInAns = prevPosInAns + 1; posInAns < 12; posInAns++) //for each character from maxOrder, figure out which position it matches with the answer 
		{
			if (maxOrder[startPos] == answer[posInAns])
				break;
		}

		int posInJen;
		for (posInJen = prevPosInAns + 1; posInJen < jennifer.size(); posInJen++) //for each character from maxOrder, figure out which position it matches with the given string
		{
			if (maxOrder[startPos] == jennifer[posInJen])
				break;
		}

		int termInAns = posInAns - prevPosInAns; //comparing two characters, count how many characters should be placed in order to be completed
		int termInJen = posInJen - prevPosInJen; //comparing two characters, count how many characters are available to be changed
		while (termInJen > 1 && termInAns > 1) //until both two above conditions are still satisfied
		{
			//change char
			jennifer[prevPosInJen+1] = answer[prevPosInAns+1];
			//update maxOrder
			maxOrder.push_back(maxOrder.back()); //push back a new vector
			for (int j = maxOrder.size() - 1; j > startPos; j--)
			{
				maxOrder[j] = maxOrder[j - 1]; //from the end, copy previous character and paste back to next position until it reaches position of missing character
			}
			maxOrder[startPos] = answer[prevPosInAns];

			
			totalNum++; //count
			startPos++; //update all variables
			prevPosInJen++; 
			prevPosInAns++;
			termInJen--;
			termInAns--;
		}
		prevPosInAns = posInAns; //update previous positions in both vectors
		prevPosInJen = posInJen;
	}

	//delete one char
	//right now, maxOrder is a group of characters which are actually used in order
	//make jennifer to maxOrder
	for (int i = 0; i < jennifer.size() - 1; i++)
	{
		if (jennifer[i] != maxOrder[i]) //if detect any character to be deleted,
		{			
			for (int j = i; j < jennifer.size() - 1; j++)
			{
				jennifer[j] = jennifer[j+1]; //from that position, copy next character and paste back to current position until it reaches the end
			}
			jennifer.pop_back(); //then pop the last vector content
			totalNum++; //count
		}
	}
	
	
	//insert characters in right order
	for (int i = 0; i < 12; i++)
	{
		if (jennifer[i] != answer[i]) //if detect any character is missing
		{
			jennifer.push_back(jennifer.back()); //push back a new vector
			for (int j = jennifer.size() - 1; j > i; j--)
			{
				jennifer[j] = jennifer[j-1]; //from the end, copy previous character and paste back to next position until it reaches position of missing character
			}
			jennifer[i] = answer[i]; //put correct character in right position
			totalNum++; //count
		}
	}
	
	fout << totalNum; //write ouput
	fin.close();
	fout.close();
	return 0;
}
