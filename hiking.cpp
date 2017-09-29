#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std; 

int find_max(int **map, int n) {
	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] > max)
				max = map[i][j];
		}
	}
	return max;
}

int solve_without_k(int **map, bool **visited, int n, int x, int y, int length) {
	int max = length; 
	bool **new_visited;
	new_visited = new bool*[n];
	for (int i = 0; i < n; i++) {
		new_visited[i] = new bool[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			new_visited[i][j] = visited[i][j];
		}
	}
	new_visited[x][y] = true;
	if (x + 1 < n && new_visited[x+1][y] == false) {
		if (map[x][y] > map[x + 1][y]) {
			int sol = solve_without_k(map, new_visited, n, x + 1, y, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	if (x - 1 >= 0 && new_visited[x - 1][y] == false) {
		if (map[x][y] > map[x - 1][y]) {
			int sol = solve_without_k(map, new_visited, n, x - 1, y, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	if (y + 1 < n && new_visited[x][y + 1] == false) {
		if (map[x][y] > map[x][y + 1]) {
			int sol = solve_without_k(map, new_visited, n, x, y + 1, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	if (y - 1 >= 0 && new_visited[x][y - 1] == false) {
		if (map[x][y] > map[x][y - 1]) {
			int sol = solve_without_k(map, new_visited, n, x, y - 1, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	return max;
}

int solve(int **map, bool **visited, int n, int k, int x, int y, int length) {
	int max = length;
	bool **new_visited;
	new_visited = new bool*[n];
	for (int i = 0; i < n; i++) {
		new_visited[i] = new bool[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			new_visited[i][j] = visited[i][j];
		}
	}
	new_visited[x][y] = true;
	//update visited
	if (x + 1 < n && new_visited[x + 1][y] == false) {
		if (map[x][y] > map[x + 1][y]) {
			int sol = solve(map, new_visited, n, k, x + 1, y, length + 1);
			if (max < sol)
				max = sol;
		}
		else if (map[x][y] > map[x + 1][y] - k) {//make a new map
			int **new_map; 
			new_map = new int*[n];
			for (int i = 0; i < n; i++) {
				new_map[i] = new int[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					new_map[i][j] = map[i][j];
				}
			}
			new_map[x + 1][y] = map[x][y] - 1;
			int sol = solve_without_k(new_map, new_visited, n, x + 1, y, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	if (x - 1 >= 0 && new_visited[x - 1][y] == false) {
		if (map[x][y] > map[x - 1][y]) {
			int sol = solve(map, new_visited, n, k, x - 1, y, length + 1);
			if (max < sol)
				max = sol;
		}
		else if (map[x][y] > map[x - 1][y] - k) {//make a new map
			int **new_map;
			new_map = new int*[n];
			for (int i = 0; i < n; i++) {
				new_map[i] = new int[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					new_map[i][j] = map[i][j];
				}
			}
			new_map[x - 1][y] = map[x][y] - 1;
			int sol = solve_without_k(new_map, new_visited, n, x - 1, y, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	if (y + 1 < n && new_visited[x][y + 1] == false) {
		if (map[x][y] > map[x][y + 1]) {
			int sol = solve(map, new_visited, n, k, x, y + 1, length + 1);
			if (max < sol)
				max = sol;
		}
		else if (map[x][y] > map[x][y + 1] - k) {//make a new map
			int **new_map;
			new_map = new int*[n];
			for (int i = 0; i < n; i++) {
				new_map[i] = new int[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					new_map[i][j] = map[i][j];
				}
			}
			new_map[x][y + 1] = map[x][y] - 1;
			int sol = solve_without_k(new_map, new_visited, n, x, y + 1, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	if (y - 1 >= 0 && new_visited[x][y - 1] == false) {
		if (map[x][y] > map[x][y - 1]) {
			int sol = solve(map, new_visited, n, k, x, y - 1, length + 1);
			if (max < sol)
				max = sol;
		}
		else if (map[x][y] > map[x][y - 1] - k) {//make a new map
			int **new_map;
			new_map = new int*[n];
			for (int i = 0; i < n; i++) {
				new_map[i] = new int[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					new_map[i][j] = map[i][j];
				}
			}
			new_map[x][y - 1] = map[x][y] - 1;
			int sol = solve_without_k(new_map, new_visited, n, x, y - 1, length + 1);
			if (max < sol)
				max = sol;
		}
	}
	return max;
}

int main(int argc, char** argv) {
	int test_case;
	ifstream inputfile("sample_input.txt");
	ofstream outputfile("output.txt");
	if (inputfile.is_open()) {
		inputfile >> test_case;
	}

	///////////////////////////START
	for(int testnum = 1; testnum <= test_case; testnum++) {
		int solution = 0;
		if (inputfile.is_open()) { //read input
			int n, k;
			int **map;
			bool **visited;
			inputfile >> n >> k;
			map = new int*[n];
			for (int i = 0; i < n; i++) {
				map[i] = new int[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					inputfile >> map[i][j];
				}
			}
			visited = new bool*[n];
			for (int i = 0; i < n; i++) {
				visited[i] = new bool[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					visited[i][j] = false;
				}
			}

			int highest = find_max(map, n); //func
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (map[i][j] == highest) {
						int path = solve(map, visited, n, k, i, j, 1); //func
						if (solution < path)
							solution = path;
					}
				}
			}

			for (int i = 0; i < n; i++) { //free memory
				delete[] map[i];
			}
			delete map;
		}

		if (outputfile.is_open()) { //output answer
			outputfile << "#" << testnum << " " << solution << "\n";
		}
	}

	////////////////////////////END
	if (inputfile.is_open()) {
		inputfile.close();
	}
	if (outputfile.is_open()) {
		outputfile.close();
	}
	return 0;
}