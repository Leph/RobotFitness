#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Fitness.hpp"
#include "Plot.hpp"
#include "FFT.hpp"

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


std::vector<double> Fitness::computeFitness(SensorData& sensors, 
    const std::vector< std::pair<size_t,size_t> >& phases)
{
    size_t nbSensor = sensors.getNbSensor();
    size_t nbPhases = phases.size();
    double fitness=0;
    std::vector<double> fitnessVector;
    for(size_t j=0;j<nbPhases;j++) {
        for(size_t i=0;i<nbSensor;i++) {
            std::vector<double> phaseSignal;
	    std::vector<double> amplitudeSignal;
	    std::vector<double> frequencySignal;
            std::string sensorName = sensors.getSensor(i);
            std::vector<double>& sensorValues = sensors.getSensorValues(sensorName);
	    double realPart,imPart;
            //Compute for each window
            int indexStart = phases[j].first;
            int indexEnd = phases[j].second;
            for (size_t k=indexStart;k<indexEnd-FFT_WINDOW_LENGTH;k++) {
                //Compute FFT
                std::vector< std::pair<double,double> > result = windowedFFT(
                    sensorValues, k, k+FFT_WINDOW_LENGTH, FTT_SAMPLE_RATE, 1);
		
		
                size_t fundamental = findFundamental(result);
		
                //Compute freq and phase
                phaseSignal.push_back(atan2(result[fundamental].second, result[fundamental].first));
		frequencySignal.push_back((double)fundamental);
		realPart = result[fundamental].first;
		imPart = result[fundamental].second;
		amplitudeSignal.push_back(sqrt(realPart*realPart+imPart*imPart));
		
		
            }
	    
	    double pas =0.10;
	    double l;
	    size_t m,phaseSize;
	    double precision = pas/2;
	    for(l=M_PI;l>-M_PI;l-=pas){
	      std::vector<size_t> valueCompared;
	      phaseSize=phaseSignal.size();
	      for(m=0;m<phaseSize;m++){
		if(phaseSignal[m]+precision>l && phaseSignal[m]-precision<l){
		  valueCompared.push_back(m+indexStart);
		}
	      }
	      double mean=0;
	      size_t valueComparedSize =valueCompared.size();
	      for(m=0;m<valueComparedSize;m++){
		// Fitness : adding variance
		mean += sensorValues[valueCompared[m]];
	      }
	      mean = mean/valueComparedSize;
	      //std::cout<<"mean is "<<mean<<std::endl;
	      double variance=0;
	      if(valueComparedSize!=0){
		for(m=0;m<valueComparedSize;m++){
		  variance += abs(mean-sensorValues[valueCompared[m]]);
		}
		variance = variance/valueComparedSize;
		std::cout<<"variance is "<<variance<<std::endl;
		fitness += variance;
	      }
	    }
		  /*
            for(size_t k=0;k<result.size();k++) {
                double realPart = result[k].first;
                double imPart = result[k].second;
                plot1.push_back(sqrt(realPart*realPart+imPart*imPart));
                plot2.push_back(atan2(imPart,realPart));
            }
	    */
            if(i==1 && j == 2) {
                Plot::add("phase", phaseSignal);
		Plot::add("frequency",frequencySignal);
		//Plot::add("amplitude",amplitudeSignal);
	    }
        }
	fitnessVector.push_back(fitness);
	fitness=0;
    }
    Plot::plot();
    return fitnessVector;
}

size_t Fitness::findFundamental(std::vector<std::pair<double,double> > result){
  size_t i;
  double realPart = result[0].first;
  double imPart = result[0].second;
  double maxAmpl=sqrt(realPart*realPart+imPart*imPart);
  size_t indexMax =0;
  size_t resultSize = result.size();
  for(i=0;i<resultSize;i++){
    realPart = result[i].first;
    imPart = result[i].second;
    double tempAmpl=sqrt(realPart*realPart+imPart*imPart);
    if(tempAmpl>maxAmpl){
      indexMax=i;
      maxAmpl=tempAmpl;
    }
  }
  return indexMax;
}
