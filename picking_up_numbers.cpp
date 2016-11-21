#include <iostream>
using namespace std;

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++) {
		int num;
		cin >> num;
		int result = 0;
		for (int i = 0; i < num; i++)
		{
			int value;
			cin >> value;
			result ^= value;
		}
		cout << "Case #" << test_case << endl;
		cout << result << endl;
	}

	return 0;
}