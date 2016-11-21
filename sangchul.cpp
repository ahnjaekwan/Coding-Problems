#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double growth_rate(double birthrate, double deathrate)
{
	return birthrate - deathrate;
}

int det_population(int population, double rate, int years)
{
	return population * pow(1 + rate, years);
}

double enviro_population(int population, double rate, int years)
{
	double result = 1;
	for (int i = 0; i<years; i++)
	{
		double e = 1 - 2 * ((double)rand() / (RAND_MAX));
		result = result * (1 + rate - e);
	}
	return result * population;

}

double extinction_probability(int population, double rate, int years)
{
	double count = 0;
	for (int i = 0; i < 800; i++)
	{
		double pop = enviro_population(population, rate, years);
		if (pop <= 0)
			count++;
	}
	return count/800;
}
int main()
{
	cout << "Initial Population = ";
	int int_population;
	cin >> int_population;

	cout << "Birth Rate = ";
	double birthrate;
	cin >> birthrate;

	cout << "Death Rate = ";
	double deathrate;
	cin >> deathrate;

	cout << "Years = ";
	int years;
	cin >> years;
	double rate = growth_rate(birthrate, deathrate);
	cout << "Deterministic: " << det_population(int_population, rate, years) << endl;
	cout << "Environmental: " << enviro_population(int_population, rate, years) << endl;
	cout << "extinction prob; " << extinction_probability(int_population, rate, years) << endl;
	return 0;


}