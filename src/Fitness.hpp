#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "SensorData.hpp"

class Fitness
{
    public:

        /**
         * Window length for findWalkPhases
         */
        static const size_t FINDWALK_WINDOW_LENGTH = 20;

        /**
         *
         */
        static void findWalkPhases(SensorData& sensors);
};

#endif

