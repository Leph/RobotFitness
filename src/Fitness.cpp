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
    std::vector<double> fitnessVector;
    //Evaluate fitness for each walking phases
    for (size_t j=0;j<nbPhases;j++) {
        double fitness = 0;
        //For each sensors
        for (size_t i=0;i<nbSensor;i++) {
            //Contains interpolated phase, amplitude and fundamental frequency
            std::vector<double> phaseSignal;
	         std::vector<double> amplitudeSignal;
	         std::vector<double> frequencySignal;
            //Usefull variables
            std::string sensorName = sensors.getSensor(i);
            std::vector<double>& sensorValues = sensors.getSensorValues(sensorName);
            int indexStart = phases[j].first;
            int indexEnd = phases[j].second;
            //Compute on sliding window
            for (size_t k=indexStart;k<indexEnd-FFT_WINDOW_LENGTH;k++) {
                //Compute FFT on the window
                std::vector< std::pair<double,double> > fftCoefs = windowedFFT(
                    sensorValues, k, k+FFT_WINDOW_LENGTH, FTT_SAMPLE_RATE, 1);
	             //Find fundamental frequency of the window signal
                size_t fundamental = findFundamental(fftCoefs);
                //Compute freq and phase for the fundamental frequency
		          double realPart = fftCoefs[fundamental].first;
		          double imPart = fftCoefs[fundamental].second;
                phaseSignal.push_back(atan2(imPart, realPart));
		          frequencySignal.push_back(fundamental);
		          amplitudeSignal.push_back(sqrt(realPart*realPart+imPart*imPart));
            }
	         //Now, evaluates fitness on the walking phase
            //For each phase value (movement step)
            for (double l=M_PI;l>=-M_PI;l-=FITNESS_PHASE_STEP) {
                //Find all sensors value at same movement step
                std::vector<size_t> valueCompared;
                for (size_t m=0;m<phaseSignal.size();m++) {
                    if(
                        phaseSignal[m]+FITNESS_PHASE_THRESHOLD > l && 
                        phaseSignal[m]-FITNESS_PHASE_THRESHOLD < l
                    ){
                        valueCompared.push_back(indexStart+m);
                    }
                }
                if (valueCompared.size() == 0) {
                    continue;
                }
                //Then, compute values mean
                double mean = 0;
                for (size_t m=0;m<valueCompared.size();m++) {
                    mean += sensorValues[valueCompared[m]];
                }
                mean = mean/valueCompared.size();
                //Compute values variance 
                double variance = 0;
                for(size_t m=0;m<valueCompared.size();m++) {
                    variance += abs(mean - sensorValues[valueCompared[m]]);
                }
                variance = variance/valueCompared.size();
                //Add the error to fitness
                fitness += variance;
            }
            if(i==1 && j==3) {
                Plot::add("phase", phaseSignal);
		          Plot::add("frequency", frequencySignal);
                Plot::plot();
	         }
        }
	     fitnessVector.push_back(fitness);
    }

    return fitnessVector;
}

size_t Fitness::findFundamental
    (const std::vector< std::pair<double,double> >& fftCoefs)
{
    double realPart = fftCoefs[0].first;
    double imPart = fftCoefs[0].second;
    double maxAmpl = sqrt(realPart*realPart+imPart*imPart);
    size_t indexMax = 0;
    for(size_t i=0;i<fftCoefs.size();i++) {
        realPart = fftCoefs[i].first;
        imPart = fftCoefs[i].second;
        double tmpAmpl = sqrt(realPart*realPart+imPart*imPart);
        if(tmpAmpl > maxAmpl){
            indexMax = i;
            maxAmpl = tmpAmpl;
        }
    }
    return indexMax;
}

