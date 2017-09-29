
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool check(int** map, int n, int len, int startX, int startY) {
	if (startX + len > n || startY + len > n)
		return false;
	int x = startX + 1;
	int y = startY;
	//create array
	int arr[40];
	for (int i = 0; i < len - 2; i++) {
		//reset array
		for (int j = 0; j < 40; j++)
			arr[j] = 0;
		int index = 0;
		//put all elements composed of rectangle into array
		while (x > startX) {
			arr[index] = map[y][x];
			index++; x--; y++;
		}
		while (y < startY + len - 1) {
			arr[index] = map[y][x];
			index++; x++; y++;
		}
		while (x < startX + len - 1) {
			arr[index] = map[y][x];
			index++; x++; y--;
		}
		while (y > startY) {
			arr[index] = map[y][x];
			index++; x--; y--;
		}
		//sort array
		sort(arr, arr + index);
		//check if there exists duplicate
		bool check = true;
		for (int j = 0; j < index - 1; j++) {
			if (arr[j] == arr[j + 1]) {
				check = false;
				break;
			}
		}
		if (check)
			return true;
		x++;
	}
	return false;
}

int main(int argc, char** argv) {
	int test_case;
	ifstream inputfile("sample_input.txt");
	ofstream outputfile("output.txt");

	inputfile >> test_case;
	int testnum;
	for (testnum = 1; testnum <= test_case; testnum++) {
		//get input values
		int n;
		inputfile >> n;
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
		int solution = -1;
		bool found = false;
		for (int len = n; len >= 3; len--) {
			//check(board, n, len, int startX, int startY)
			for (int startX = 0; startX + len <= n; startX++) {
				for (int startY = 0; startY + len <= n; startY++) {
					if (check(board, n, len, startX, startY)) {
						solution = (len - 1) * 2;
						found = true;
						break;
					}
				}
				if (found)
					break;
			}
			if (found)
				break;
		}
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