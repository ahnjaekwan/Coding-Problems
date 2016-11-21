#include <iostream>
#include <fstream>
#include <cmath> //this is required to use 'sqrt' func
#include <vector>
using namespace std;

struct Point //this is a base unit which I am using with
{
	int x;
	int y;
	bool visited;
};

double calculate(int a, int b, int c, int d) //calculating distance between two points
{
	double sq1 = pow((double)(c - a), 2);
	double sq2 = pow((double)(d - b), 2);
	double dis = sqrt(sq1 + sq2);
	return dis;
}

class find_dis
{
public:
	find_dis() : fout("output.txt"), fin("input.txt") //use fstream in constructor so that I can read and write from input file and to output file
	{
		int number;
		char num[10];
		fin.getline(num, 10); //get the number of trash
		number = atoi(num);
		trashNum = number;

		for (int i = 0; i < number; i++)
		{
			fin.getline(num, 10); //get a location of trash
			char temp1[2];
			char temp2[2];
			int x, y;
			int j;
			for (j = 0; num[j] != ' '; j++) //extract number x of (x,y)
				temp1[j] = num[j];
			x = atoi(temp1); //make it integer
			for (int k = 0; num[j + k + 1] != '\0'; k++) //extract number y of (x,y)
				temp2[k] = num[j + k + 1];
			y = atoi(temp2); //make it integer
			initialize(x, y); //put the location of trash into initialize function
		}
	}

	~find_dis() //destructor closes fstream
	{
		fin.close();
		fout.close();
	}

	void addFront(int a, int b) //this function put a Point into beginningList
	{
		beginningList.push_back(Point());
		int pos = beginningList.size() - 1;
		beginningList[pos].x = a;
		beginningList[pos].y = b;
		beginningList[pos].visited = true; //it doesn't matter actually
		return;
	}

	void addBack(int a, int b) //this function put a Point into endingList
	{
		endingList.push_back(Point());
		int pos = endingList.size() - 1;
		endingList[pos].x = a;
		endingList[pos].y = b;
		endingList[pos].visited = true; //it doesn't matter actually
		return;
	}

	void initialize(int a, int b) //this function put new Point into pointList
	{
		pointList.push_back(Point());
		int pos = pointList.size() - 1;
		pointList[pos].x = a;
		pointList[pos].y = b;
		pointList[pos].visited = false; //this is important! Points are initially set 'visited' as false
		return;
	}

	int numVisited()
	{
		return beginningList.size() + endingList.size(); //this is used when to finish the recursion in minDistance function
	}

	void print() //it writes the result into output file
	{
		fout << "(0,0) -> ";
		for (int i = 0; i < beginningList.size(); i++)
			fout << "(" << beginningList[i].x << ", " << beginningList[i].y << ") -> ";
		for (int i = endingList.size() - 1; i >= 0; i--)
			fout << "(" << endingList[i].x << ", " << endingList[i].y << ") -> ";
		fout << "(10, 10)";
	}

	void minDistance(int a, int b, int c, int d) //find minimum distance from (0,0) to (10,10) by figuring out closet points from the start and the end. And use recursion using this algorithm
	{
		int baseCondition = trashNum - numVisited();

		if (baseCondition == 0) //stopping condition of recursion
			return;

		else if (baseCondition == 1) //in this case there is only one point left unvisited
		{
			int pos = 0;
			for (int i = 0; i < trashNum; i++) //find the unvisited point
				if (pointList[i].visited == false)
					pos = i;
			addFront(pointList[pos].x, pointList[pos].y); //put it in beginningList
			pointList[pos].visited = true; //mark it as visited

			return;
		}

		double minimum1=100; //just set it whatever you want but make sure that it is bigger than any possible distance
		int pos1 = 0;
		for (int i = 0; i < trashNum; i++)
		{
			if (pointList[i].visited == false) //skip the point already visited
			{
				double distance = calculate(a, b, pointList[i].x, pointList[i].y);
				if (minimum1 > distance) //get the nearest point from the point which is recently added in beginningList
				{
					minimum1 = distance;
					pos1 = i;
				}
			}
		}
		addFront(pointList[pos1].x, pointList[pos1].y); //put it in beginningList
		pointList[pos1].visited = true; //mark it as visited

		double minimum2=100; //same as above but find the nearest point from the point which is recently added in endingList
		int pos2 = 0;
		for (int i = 0; i < trashNum; i++)
		{
			if (pointList[i].visited == false)
			{
				double distance = calculate(c, d, pointList[i].x, pointList[i].y);
				if (minimum2 > distance)
				{
					minimum2 = distance;
					pos2 = i;
				}
			}
		}
		addBack(pointList[pos2].x, pointList[pos2].y);
		pointList[pos2].visited = true;

		minDistance(pointList[pos1].x, pointList[pos1].y, pointList[pos2].x, pointList[pos2].y); //by using recursion, find to shortest path from (0,0) to (10,10)

		return;
	}

private:
	vector<Point> beginningList;
	vector<Point> endingList;
	vector<Point> pointList;
	ifstream fin;
	ofstream fout;
	int trashNum;
};

int main()
{
	find_dis solve; //create class
	solve.minDistance(0, 0, 10, 10); //find the shorest path
	solve.print(); //print it on output file
	return 0;
}
