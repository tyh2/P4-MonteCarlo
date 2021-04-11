#ifndef MONTECARLOSIM_HPP
#define MONTECARLOSIM_HPP
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MonteCarloSim {

	private:
		string inputFile;
		int numDays;
		int numCategories;
		string units;
		vector<int> categoryLow;
		vector<int> categoryHigh;
		vector<int> categoryMeans;
		vector<int> frequencies;
		vector<double> occurenceProbabilities;
		vector<double> cumulativeProbabilities;
		vector<int> simResults;

	public:
		MonteCarloSim(string filename);
		void readInputs();
		void runMCSimulation();
		double getAnalyticalModel();
		double getSimulationModel();
		void outputSimResults();


};
#endif
