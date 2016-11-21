#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++) {
		double A, B, C, D, E;
		int num;
		cin >> A >> B >> C >> D >> E;
		cin >> num;
		int total = 0;
		for (int i = 0; i < num; i++)
		{
			double x, y;
			cin >> x >> y;
			double dis = sqrt(pow(x, 2) + pow(y, 2));

			double deg;
			if (x == 0 && y >= 0)
				deg = PI / 2;
			else if (x == 0 && y < 0)
				deg = 3 * PI / 2;
			else if (x > 0 && y >= 0)
				deg = atan(y/x);
			else if (x > 0 && y < 0)
				deg = 2*PI - atan(y/x);
			else if (x < 0 && y >= 0)
				deg = PI - atan(y/x);
			else if (x < 0 && y < 0)
				deg = PI + atan(y/x);

			int point;
			if (deg < PI / 20)
				point = 6;
			else if (deg < PI / 20 + PI / 10 * 1)
				point = 13;
			else if (deg < PI / 20 + PI / 10 * 2)
				point = 4;
			else if (deg < PI / 20 + PI / 10 * 3)
				point = 18;
			else if (deg < PI / 20 + PI / 10 * 4)
				point = 1;
			else if (deg < PI / 20 + PI / 10 * 5)
				point = 20;
			else if (deg < PI / 20 + PI / 10 * 6)
				point = 5;
			else if (deg < PI / 20 + PI / 10 * 7)
				point = 12;
			else if (deg < PI / 20 + PI / 10 * 8)
				point = 9;
			else if (deg < PI / 20 + PI / 10 * 9)
				point = 14;
			else if (deg < PI / 20 + PI / 10 * 10)
				point = 11;
			else if (deg < PI / 20 + PI / 10 * 11)
				point = 8;
			else if (deg < PI / 20 + PI / 10 * 12)
				point = 16;
			else if (deg < PI / 20 + PI / 10 * 13)
				point = 7;
			else if (deg < PI / 20 + PI / 10 * 14)
				point = 19;
			else if (deg < PI / 20 + PI / 10 * 15)
				point = 3;
			else if (deg < PI / 20 + PI / 10 * 16)
				point = 17;
			else if (deg < PI / 20 + PI / 10 * 17)
				point = 2;
			else if (deg < PI / 20 + PI / 10 * 18)
				point = 15;
			else if (deg < PI / 20 + PI / 10 * 19)
				point = 10;
			else
				point = 6;

			if (dis < A)
				total += 50;
			else if (dis < B)
				total += point;
			else if (dis < C)
				total += point * 3;
			else if (dis < D)
				total += point;
			else if (dis < E)
				total += point * 2;
			else;
		}

		cout << "Case #" << test_case << endl;
		cout << total << endl;
	}

	return 0;
}