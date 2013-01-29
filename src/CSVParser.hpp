#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include "SensorData.hpp"

class CSVParser
{
    public:

        /**
         * Parse a CSV data file
         */
        static void parseFile(const char* filename, SensorData& sensors);
};

#endif

