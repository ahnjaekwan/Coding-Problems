#include <iostream>
using namespace std;

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++)
	{
		int num;
		cin >> num;

		int minNum;

		for (minNum = 2;minNum < num - 1; minNum++)
		{
			int count = 0;
			int a = 1;
			int b = num;
			for (; a <= num; count++)
				a *= minNum;

			int *arr = new int[count];
			for (int i = 0;; i++)
			{
				a /= minNum;
				if (a == 1)
				{
					arr[i] = b;
					break;
				}
				else if (b >= a)
				{
						arr[i] = (b - (b%a)) / a;
						b %= a;
				}
				else
					arr[i] = 0;
			}

			bool check = true;
			for (int i = 0; i < count - 1; i++)
			{
				if (arr[i] != arr[i + 1])
				{
					check = false;
					break;
				}
			}

			if (check)
				break;
		}

		cout << "Case #" << test_case << endl;
		cout << minNum << endl;
	}

	return 0;
}