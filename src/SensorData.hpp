#ifndef _SENSORDATA_HPP_
#define _SENSORDATA_HPP_

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>


class SensorData
{   
public:
    
    SensorData();

    /**
     * Get the number of sensors stored
     */
    size_t getNbSensor() const;
    
    /**
     * Get sensor name by index
     */
    std::string& getSensor(size_t index) const;

    /**
     * Add sensor by name
     */
    void addSensor(const std::string& name);
  
    /**
     * Get the number of value for a given sensor
     */
    size_t getSensorNbValues(const std::string& name);

    /**
     * Access container value or value of a given sensor
     */
    std::vector<double>& getSensorValues(const std::string& name);
    double getSensorValue(const std::string& name, size_t index);

    /**
     * Append a value to a sensor container by its name
     */
    void addSensorValue(const std::string& name, double value);

private: 

    /**
     * Sensor name container
     */
    std::vector<std::string> _sensorName;

    /**
     * Value map container
     */
    std::map<std::string, std::vector<double> > _valueMap;
};
 
#endif
