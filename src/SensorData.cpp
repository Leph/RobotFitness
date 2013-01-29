#include "SensorData.hpp"

using namespace std;
 
SensorData::SensorData() :
    _sensorName(),
    _valueMap()
{
}

size_t SensorData::getNbSensor() const 
{
    return _sensorName.size();
}

string& SensorData::getSensor(size_t index) const
{
    if(index < _sensorName.size()) {
        return (string&)_sensorName[index];
    }
    else {
        throw string("Unbound index");
    }
}

void SensorData::addSensor(const string& name)
{
    _sensorName.push_back(name);
    _valueMap[name] = vector<double>();
}

size_t SensorData::getSensorNbValues(const string& name)
{
    return _valueMap[name].size();
}

vector<double>& SensorData::getSensorValues(const string& name)
{
    return _valueMap[name];
}

double SensorData::getSensorValue(const string& name, size_t index)
{
    return _valueMap[name][index];
}

void SensorData::addSensorValue(const string& name, double value)
{
    _valueMap[name].push_back(value);
}


