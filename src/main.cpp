#include <cstdlib>
#include <iostream>
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
        Fitness::findWalkPhases(sensors);
    } catch (std::string error) {
        std::cout << "ERROR: " << error << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

