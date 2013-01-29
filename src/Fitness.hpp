#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "SensorData.hpp"

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
         * FTT sample rate for computeFitness
         */
        static const int FTT_SAMPLE_RATE = 8192;

        /**
         * FTT window length for computeFitness
         */
        static const size_t FFT_WINDOW_LENGTH = 200;

        /**
         * Returns pair (begin, end) of walking phases
         */
        static std::vector< std::pair<size_t,size_t> > findWalkPhases
            (SensorData& sensors);

        /**
         * Compute FFT
         **/ 
        static void computeFitness(SensorData& sensors, 
            const std::vector< std::pair<size_t,size_t> >& phases);
};

#endif

