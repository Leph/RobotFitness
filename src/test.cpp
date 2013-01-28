#include "SensorData.hpp"

using namespace std;

void scenario1(SensorData & test){
  string result = test.getSensor(10);
  cout<<"test 1 :" << result<<endl;
  test.addSensor("alpha");
  test.addSensor("beta");
  test.addSensor("teta");
  test.addSensorValue("machin",112.5);
  test.addSensorValue("alpha",2);
  test.addSensorValue("teta",-1);
  test.addSensorValue("teta",-4);
  test.addSensorValue("teta",2);
}

SensorData& scenario2(){
  SensorData* test = new SensorData();
  string result = test->getSensor(10);
  cout<<"test element non existant :" << result<<endl;
  test->addSensor("alpha");
  test->addSensor("beta");
  test->addSensor("teta");
  test->addSensorValue("machin",112.5);
  test->addSensorValue("alpha",2);
  test->addSensorValue("teta",-1);
  test->addSensorValue("teta",-4);
  test->addSensorValue("teta",2);
  return *test;
}

int main(int argc, char *argv[])
{
  /*
  SensorData test;
  scenario1(test);
  */
  SensorData& test = scenario2();

  unsigned int i,j;
  for(i=0;i<test.getNbSensor();i++){
    cout<<"*** accessing "<<i<<"eme sensor :***"<<test.getSensor(i)<<endl;
    // teste premiere methode de faire des boucles
    cout<<"containing "<<test.getSensorNbValues(test.getSensor(i))<<" values :"<<endl;
    for(j=0;j<test.getSensorNbValues(test.getSensor(i));j++){
      cout<<test.getSensorValue(test.getSensor(i),j)<<" ";
    }
    cout<<endl;
    cout<<"*** testing other access method ***" ;
    string sensorName =test.getSensor(i);
    vector<double>& sensorValues = test.getSensorValues(sensorName);
    cout<<"containing "<<sensorValues.size()<<" values :"<<endl;
    for(j=0;j<sensorValues.size();j++){
      cout<<sensorValues[j]<<" ";
    }
    cout<<endl;
  }
  delete(&test);
  return EXIT_SUCCESS;
}
