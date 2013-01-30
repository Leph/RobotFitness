#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "SensorData.hpp"

#define SAMPLE_RATE 64 

class Fitness
{
    public:

        /**
         * Window length for findWalkPhases
         */
        static const size_t FINDWALK_WINDOW_LENGTH = 30;
        
        /**
         * Threshold for findWalkPhases
         */
        static const double FINDWALK_THRESHOLD = 0.5;

        /**
         * Returns pair (begin, end) of walking phases
         */
        static std::vector< std::pair<size_t,size_t> > findWalkPhases
            (SensorData& sensors);

  /**
   * Compute FFT
   **/ 
  static void computeFitness(SensorData& sensors, std::vector< std::pair<size_t,size_t> >& phases);
};

#endif

