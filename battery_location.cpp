#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

float distance(Point p1, Point p2)
{
	return max(abs(p2.x - p1.x), abs(p2.y - p1.y));
}

struct Point
{
	Point(int a, int b)
	{
		x = a;
		y = b;
	}
	int x, y;
};

struct Line
{
	Line(int a, int b, int c, int d)
	{
		Point p1 = Point(a, b);
		Point p2 = Point(c, d);
	}
};

class max_dis
{
public:
	max_dis() : fout("output.txt"), fin("input.txt")
	{
		fin >> num;
		for (int i = 0; i < num; i++)
		{
			int x1, y1, x2, y2;
			fin >> x1 >> y1 >> x2 >> y2;
			LineList.push_back(Line(x1, y1, x2, y2));
			if()
		}
	}
	~max_dis()
	{
		fin.close();
		fout.close();
	}
	float find_max()
	{
		float maximum = 0;
		for (int i = 0; i < num; i++)
		{
			if (distanceList[i] > maximum)
				maximum = distanceList[i];
		}
		return maximum;
	}
	Point closest(int x, int y)
	{
		if (distance(l.p1, p) > distance(l.p2, p))
			return l.p1;
		else
			return l.p2;
	}
private:
	int num;
	ifstream fin;
	ofstream fout;
	vector<Line> LineList;
	vector<Point> PointList;
	vector<float> distanceList;
};

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++)
	{
		int num;
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
		}

		cout << "Case #" << test_case << endl;
		cout << minNum << endl;
	}

	return 0;
}