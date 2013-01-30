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
	// Le meilleur est preservé intact
	if(i==0 && k==0){
	  outputParticules->addParticuleValue(i*generationRatio+k,inputValue);
	}
	else {
	  outputParticules->addParticuleValue(i*generationRatio+k,inputValue+valueRandRatio*inputValue*(2*((double)rand())/(double)(RAND_MAX)-1));
	}
      }
    }
  }
  return (*outputParticules);
}
