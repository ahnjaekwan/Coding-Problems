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
		int *arr = new int[num];

		for (int i = 0; i < num; i++)
		{
			int value;
			cin >> value;
			arr[i] = value;
		}
		int k;
		cin >> k;

		int jump = 0;
		int position = 0;
		for (int i = 0; i < num; i++)
		{
			if (arr[i] > position + k)
			{
				jump = -1;
				break;
			}
			while (position + k >= arr[i + 1])
			{
				i++;
				if (i + 1 == num)
					break;
			}
			position = arr[i];
			jump++;
		}

		cout << "Case #" << test_case << endl;
		cout << jump << endl;
	}

	return 0;
}