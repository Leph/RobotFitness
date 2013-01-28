#include "SensorData.hpp"
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
