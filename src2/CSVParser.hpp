#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include "ParticuleData.hpp"

class CSVParser
{
    public:

        /**
         * Parse a CSV data file
         */
        static void parseFile(const char* filename, ParticuleData& sensors);
};

#endif

