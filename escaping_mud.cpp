#include <iostream>
#include <fstream>
using namespace std;

class escape
{
public:
	escape() : fout("output.txt"), fin("input.txt") //use fstream in constructor so that I can read and write from input file and to output file
	{
		int inputLine;
		char num[10];
		fin.getline(num, 10);
		inputLine = atoi(num); //get the line number
		line = inputLine;

		matrix = new int*[line]; //create matrix line by line
		for (int i = 0; i < line; i++)
			matrix[i] = new int[line];
		
		visited = new bool*[line]; //create bool matrix which shows whether each location has been visited or not
		for (int i = 0; i < line; i++)
			visited[i] = new bool[line];

		for (int i = 0; i < line; i++)
		{
			fin.getline(num, line + 1);
			for (int j = 0; j < line; j++)
			{
				matrix[i][j] = num[j] - '0'; //stores input in matrix
				visited[i][j] = false; //initiate each cell as false which means "not visited"
			}
		}
		

		matrixInit = new int*[line]; //duplicate the matrix
		for (int i = 0; i < line; i++)
			matrixInit[i] = new int[line];

		for (int i = 0; i < line; i++) //make a copy of initial matrix and visited so that we can initialize later
			for (int j = 0; j < line; j++)
			{
				matrixInit[i][j] = matrix[i][j];
			}
		
		cumulatedDirt1 = 0; //starting point always has dirt 0
		cumulatedDirt2 = 0; //make three of these for three different algorithms
		cumulatedDirt3 = 0;
	}

	~escape() //destructor closes fstream
	{
		fin.close();
		fout.close();
	}

	void initialization() //initialize matrix back to given condition
	{
		for (int i = 0; i < line; i++)
			for (int j = 0; j < line; j++)
			{
				matrix[i][j] = matrixInit[i][j];
				visited[i][j] = false;
			}
		return;
	}

	int compare() //it compares all three algorithms and if they all exceed 100, them let's just say minimum is 100
	{
		visited[line - 1][0] = true; //set the starting point as visited status
		int a1 = algorithm1(line - 1, 0);

		initialization(); //need to initialize matrix and visited back to given status
		visited[0][line - 1] = true; //this time, starting point is upside down
		int a2 = algorithm2(0, line - 1);

		initialization();
		visited[line - 1][0] = true; //set the starting point as visited status
		int a3 = algorithm3(line - 1, 0);

		int minimumDirt = 100;

		if (minimumDirt > a1)
			minimumDirt = a1;
		if (minimumDirt > a2)
			minimumDirt = a2;
		if (minimumDirt > a3)
			minimumDirt = a3;

		return minimumDirt;
	}

	void print() //it writes the result into output file
	{
		fout << compare();
		return;
	}

