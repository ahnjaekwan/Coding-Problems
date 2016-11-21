#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool function(vector<char> start, vector<char> goal, vector<vector<char>> isVisited)
{
	if (find(isVisited.begin(), isVisited.end(), start) != isVisited.end())
		return false;
	else
		isVisited.push_back(start);

	if (start == goal)
		return true;
	else if (start[1] == start[2] && start[0] != start[1])
		return false;
	else if (start[2] == start[3] && start[0] != start[2])
		return false;
	else
	{
		stack<vector<char>> s;
		char pos = start[0];
		for (int i = 0; i < 4; i++)
		{
			if (pos == start[i])
			{
				if (i == 0)
				{
					vector<char> changed = start;
					if (start[0] == 'e')
						if (start[1] == start[2] && start[1] == 'e')
							if (start[2] == start[3] && start[2] == 'e')
								changed[0] = 'w';
					else
						if (start[1] == start[2] && start[1] == 'w')
							if (start[2] == start[3] && start[2] == 'w')
						changed[0] = 'e';
					s.push(changed);
				}
				else
				{
					vector<char> changed = start;
					if (start[0] == 'e')
					{
						changed[0] = 'w';
						changed[i] = 'w';
					}
					else
					{
						changed[0] = 'e';
						changed[i] = 'e';
					}
					s.push(changed);
				}
			}
		}
		vector<char> next = s.top();
		s.pop();
		while (!s.empty())
		{
			if (function(next, goal, isVisited))
				return true;
			next = s.top();
			s.pop();
		}
		return true;
	}
}
int main(int argc, char** argv) {
	vector<char> start(4, 'e');
	//start[0] = 'w';
	//start[1] = 'w';
	//start[2] = 'w';
	//start[3] = 'w';
	vector<char> goal(4, 'w');
	vector<vector<char>> isVisited;
	if (function(start, goal, isVisited))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}