#include "BadChipSim.hpp"
#include "MonteCarloSim.hpp"
#include <iostream>
using namespace std;

int main() {

	BadChipSim sim1("t1.txt");
	BadChipSim sim2("t2.txt");
	BadChipSim sim3("t3.txt");
	BadChipSim sim4("t4.txt");

	cout << "Simulation 1: " << endl;
	sim1.getSpecs();
	sim1.generateDatasets();
	sim1.runSimulation();

	cout << "Simulation 2: " << endl;
	sim2.getSpecs();
	sim2.generateDatasets();
	sim2.runSimulation();

	cout << "Simulation 3: " << endl;
	sim3.getSpecs();
	sim3.generateDatasets();
	sim3.runSimulation();

	cout << "Simulation 4: " << endl;
	sim4.getSpecs();
	sim4.generateDatasets();
	sim4.runSimulation();	

	cout << "Monte Carlo Simulation" << endl;
	MonteCarloSim mcSim("readings.txt");
	mcSim.readInputs();
	mcSim.runMCSimulation();

	return 0;
}
