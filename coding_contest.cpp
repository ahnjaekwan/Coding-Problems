#include <iostream>
#include <stdlib.h>     /* qsort */
using namespace std;

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++) {
		int num;
		cin >> num;
		int *arr = new int[num];

		for (int i = 0; i < num; i++)
		{
			int value;
			cin >> value;
			arr[i] = value;
		}
		qsort(arr, num, sizeof(int), compare);

		int count = 0;
		int max = 0;
		for (int i = 1; i <= num; i++)
		{
			arr[num - i] += i;
			if (arr[num - i] > max)
				max = arr[num - i];
			if (arr[num - i] - i + num >= max)
				count++;
		}

		cout << "Case #" << test_case << endl;
		cout << count << endl;
	}

	return 0;
}