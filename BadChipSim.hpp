#ifndef BADCHIPSIM_HPP
#define BADCHIPSIM_HPP

#include <iostream>
using namespace std;

class BadChipSim {

	private:
		string filename;
		int numBatches;
		int numItemsInBatch;
		int pctBadBatches;
		int pctBadItemsInBadBatch;
		int numItemsToSample;
		int badBatchesCreated;
		int badBatchesFound;
	
	public:
		BadChipSim(string filename);
		void getSpecs();
		void generateDatasets();
		void runSimulation();
		void outputSimResults();
};
#endif
