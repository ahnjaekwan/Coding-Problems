#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

int calculate(queue<int> q, int c) {
	if (c == 0 || q.empty())
		return 0;
	int front = q.front();
	q.pop();

	if (front > c) {
		return calculate(q, c);
	}
	else {
		int	sum1 = front*front + calculate(q, c - front);
		int sum2 = calculate(q, c);
		if (sum1 > sum2)
			return sum1;
		else
			return sum2;
	}
}

int solve(int** board, int n, int m, int c) {
	queue<int> q1, q2;
	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j + m <= n; j++) {
			//reset queue
			while (!q1.empty()) {
				q1.pop();
			}
			//update queue
			for (int c = 0; c < m; c++) {
				q1.push(board[i][j + c]);
			}
			//all possible cases for next person
			for (int k = i; k < n; k++) {
				//for (int l = j + m ; l + m <= n; l++) {
				for (int l = 0; l + m <= n; l++) {
					if (k == i && l < j + m)
						continue;
					//reset array
					while (!q2.empty()) {
						q2.pop();
					}
					//update vector
					for (int c = 0; c < m; c++) {
						q2.push(board[k][l +c]);
					}
					int solution1 = calculate(q1, c);
					int solution2 = calculate(q2, c);
					int solution = solution1 + solution2;
					if (solution > max)
						max = solution;
				}
			}
		}
	}
	return max;
}
int main(int argc, char** argv) {
	int test_case;
	ifstream inputfile("sample_input.txt");
	ofstream outputfile("output.txt");

	inputfile >> test_case;
	int testnum;
	for (testnum = 1; testnum <= test_case; testnum++) {
		//get input values
		int n, m, c;
		inputfile >> n >> m >> c;
		int** board;
		board = new int*[n];
		for (int i = 0; i < n; i++) {
			board[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				inputfile >> board[i][j];
			}
		}

		//solve
		int solution = solve(board, n, m, c);

		//free memory
		for (int i = 0; i < n; i++) {
			delete board[i];
		}
		delete board;

		//write
		outputfile << "#" << testnum << " " << solution << "\n";
	}

	//close
	if (inputfile.is_open()) {
		inputfile.close();
	}
	if (outputfile.is_open()) {
		outputfile.close();
	}
	return 0;
}