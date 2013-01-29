#include "SensorData.hpp"
<<<<<<< HEAD
#include "assert.h"

SensorData::SensorData(){

}

unsigned int SensorData::getNbSensor(void)const{
  return this->sensorName.size();
}

string SensorData::getSensor(unsigned int indice)const{
  string result;
  if(indice < this->sensorName.size()){
    result = sensorName[indice];
  }
  else {
    result = "";
  }
  return result;
}

void SensorData::addSensor(string name){
  this->sensorName.push_back(name);
  this->valueMap[name]=vector<double>();
}

unsigned int SensorData::getSensorNbValues(string name){
  return this->valueMap[name].size();
}

vector<double>& SensorData::getSensorValues(string name){
  return this->valueMap[name];
}

double SensorData::getSensorValue(string name, unsigned int indice){
  return this->valueMap[name][indice];
}

void SensorData::addSensorValue(string name, double value){
  this->valueMap[name].push_back(value);
}
=======

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

>>>>>>> 210b1024401f7d02216904deecdad4d1c16bc343
