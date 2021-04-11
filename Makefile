run : main.o BadChipSim.o MonteCarloSim.o
	g++ main.o BadChipSim.o MonteCarloSim.o -o run

main.o : main.cpp
	g++ -c main.cpp

BadChipSim.o : BadChipSim.hpp BadChipSim.cpp
	g++ -c BadChipSim.hpp BadChipSim.cpp

MonteCarloSim.o : MonteCarloSim.hpp MonteCarloSim.cpp
	g++ -c MonteCarloSim.hpp MonteCarloSim.cpp


