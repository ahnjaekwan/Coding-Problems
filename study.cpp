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
		int num, k;
		cin >> num;
		cin >> k;
		int *arr = new int[num];

		for (int i = 0; i < num; i++)
		{
			int value;
			cin >> value;
			arr[i] = value;
		}
		qsort(arr, num, sizeof(int), compare);

		int sum = 0;
		for (int i = 0; i < k; i++)
			sum += arr[num - 1 - i];

		cout << "Case #" << test_case << endl;
		cout << sum << endl;
	}

	return 0;
}