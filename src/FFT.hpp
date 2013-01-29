#ifndef _FFT_H_
#define _FFT_H_

/**
 * Calcul de la FFT (code d'origine rhoban)
 */
std::vector<std::pair<double,double> > FFT
    (std::vector<double>& signal, unsigned int sample_rate, int sign);

/**
 * Calcul de la FFT pour une fenetre donnee du vecteur en entre
 */
std::vector<std::pair<double,double> > windowedFFT(
    const std::vector<double>& sensorValues, size_t startIndex, size_t endIndex,
    int sample_rate, int sign);

#endif
