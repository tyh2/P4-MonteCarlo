#include "MonteCarloSim.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

MonteCarloSim::MonteCarloSim(string filename)
{
	this->inputFile = filename;
}

void MonteCarloSim::readInputs()
{
	ifstream in;
	in.open(inputFile);

	in >> numDays;
	in >> numCategories;
	
	string str = "";
	getline(in, str);
	
	vector<string> tokens;
	tokens.resize(numCategories*3);
	for(int i = 0; i < numCategories; i++) {
		getline(in, str);
		stringstream ss(str);

		string temp;

		getline(ss, temp, '-');
		tokens.at(i*3) = temp;
		
		getline(ss, temp, ':');
		tokens.at(i*3 + 1) = temp;
		
		getline(ss, temp, ' ');
		getline(ss, temp);
		tokens.at(i*3 + 2) = temp;
	}

	getline(in, units);
	in.close();
	
	categoryLow.resize(numCategories);
	categoryHigh.resize(numCategories);
	categoryMeans.resize(numCategories);
	frequencies.resize(numCategories);
	for(int i = 0; i < numCategories; i++) {
		
		stringstream low(tokens.at(i*3));
		int l = 0;
		low >> l;
		categoryLow.at(i) = l;

		stringstream high(tokens.at(i*3 + 1));
		int h = 0;
		high >> h;
		categoryHigh.at(i) = h;
		categoryMeans.at(i) = (l + h)/2;

		stringstream freq(tokens.at(i*3 + 2));
		int f = 0;
		freq >> f;
		frequencies.at(i) = f;
	}
	
	occurenceProbabilities.resize(numCategories);
        cumulativeProbabilities.resize(numCategories);

        for(int i = 0; i < numCategories; i++) {
                occurenceProbabilities.at(i) = static_cast<double>(frequencies.at(i))/100;
        }

        cumulativeProbabilities.at(0) = occurenceProbabilities.at(0);

        for(int i = 1; i < numCategories; i++) {
                cumulativeProbabilities.at(i) = cumulativeProbabilities.at(i-1) + occurenceProbabilities.at(i);
        }
}

void MonteCarloSim::runMCSimulation()
{
	vector<int> randLow(numCategories);
	vector<int> randHigh(numCategories);

	randLow.at(0) = 0;
	randHigh.at(0) = static_cast<int>(cumulativeProbabilities.at(0) * 100) - 1;

	for(int i = 1; i < numCategories; i++) {
		
		randLow.at(i) = randHigh.at(i-1) + 1;
		randHigh.at(i) = static_cast<int>(cumulativeProbabilities.at(i) * 100) - 1;
	}

	simResults.resize(numDays);

	for(int i = 0; i < numDays; i++) {

		int r = rand() % 100;

		for(int j = 0; j < numCategories; j++) {
			if(r > randLow.at(j) && r <= randHigh.at(j)) {
				simResults.at(i) = j;
			}
			

		}
	}

	outputSimResults();
}

double MonteCarloSim::getAnalyticalModel()
{
	double model = 0.0;

	for(int i = 0; i < numCategories; i++) {
		model += (occurenceProbabilities.at(i) * categoryMeans.at(i));
	}
	
	return model;	
}

double MonteCarloSim::getSimulationModel()
{
	double model = 0.0;

	for(int i = 0; i < numDays; i++) {

		int index = simResults.at(i);
		model += categoryMeans.at(index);
	}

	model /= numDays;
	return model;
}

void MonteCarloSim::outputSimResults()
{
	cout << "Simulated days: " << numDays << endl;
	cout << "Number of categories: " << numCategories << endl;
	cout << "Ranges and occurences at each range: " << endl;
	
	for(int i = 0; i < numCategories; i++) {
		cout << "\t" << categoryLow.at(i) << "-" << categoryHigh.at(i) << ": " << frequencies.at(i) << endl;
	}

	cout << "Units of measure: " << units << endl;

	cout << "Analytical model: " << getAnalyticalModel();
	cout << "Simulation: " << getSimulationModel() << endl << endl;
}
