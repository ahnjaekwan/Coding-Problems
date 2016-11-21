
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream fout("output.txt");
	ifstream fin("input.txt");
	
	int line;
	fin >> line; //get a line number from input text
	char ch[2];
	fin.getline(ch, 2); //get rid of '\0' character after line input
	
	/*
		Or we can do in another way of getting a line number from input text:
		int line;
		char lineCh[4];
		fin.getline(lineCh, 4);
		line = atoi(lineCh);
	*/

	char **seat; //make a matrix composed of line by line characters
	seat = new char*[line];
	for (int i = 0; i < line; i++)
		seat[i] = new char[line];

	int count = 0;
	for (int i = 0; i < line; i++)
	{
		fin.getline(seat[i], line + 1); //store each line into 'seat' matrix
		for (int j = 0; j < line - 1; j++) //count all the available couple set of seats
		{
			if (seat[i][j] == '.' && seat[i][j + 1] == '.')
				count++;
		}
	}
	fout << count;

	fin.close();
	fout.close();
	return 0;
}
