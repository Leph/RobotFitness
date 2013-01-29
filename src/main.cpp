#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "CSVParser.hpp"
#include "Plot.hpp"
#include "Fitness.hpp"

int main()
{
    try {
        SensorData sensors = SensorData();
        std::cout << "loading..." << std::endl;
        CSVParser::parseFile("../data.csv", sensors);
        std::vector< std::pair<size_t,size_t> > phases = 
            Fitness::findWalkPhases(sensors);
       for (size_t i=0;i<phases.size();i++) {
            std::cout << "start " << phases[i].first 
           << " stop " << phases[i].second << std::endl;
        }
       Fitness::computeFitness(sensors, phases);
    } catch (std::string error) {
        std::cout << "ERROR: " << error << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

