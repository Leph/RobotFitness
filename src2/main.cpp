#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "CSVParser.hpp"
#include "ParticuleData.hpp"

int main()
{
    try {
        ParticuleData particules = ParticuleData();
        std::cout << "loading..." << std::endl;
        CSVParser::parseFile("particulesDataTest.csv", particules);
        particules.quicksortValuesByFitness();
	for(unsigned int i=0;i<particules.getNbParticule();i++){
	  std::cout<<"Particule "<<i<<" of fitness "<<particules.getParticuleFitness(i)<<std::endl;
	  for(unsigned int j=0;j<particules.getParticuleNbValues(i);j++){
	    std::cout<<particules.getParticuleValue(i,j)<<" ";
	  }
	  std::cout<<std::endl;
	}
    } catch (std::string error) {
        std::cout << "ERROR: " << error << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

