#include <iostream>
#include <vector>
#include "Fitness.hpp"
#include "Plot.hpp"

std::vector< std::pair<size_t,size_t> > Fitness::findWalkPhases(SensorData& sensors)
{
    std::vector<double> normCoef(
        sensors.getSensorValues(sensors.getSensor(0)).size(), 0.0);
    for (size_t i=0;i<sensors.getNbSensor();i++) {
        std::string name = sensors.getSensor(i);
        if (sensors.getSensorNbValues(name) != normCoef.size()) {
            throw std::string("Different dataset size");
        }
        std::vector<double> norm;
        size_t bound = sensors.getSensorNbValues(name) - 
            Fitness::FINDWALK_WINDOW_LENGTH;
        //Compute norm
        for (size_t j=0;j<bound;j++) {
            double min = sensors.getSensorValue(name, j);
            double max = sensors.getSensorValue(name, j);
            for (size_t k=0;k<Fitness::FINDWALK_WINDOW_LENGTH;k++) {
                if (sensors.getSensorValue(name, j+k) < min) {
                    min = sensors.getSensorValue(name, j+k);
                }
                if (sensors.getSensorValue(name, j+k) > max) {
                    max = sensors.getSensorValue(name, j+k);
                }
            }
            norm.push_back(max-min);
        }
        //Normalize
        double maxNorm = norm[0];
        double minNorm = norm[0];
        for (size_t j=0;j<norm.size();j++) {
            if (norm[j] < minNorm) {
                minNorm = norm[j];
            }
            if (norm[j] > maxNorm) {
                maxNorm = norm[j];
            }
        }
        for (size_t j=0;j<norm.size();j++) {
            norm[j] = (norm[j]-minNorm)/(maxNorm-minNorm);
            normCoef[j] += norm[j];
        }
    }
    //Extract phases
    std::vector< std::pair<size_t,size_t> > phases;
    for (size_t j=0;j<normCoef.size();j++) {
        size_t start;
        size_t stop;
        if (normCoef[j] > FINDWALK_THRESHOLD*sensors.getNbSensor()) {
            start = j-FINDWALK_WINDOW_LENGTH;
            while (
                j < normCoef.size() && 
                normCoef[j] > FINDWALK_THRESHOLD*sensors.getNbSensor()
            ) {
                j++;
            }
            stop = j+FINDWALK_WINDOW_LENGTH < normCoef.size() ? 
                j+FINDWALK_WINDOW_LENGTH : normCoef.size();
            phases.push_back(std::pair<size_t,size_t>(start, stop));
        } 
    }

    return phases;
}

