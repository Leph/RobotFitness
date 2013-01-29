#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "CSVParser.hpp"

using namespace std;

void CSVParser::parseFile(const char* filename, SensorData& sensors)
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
        //Handle first line
        if (countLine == 0) {
            if (lineStr[0] != '#') {
                throw string("No label first line");
            }
            posBegin = 1;
        } 
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
            if (countLine == 0) {
                sensors.addSensor(piece);
            } else {
                double value = atof(piece.c_str());
                sensors.addSensorValue(sensors.getSensor(pieceCount), value);
            }
            pieceCount++;
        }
        countLine++;
    }

    file.close();
}

