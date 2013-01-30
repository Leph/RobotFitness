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

        /**
         * Write particule data set to a
         * CSV file
         */
        static void writeFile(const char* filename, ParticuleData& data);
};

#endif

