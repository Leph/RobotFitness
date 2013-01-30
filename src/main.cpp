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
        //Load data
        SensorData sensors = SensorData();
        std::cout << "loading..." << std::endl;
        CSVParser::parseFile("../data.csv", sensors);

        //Find walking phases
        std::vector< std::pair<size_t,size_t> > phases = 
            Fitness::findWalkPhases(sensors);
        std::cout << "Walking phases:" << std::endl;
        for (size_t i=0;i<phases.size();i++) {
            std::cout << "start " << phases[i].first 
            << " stop " << phases[i].second << std::endl;
        }

        //Compute fitness
        std::vector<double> fitnesses = Fitness::computeFitness(sensors, phases);
        Plot::add("Fitnesses for each walk phase", fitnesses);
        Plot::plot();
    } catch (std::string error) {
        std::cout << "ERROR: " << error << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

