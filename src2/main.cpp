#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "CSVParser.hpp"
#include "ParticuleData.hpp"
#include "ParticuleGenerator.hpp"

int main()
{
    try {
        ParticuleData particules = ParticuleData();
        std::cout << "loading..." << std::endl;
        CSVParser::parseFile("particulesDataTest.csv", particules);
        particules.quicksortValuesByFitness();
	ParticuleData& resultParticules =ParticuleGenerator::generate(particules);
	CSVParser::writeFile("particulesResult.csv",resultParticules);
    } catch (std::string error) {
        std::cout << "ERROR: " << error << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

