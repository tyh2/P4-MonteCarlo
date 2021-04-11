#include "BadChipSim.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

BadChipSim::BadChipSim(string filename)
{
	this->filename = filename;
}

void BadChipSim::getSpecs()
{
	ifstream in;
	in.open(filename);
	if(in.is_open()) {
		in >> numBatches;
		in >> numItemsInBatch;
		in >> pctBadBatches;
		in >> pctBadItemsInBadBatch;
		in >> numItemsToSample;
	}

	cout << "\tNumber of batches of items: " << numBatches << endl;
	cout << "\tNumber of items in each batch: " << numItemsInBatch << endl;
	cout << "\tPercentage of batches containing bad items: " << pctBadBatches << "%" << endl;
	cout << "\tPercentage of bad items in a bad batch: " << pctBadItemsInBadBatch << "%" << endl;
	cout << "\tNumber of items sampled from each set: " << numItemsToSample << endl << endl;
}

void BadChipSim::generateDatasets()
{
	int count = 100 / pctBadBatches;
	ofstream out;
	string file;
	badBatchesCreated = 0;

	cout << "\tGenerating Datasets..." << endl;

	for(int i = 1; i <= numBatches; i++) {
		
		stringstream ss;
		ss << "ds" << i << ".txt";
		file = ss.str();
		out.open(file);

		if(i % count == 0) {
			badBatchesCreated++;

			for(int j = 0; j < numItemsInBatch; j++) {
				int r = rand()%100;
				if(r < pctBadItemsInBadBatch) {
					out << "b\n";
				}
				else {
					out << "g\n";
				}
			}
		}
		else {
			for(int j = 0; j < numItemsInBatch; j++) {
				out << "g\n";
			}
		}
		
		out.close();	
	}
	cout << "\tNumber of bad batches created: " << badBatchesCreated << endl << endl;	
}

void BadChipSim::runSimulation()
{
	ifstream in;
	string file;
	char chipStatus;
	badBatchesFound = 0;
	int iter = numItemsInBatch / numItemsToSample;

	cout << "\tAnalyzing Datasets..." << endl;

	for(int i = 1; i <= numBatches; i++) {
		
		stringstream ss;
		ss << "ds" << i << ".txt";
		file = ss.str();
		in.open(file);
		
		for(int j = 0; j < numItemsInBatch; j++) {
			
			in >> chipStatus;
			
			if(j % iter == 0) {
				if(chipStatus == 'b') {
					badBatchesFound++;
					break;
				}
			}
		}

		in.close();
	}

	cout << "\tNumber of bad batches found: " << badBatchesFound << endl << endl;

	outputSimResults();
}	

void BadChipSim::outputSimResults()
{
	cout << "\tBase = " << ((100 - pctBadItemsInBadBatch)/static_cast<double>(100)) << endl;
	cout << "\tExponent = " << numItemsToSample << endl;
	cout << "\tP(failure to detect bad batch) = " << pow(((100 - pctBadItemsInBadBatch)/static_cast<double>(100)), numItemsToSample) << endl;
	cout << "\tPercentage of bad batches actually detected = " << (static_cast<double>(badBatchesFound)/badBatchesCreated)*100 << "%" << endl << endl;
}



