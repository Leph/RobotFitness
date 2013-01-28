#ifndef _SENSORDATA_HPP_
#define _SENSORDATA_HPP_

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;
 
class SensorData{
private: 
  vector<string> sensorName;
  std::map<string, vector<double> > valueMap;

public:
  SensorData();

  //Accessors
  // get the number of sensors stored
  unsigned int getNbSensor(void) const;
  // get and add sensor by name
  string getSensor(unsigned int indice) const;
  void addSensor(string name);
  
  // Access stored values given a sensor name
  unsigned int getSensorNbValues(string name);
  vector<double>& getSensorValues(string name);
  double getSensorValue(string name, unsigned int indice);
  void addSensorValue(string name, double value);
};
 
#endif
