#include <iostream>
#include <vector>
#include "Fitness.hpp"
#include "Plot.hpp"

void Fitness::findWalkPhases(SensorData& sensors)
{
    for (size_t i=0;i<sensors.getNbSensor();i++) {
        std::string name = sensors.getSensor(i);
        std::vector<double> norm;
        size_t bound = sensors.getSensorNbValues(name) - 
            Fitness::FINDWALK_WINDOW_LENGTH;
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
        Plot::add("Norm "+name, norm);
        Plot::plot();
    }
}

