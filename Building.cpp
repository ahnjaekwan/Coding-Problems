
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Board
{
public:
	int totalFloor(char **board, int num);
	int numFloor(int i, int j, char **board, int num);
	int numHeight(char **board, int num, int height);
	void transform(char **board, char **numBoard, int num);
};

int Board::numFloor(int i, int j, char **board, int num)
{
	int count = 1;
	if (board[i - 2][j] == 'P' || board[i - 2][j] == 'P' || board[i - 2][j] == 'P' || board[i - 2][j] == 'P')
		return count;
	for (int k = 2; board[i - k][j] == 'B'; k+=2)
		count++;
	for (int k = 2; board[i + k][j] == 'B'; k+=2)
		count++;
	for (int k = 2; board[i][j - k] == 'B'; k+=2)
		count++;
	for (int k = 2; board[i][j + k] == 'B'; k+=2)
		count++;
	return count;
}

int Board::totalFloor(char **board, int num)
{
	int totalNum = 0;
	for (int i = 0; i < num; i+=2)
		for (int j=0; j < num; j+=2)
			if (board[i][j] == 'B')
				totalNum += numFloor(i, j, board, num);
	return totalNum;
}

int Board::numHeight(char **board, int num, int height)
{
	int count = 0;
	for (int i = 0; i < num; i+=2)
		for (int j = 0; j < num; j+=2)
			if (board[i][j] == 'B')
				if (numFloor(i, j, board, num) >= height)
					count++;
	return count;
}

void Board::transform(char **board, char **numBoard, int num)
{
	for (int i = 0; i < num; i += 2)
		for (int j = 0; j < num; j += 2)
		{
			if (board[i][j] == 'P')
				numBoard[i][j] = '0';
			else
			{
				int a = '0' + numFloor(i, j, board, num);
				numBoard[i][j] = (char)a;
			}
		}
}


int main(void)
{
	ofstream fout("output.txt");
	ifstream fin("input.txt");
	Board board;
	char **BuildingBoard = NULL;
	char **NumberBoard = NULL;
	string str;
	int totalNum, num, height, i, j;
	getline(fin, str);
	int testNum = atoi(str.c_str());
	for (i = 0; i < testNum; i++)
	{
		cout << "#" << i + 1 << endl << "Plan" << endl;
		getline(fin, str);
		int startIndex = 0;
		string condition[2];
		for (i = 0; i < 2; i++)
		{
			int fIndex = str.find(" ", startIndex);
			condition[i] = str.substr(startIndex, fIndex - startIndex);
			startIndex = fIndex + 1;
		}
		num = atoi(condition[0].c_str());
		height = atoi(condition[1].c_str());
		BuildingBoard = new char*[num];
		for (i = 0; i < num; i++)
			BuildingBoard[i] = new char[num];
		for (i = 0; i < num; i++)
		{
			getline(fin, str);
			cout << str << endl;
			for (j = 0; j < num; j++)
			{
				BuildingBoard[i] = str.c_str();
				//NumberBoard[i] = str.c
				int fIndex = str.find(" ", startIndex);
				string temp;
				temp = str.substr(startIndex, fIndex - startIndex);
				BuildingBoard[i][j] = temp.c_str();
				startIndex = fIndex + 1;
			}
		}

		cout << endl << "Building Height(Floor)" << endl;
		cout << "" <<endl;
		cout << endl << "Total sum of floors of all buildings : " << board.totalFloor(BuildingBoard, num) << endl;
		cout << "Number of buildings with higher than " << height << "th floor : " << board.numHeight(BuildingBoard, num, height) << endl;
		fout << "#" << i+1 << " " << board.totalFloor(BuildingBoard, num) << " " << board.numHeight(BuildingBoard, num, height) << endl;
	}
	string cutStr[3];
	char *cutChar[3];
	int num, size[3];
	int pt[3][8] = { 0, }, ptx, pty;
	int i = 0, j, k;
	int remainder;
	getline(fin, str);
	testNum = atoi(str.c_str());
	for (k = 0; k < testNum; k++)
	{
		getline(fin, str);
		num = atoi(str.c_str());
		getline(fin, str);
		BombBoard = new char*[num];
		for (i = 0; i < num; i++)
			BombBoard[i] = new char[num];
		int startIndex = 0;
		for (i = 0; i < 3; i++)
		{
			int fIndex = str.find(",", startIndex);
			cutStr[i] = str.substr(startIndex, fIndex - startIndex);
			startIndex = fIndex + 1;
		}
		for (i = 0; i < 3; i++)
			size[i] = cutStr[i].length();
		for (i = 0; i < 3; i++)
			cutChar[i] = (char*)cutStr[i].c_str();

	}

}