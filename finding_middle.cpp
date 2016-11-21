#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;
const double score_max = 100;
struct Info
{
	string name;
	double* coordinate;
	double importance;
	Info(string n, double* c, double i) : name(n), coordinate(c), importance(i) {}
};
struct Data
{
	string name;
	double distance, drink, meal, date, club, night;
	double* coordinate;
	Data(string n, double* c, double dr, double me, double da, double cl, double ni) 
		: name(n), coordinate(c), drink(dr), meal(me), date(da), club(cl), night(ni)
	{}
};

class find_place
{
public: 
	find_place() : fout("output.txt"), fin_data("data.txt"), fin_info("party.txt")
	{
		string name; double x, y, drink, meal, date, club, night, importance;
		while (fin_data >> name >> x >> y >> drink >> meal >> date >> club >> night)
		{
			double* coordinate = new double[2];
			coordinate[0] = x; coordinate[1] = y;
			data.push_back(Data(name, coordinate, drink, meal, date, club, night));
		}
		while (fin_info >> name >> x >> y >> importance)
		{
			double* coordinate = new double[2];
			coordinate[0] = x; coordinate[1] = y;
			party.push_back(Info(name, coordinate, importance));
		}
		location = new double[2];
		center_of_mass();
		put_dist();
	}

	~find_place()
	{
		fin_data.close();
		fin_info.close();
		fout.close();
	}

	void write_output()
	{
		fout << "RECOMMENDATION:\n";
		int num = data.size();
		for (int i = 0; i < num; i++)
		{
			fout << "#" << i + 1 << ":	" << data[i].name << endl;
		}
	}

	struct dist_order
	{
		inline bool operator() (const Data& data1, const Data& data2)
		{
			return (data1.distance < data2.distance);
		}
	};
	struct drink_order
	{
		inline bool operator() (const Data& data1, const Data& data2)
		{
			return ((data1.distance * (score_max - data1.drink)) < (data2.distance * (score_max - data2.drink)));
		}
	};
	struct meal_order
	{
		inline bool operator() (const Data& data1, const Data& data2)
		{
			return ((data1.distance * (score_max - data1.meal)) < (data2.distance * (score_max - data2.meal)));
		}
	};
	struct date_order
	{
		inline bool operator() (const Data& data1, const Data& data2)
		{
			return ((data1.distance * (score_max - data1.date)) < (data2.distance * (score_max - data2.date)));
		}
	};
	struct club_order
	{
		inline bool operator() (const Data& data1, const Data& data2)
		{
			return ((data1.distance * (score_max - data1.club)) < (data2.distance * (score_max - data2.club)));
		}
	};
	struct night_order
	{
		inline bool operator() (const Data& data1, const Data& data2)
		{
			return ((data1.distance * (score_max - data1.night)) < (data2.distance * (score_max - data2.night)));
		}
	};

	void center_of_mass()
	{
		int num_party = party.size();
		double xImportance = 0, yImportance = 0, sum_importance = 0;
		for (int i = 0; i < num_party; i++)
		{
			xImportance += party[i].coordinate[0] * party[i].importance;
			yImportance += party[i].coordinate[1] * party[i].importance;
			sum_importance += party[i].importance;
		}
		location[0] = xImportance / sum_importance;
		location[1] = yImportance / sum_importance;
	}

	double distance(double *first, double *second)
	{
		return sqrt(pow(abs(first[0] - second[0]), 2.0) + pow(abs(first[1] - second[1]), 2.0));
	}

	void put_dist()
	{
		int data_size = data.size();
		for (int i = 0; i < data_size; i++)
		{
			data[i].distance = distance(data[i].coordinate, location);
		}
	}

	void sort_by_dist()
	{
		sort(data.begin(), data.end(), dist_order());
	}
	void sort_by_drink()
	{
		sort(data.begin(), data.end(), drink_order());
	}
	void sort_by_meal()
	{
		sort(data.begin(), data.end(), meal_order());
	}
	void sort_by_date()
	{
		sort(data.begin(), data.end(), date_order());
	}
	void sort_by_club()
	{
		sort(data.begin(), data.end(), club_order());
	}
	void sort_by_night()
	{
		sort(data.begin(), data.end(), night_order());
	}

	void take_option(int option)
	{
		switch (option) {
		case 1: sort_by_drink();
			break;
		case 2: sort_by_meal();
			break;
		case 3: sort_by_date();
			break;
		case 4: sort_by_club();
			break;
		case 5: sort_by_night();
			break;
		case 6: sort_by_dist();
			break;
		default: break;
		}
	}
private:
	ifstream fin_data;
	ifstream fin_info;
	ofstream fout;
	double *location;
	vector<Info> party;
	vector<Data> data;
};


int main(int argc, char** argv) {
	cout << "Choose the purpose of meeting:\n" << "#1. Drink\n" << "#2. Meal\n"
		<< "#3. Date\n" << "#4. Club\n" << "#5. Overall Night Life\n" << "#6. Just find the mid-spot\n"
		<< "Your choie(enter only number of options above): ";
	int option;
	cin >> option;
	while (option > 6 || option < 0)
	{
		cout << "Please pick one of options above\n" << "Your choie(enter only number of options above): ";
		cin >> option;
	}
	find_place a;
	a.take_option(option);
	a.write_output();
	return 0;
}