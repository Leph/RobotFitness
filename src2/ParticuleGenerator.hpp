#ifndef _PARTICULEGENERATOR_HPP_
#define _PARTICULEGENERATOR_HPP_

#include <iostream>
#include <cstdlib>
#include "ParticuleData.hpp"

class ParticuleGenerator {
 public:
  static const double generationRatio = 4;
  static const double valueRandRatio = 0.1;
  
  static ParticuleData& generate(ParticuleData& inputParticules);




 private:
};

#endif
