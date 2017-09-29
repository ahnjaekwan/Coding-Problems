#include <iostream>
#include <fstream>
using namespace std;

bool check(int monthly[12]) {
	for (int i = 0; i < 12; i++) {
		if (monthly[i] != 0)
			return false;
	}
	return true;
}
int solve(int monthly[12], int day, int mon, int three, int year, int fare) {
	if (check(monthly))
		return fare;
	for (int i = 0; i < 12; i++) {
		if (monthly[i] != 0) {
			//three option
			//first daily payment
			int new_monthly1[12];
			for (int j = 0; j < 12; j++) {
				new_monthly1[j] = monthly[j];
			}
			new_monthly1[i] = 0;
			int howmuch1 = solve(new_monthly1, day, mon, three, year, fare + day*monthly[i]);
			//second monthly payment
			int howmuch2 = solve(new_monthly1, day, mon, three, year, fare + mon);
			//third three months payment
			int new_monthly2[12];
			for (int j = 0; j < 12; j++) {
				if (j == i || j == i + 1 || j == i + 2)
					new_monthly2[j] = 0;
				else
					new_monthly2[j] = monthly[j];
			}
			int howmuch3 = solve(new_monthly2, day, mon, three, year, fare + three);

			if (howmuch1 >= howmuch2) {
				if (howmuch2 >= howmuch3) {
					return howmuch3;
				}
				else {
					return howmuch2;
				}
			} else {
				if (howmuch1 >= howmuch3) {
					return howmuch3;
				}
				else {
					return howmuch1;
				}
			}
		}
	}
}

int main(int argc, char** argv) {
	int test_case;
	//ifstream inputfile("sample_input.txt");
	//ofstream outputfile("output.txt");

	/*if (inputfile.is_open()) {
		inputfile >> test_case;
	}*/
	cin >> test_case;

	for (int testnum = 1; testnum <= test_case; testnum++) {
		int day, mon, three, year;
		//inputfile >> day >> mon >> three >> year;
		cin >> day >> mon >> three >> year;
		int monthly[12];
		//inputfile >> monthly[0] >> monthly[1] >> monthly[2] >> monthly[3] >> monthly[4] >> monthly[5] >> monthly[6] >> monthly[7] >> monthly[8] >> monthly[9] >> monthly[10] >> monthly[11];
		cin >> monthly[0] >> monthly[1] >> monthly[2] >> monthly[3] >> monthly[4] >> monthly[5] >> monthly[6] >> monthly[7] >> monthly[8] >> monthly[9] >> monthly[10] >> monthly[11];
		int solution = year;

		int fare = solve(monthly, day, mon, three, year, 0);
		if (solution > fare)
			solution = fare;

		/*if (outputfile.is_open()) {
			outputfile << "#" << testnum << " " << solution << "\n";
		}*/
		cout << "#" << testnum << " " << solution << "\n";
	}

	//close
	/*if (inputfile.is_open()) {
		inputfile.close();
	}
	if (outputfile.is_open()) {
		outputfile.close();
	}*/
	return 0;
}