#include <math.h>
#include "ParticuleGenerator.hpp"
#include <time.h>
ParticuleData& ParticuleGenerator::generate(ParticuleData& inputParticules){
  srand(time(NULL));
  ParticuleData* outputParticules =new ParticuleData();
  size_t nbKeptParticules = inputParticules.getNbParticule()/ParticuleGenerator::generationRatio;
  for(size_t i=0;i<nbKeptParticules;i++){
    size_t nbValues = inputParticules.getParticuleNbValues(i);
    for(size_t k=0;k<generationRatio;k++){
      outputParticules->addParticule(-1);
      for(size_t j=0;j<nbValues;j++){
	double inputValue =inputParticules.getParticuleValue(i,j);
	outputParticules->addParticuleValue(i*generationRatio+k,inputValue+valueRandRatio*inputValue*(2*rand()-1));
      }
    }
  }
  return (*outputParticules);
}
