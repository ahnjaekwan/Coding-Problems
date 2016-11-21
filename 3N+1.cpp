#include <iostream>
#include <vector>
using namespace std;

int function(int x)
{
	int count=0;
	while (x != 1)
	{
		if (x % 2 == 0)
			x /= 2;
		else
			x = 3 * x + 1;
		count++;
	}
	return count;
}

bool check(vector<bool> v)
{
	bool complete = true;
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		if (v[i] == false)
		{
			complete = false;
			break;
		}
	}
	return complete;
}

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++)
	{
		
		int num;
		cin >> num;

		//create array
		unsigned long long *arr = new unsigned long long[100000000];
		arr[0] = 1;
		int index = 1;

		for (int i = 0; i < num; i++)
		{
			//update
			int increment = 0;
			for (int j = 0; j < index; j++)
			{
				if ((arr[j] - 1) % 3 == 0 && arr[j] != 1 && arr[j] != 4)
				{
					//add new number 
					arr[index + increment] = (arr[j] - 1) / 3;
					arr[j] *= 2;
					increment++;
				}
				else
					arr[j] *= 2;
			}
			index += increment;
		}

		unsigned long long minNum = 1000000, maxNum = 1;
		for (int i = 0; i < index; i++)
		{
			//find min and max and update them
			if (arr[i] > maxNum)
				maxNum = arr[i];
			if (arr[i] < minNum)
				minNum = arr[i];
			
		}

		cout << "Case #" << test_case << endl;
		cout << minNum << " " << maxNum << endl;
		delete[] arr;
		

		/*
		int num;
		cin >> num;

		//find min
		vector<int> v1(64);
		vector<bool> v2(64, false);
		int startNum = 1;
		while (!check(v2))
		{
			int index = function(startNum);
			if (v2[index] == false)
			{
				v1[index] = startNum;
				v2[index] = true;
			}
			startNum++;
		}

		unsigned long long maxNum = 1;
		for (int i = 0; i < num; i++)
			maxNum *= 2;

		cout << "Case #" << test_case << endl;
		cout << v1[num] << " " << maxNum << endl;
		*/
	}

	return 0;
}