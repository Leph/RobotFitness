#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "CSVParser.hpp"

using namespace std;

void CSVParser::parseFile(const char* filename, ParticuleData& particules)
{
    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        throw string("Unable to open file: ")+string(filename);
    }

    char line[2048];
    string lineStr;
    string piece;
    int countLine = 0;
    while (file.good()) {
        file.getline(line, 2048);
        lineStr = line;
        size_t posBegin = 0;
        size_t posEnd = 0;
        size_t pieceCount = 0;
        
        //Extract pieces
        while (posEnd != string::npos) {
            posEnd = lineStr.find_first_of(';', posBegin);
            if (posEnd != string::npos) {
                piece = lineStr.substr(posBegin, posEnd-posBegin);
                posBegin = posEnd+1;
            } else {
                piece = lineStr.substr(posBegin);
            }
            if (piece.size() == 0) {
                continue;
            }
	    double value = atof(piece.c_str());
            if (countLine%2 == 0) {
	      particules.addParticule(value);
            } else {
	      particules.addParticuleValue(countLine/2, value);
            }
            pieceCount++;
        }
        countLine++;
    }

    file.close();
}

