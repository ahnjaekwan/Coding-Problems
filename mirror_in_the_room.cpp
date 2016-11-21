#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {

	int TC;
	int test_case;
	cin >> TC;

	for (test_case = 1; test_case <= TC; test_case++)
	{
		int num;
		cin >> num;
		char ch[2];
		cin.getline(ch, 2);
		char **arr;
		arr = new char*[num];
		for (int i = 0; i < num; i++)
				arr[i] = new char[num];

		for (int i = 0; i < num; i++)
			cin.getline(arr[i], num + 1);

		bool **visited = new bool*[num];
		for (int i = 0; i < num; i++)
			visited[i] = new bool[num];
		for (int i = 0; i < num; i++)
			for (int j = 0; j < num; j++)
				visited[i][j] = false;

		int count = 0;
		int i = 0, j = 0;
		char dir = 'e';
		while (i >= 0 && i < num && j >= 0 && j < num)
		{
			if (arr[i][j] == '0')
			{
				if (dir == 'e')
					j++;
				else if (dir == 'w')
					j--;
				else if (dir == 's')
					i++;
				else if (dir == 'n')
					i--;
			}
			else if (arr[i][j] == '1')
			{
				if (visited[i][j] == false)
				{
					count++;
					visited[i][j] = true;
				}

				if (dir == 'e')
				{
					i--;
					dir = 'n';
				}				
				else if (dir == 'w')
				{
					i++;
					dir = 's';
				}
				else if (dir == 's')
				{
					j--;
					dir = 'w';
				}
				else if (dir == 'n')
				{
					j++;
					dir = 'e';
				}
			}
			else if (arr[i][j] == '2')
			{
				if (visited[i][j] == false)
				{
					count++;
					visited[i][j] = true;
				}

				if (dir == 'e')
				{
					i++;
					dir = 's';
				}
				else if (dir == 'w')
				{
					i--;
					dir = 'n';
				}
				else if (dir == 's')
				{
					j++;
					dir = 'e';
				}
				else if (dir == 'n')
				{
					j--;
					dir = 'w';
				}
			}
		}

		cout << "Case #" << test_case << endl;
		cout << count << endl;
	}

	return 0;
}