	int algorithm1(int y, int x) //this algorithms is that from starting point to ending point, make a move to other cell with lowest dirt number
	{		
		if (visited[0][line - 1] == true || cumulatedDirt1 >= 100) //stopping condition
			//if it reaches the end, or its cumulative Dirt exceeds 100, then just return cumulative Dirt
			return cumulatedDirt1;
		
		int compareNum = 10; //make a variable to compare which cell has the smallest; set it as bigger than any other possible number
		char option = 'x';
		//below if statements are in order of preference which means if dirt numbers are same, it prefers to make a move in order of (up, right, left, down)
		if (y - 1 >= 0 && visited[y - 1][x] == false && compareNum > matrix[y - 1][x]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y - 1][x];
			option = 'a';
		}
		if (x + 1 < line && visited[y][x + 1] == false && compareNum > matrix[y][x + 1]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y][x + 1];
			option = 'b';
		}
		if (x - 1 >= 0 && visited[y][x - 1] == false && compareNum > matrix[y][x - 1]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y][x - 1];
			option = 'c';
		}
		if (y + 1 < line && visited[y + 1][x] == false && compareNum > matrix[y + 1][x]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y + 1][x];
			option = 'd';
		}

		if (option == 'x') //in case of nowhere to go anymore: "algorithm fails"
			return 100;

		cumulatedDirt1 += compareNum; //update cumulatedDirt

		if (option == 'a') //update the current x or y value
			y--;
		else if (option == 'b')
			x++;
		else if (option == 'c')
			x--;
		else if (option == 'd')
			y++;

		visited[y][x] = true; //update the current cell visited status
		
		algorithm1(y, x); //call function itself(recursion)

		return cumulatedDirt1;
	}

	int algorithm2(int y, int x) //this algorithm is basically same as algorithm1
		//however, in this algorithm, goes backward from ending point in same movement algorithm
	{
		if (visited[line - 1 ][0] == true || cumulatedDirt2 >= 100) //stopping condition
																   //if it reaches the starting point, or its cumulative Dirt exceeds 100, then just return cumulative Dirt
			return cumulatedDirt2;

		int compareNum = 10; //make a variable to compare which cell has the smallest; set it as bigger than any other possible number
		char option = 'x';
		//below if statements are in order of preference which means if dirt numbers are same
		//this time, preference is upside down (down, left, right, up)
		if (y + 1 < line && visited[y + 1][x] == false && compareNum > matrix[y + 1][x]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y + 1][x];
			option = 'a';
		}
		if (x - 1 >= 0 && visited[y][x - 1] == false && compareNum > matrix[y][x - 1]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y][x - 1];
			option = 'b';
		}
		if (x + 1 < line && visited[y][x + 1] == false && compareNum > matrix[y][x + 1]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y][x + 1];
			option = 'c';
		}
		if (y - 1 >= 0 && visited[y - 1][x] == false && compareNum > matrix[y - 1][x]) //if possilbe to move and if dirt number is comparably small enough
		{
			compareNum = matrix[y - 1][x];
			option = 'd';
		}
		
		if (option == 'x') //in case of nowhere to go anymore: "algorithm fails"
			return 100;

		cumulatedDirt2 += compareNum; //update cumulatedDirt

		if (option == 'a')
			y++;
		else if (option == 'b')
			x--;
		else if (option == 'c')
			x++;
		else if (option == 'd') //update the current x or y value
			y--;
	
		visited[y][x] = true; //update the current cell visited status

		algorithm2(y, x); //call function itself(recursion)

		return cumulatedDirt2;
	}

	int algorithm3(int y, int x) //Important: little bit complicated
		//this algorithms is making a move to other cell with lowest dirt number sum of dirt itself, dirt located above and dirt located right
		//if any of three cell is already visited, then omit it
	{
		if (visited[0][line - 1] == true || cumulatedDirt3 >= 100) //stopping condition
																   //if it reaches the end, or its cumulative Dirt exceeds 100, then just return cumulative Dirt
			return cumulatedDirt3;

		int compareNum = 30; //make a variable to compare which cell has the smallest; set it as bigger than any other possible sum of three cell
		int dirtNum = 10;
		char option = 'x';
		//below if statements are in order of preference (up, right, left, down)
		if (y - 1 >= 0 && visited[y - 1][x] == false) //if possible to move up
		{
			if (y - 2 >= 0 && x + 1 < line) //if move up, then its up and right cell is also able to be visited
			{
				if (compareNum > matrix[y - 1][x] + matrix[y - 2][x] + matrix[y - 1][x + 1]) //if its sum is comparably small enough
				{
					compareNum = matrix[y - 1][x] + matrix[y - 2][x] + matrix[y - 1][x + 1];
					dirtNum = matrix[y - 1][x];
					option = 'a';
				}
			}
			else if (y - 2 >= 0) //if move up, then only its up cell is able to be visited
			{
				if (compareNum > matrix[y - 1][x] + matrix[y - 2][x]) //if its sum is comparably small enough
				{
					compareNum = matrix[y - 1][x] + matrix[y - 2][x];
					dirtNum = matrix[y - 1][x];
					option = 'a';
				}
			}
			else if (x + 1 < line) //if move up, then only its right cell is able to be visited
			{
				if (compareNum > matrix[y - 1][x] + matrix[y - 1][x + 1]) //if its sum is comparably small enough
				{
					compareNum = matrix[y - 1][x] + matrix[y - 1][x + 1];
					dirtNum = matrix[y - 1][x];
					option = 'a';
				}
			}
			else if (compareNum > matrix[y - 1][x]) //if move up, both its right cell is not able to be visited and if its sum is comparably small enough
			{
				compareNum = matrix[y - 1][x];
				dirtNum = matrix[y - 1][x];
				option = 'a';
			}
		}
		if (x + 1 < line && visited[y][x + 1] == false) //if possilbe to move right
		{
			if (y - 1 >= 0 && x + 2 < line) //if move right, then its up and right cell is also able to be visited
			{
				if (compareNum > matrix[y][x + 1] + matrix[y - 1][x + 1] + matrix[y][x + 2]) //if its sum is comparably small enough
				{
					compareNum = matrix[y][x + 1] + matrix[y - 1][x + 1] + matrix[y][x + 2];
					dirtNum = matrix[y][x + 1];
					option = 'b';
				}
			}
			else if (y - 1 >= 0) //if move right, then only its up cell is able to be visited
			{
				if (compareNum > matrix[y][x + 1] + matrix[y - 1][x + 1]) //if its sum is comparably small enough
				{
					compareNum = matrix[y][x + 1] + matrix[y - 1][x + 1];
					dirtNum = matrix[y][x + 1];
					option = 'b';
				}
			}
			else if (x + 2 < line) //if move right, then only its right cell is able to be visited
			{
				if (compareNum > matrix[y][x + 1] + matrix[y][x + 2]) //if its sum is comparably small enough
				{
					compareNum = matrix[y][x + 1] + matrix[y][x + 2];
					dirtNum = matrix[y][x + 1];
					option = 'b';
				}
			}
			else if (compareNum > matrix[y][x + 1]) //if move right, both its right cell is not able to be visited and if its sum is comparably small enough
			{
				compareNum = matrix[y][x + 1];
				dirtNum = matrix[y][x + 1];
				option = 'b';
			}
		}
		if (x - 1 >= 0 && visited[y][x - 1] == false) //if possilbe to move left
		{
			if (y - 1 >= 0) //since it comes from right to left, then its right cell is previously visited thus if its up cell is able to be visited
			{
				if (compareNum > matrix[y][x - 1] + matrix[y - 1][x - 1]) //if its sum is comparably small enough
				{
					compareNum = matrix[y][x - 1];
					dirtNum = matrix[y][x - 1];
					option = 'c';
				}
			}
			else if (compareNum > matrix[y][x - 1]) //else, but if its sum is comparably small enough
			{
				compareNum = matrix[y][x - 1];
				dirtNum = matrix[y][x - 1];
				option = 'c';
			}
		}
		if (y + 1 < line && visited[y + 1][x] == false) //if possilbe to move down
		{
			if (x + 1 < line) //since it comes from up to down, then its up cell is previously visited thus if its right cell is able to be visited
			{
				if (compareNum > matrix[y + 1][x] + matrix[y + 1][x + 1]) //if its sum is comparably small enough
				{
					compareNum = matrix[y + 1][x] + matrix[y + 1][x + 1];
					dirtNum = matrix[y + 1][x];
					option = 'd';
				}
			}
			else if (compareNum > matrix[y + 1][x]) //else but if its sum is comparably small enough
			{
				compareNum = matrix[y + 1][x];
				dirtNum = matrix[y + 1][x];
				option = 'd';
			}
		}

		if (option == 'x') //in case of nowhere to go anymore: "algorithm fails"
			return 100;

		cumulatedDirt3 += dirtNum; //update cumulatedDirt

		if (option == 'a') //update the current x or y value
			y--;
		else if (option == 'b')
			x++;
		else if (option == 'c')
			x--;
		else if (option == 'd')
			y++;

		visited[y][x] = true; //update the current cell visited status

		algorithm3(y, x); //call function itself(recursion)

		return cumulatedDirt3;
	}

private:
	ifstream fin;
	ofstream fout;
	int **matrix;
	bool **visited;
	int **matrixInit;
	bool **visitedInit;
	int line;
	int cumulatedDirt1;
	int cumulatedDirt2;
	int cumulatedDirt3;
};

int main()
{
	escape solve; //create class
	solve.print(); //print it on output file (execute compare() function)
	//in compare() function, execute algorithm1, algorithm2, and algorithm3 and then compare!
	return 0;
}