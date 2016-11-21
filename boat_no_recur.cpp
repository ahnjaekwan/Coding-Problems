#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool function(vector<char> start, vector<char> goal)
{
	stack<vector<char>> s;
	//bool found = false;
	vector<vector<char>> visited;
	s.push(start);
	visited.push_back(start);
	while (!s.empty())
	{
		vector<char> current = s.top();
		s.pop();
		if (current == goal)
			return true;
		
		char pos = current[0];
		for (int i = 0; i < 4; i++)
		{
			if (pos == current[i])
			{
				if (i == 0)
				{
					vector<char> changed = current;
					if (changed[0] == 'e')
						changed[0] = 'w';
					else
						changed[0] = 'e';

					if (changed[1] == changed[2] && changed[0] != changed[1])
						continue;
					else if (changed[2] == changed[3] && changed[0] != changed[2])
						continue;
					else if (find(visited.begin(), visited.end(), changed) != visited.end())
						continue;
					else
					{
						s.push(changed);
						visited.push_back(changed);
					}
				}
				else
				{
					vector<char> changed = current;
					if (changed[0] == 'e')
					{
						changed[0] = 'w';
						changed[i] = 'w';
					}
					else
					{
						changed[0] = 'e';
						changed[i] = 'e';
					}

					if (changed[1] == changed[2] && changed[0] != changed[1])
						continue;
					else if (changed[2] == changed[3] && changed[0] != changed[2])
						continue;
					else if (find(visited.begin(), visited.end(), changed) != visited.end())
						continue;
					else
					{
						s.push(changed);
						visited.push_back(changed);
					}
				}
			}
		}

	}
	return false;
}
int main(int argc, char** argv) {
	vector<char> start(4, 'e');
	//start[0] = 'w';
	//start[1] = 'w';
	//start[2] = 'w';
	//start[3] = 'w';
	vector<char> goal(4, 'w');
	if (function(start, goal))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}