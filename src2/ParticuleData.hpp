#ifndef _PARTICULEDATA_HPP_
#define _PARTICULEDATA_HPP_

#include <iostream>
#include <cstdlib>
#include <vector>


class ParticuleData
{   
public:
    
    ParticuleData();

    /**
     * Get the number of particules stored
     */
    size_t getNbParticule() const;
    
    /**
     * Get particule fitness by index
     */
    double getParticuleFitness(size_t indexParticule) const;

    /**
     * Add particule with fitness
     */
    void addParticule(double fitness);
  
    /**
     * Get the number of values for a given particule
     */
    size_t getParticuleNbValues(size_t indexParticule);

    /**
     * Access container value or value of a given particule
     */
    std::vector<double>& getParticuleValues(size_t indexParticule);
    double getParticuleValue(size_t indexParticle, size_t indexValue);

    /**
     * Append a value to a particule container 
     */
    void addParticuleValue(size_t indexParticle, size_t value);

  /**
   * Sort values and particuleFitness by ascending fitness
   */
  void quicksortValuesByFitness(); 


private: 


  /**
   * Particule fitnesse container
   */
   std::vector<double> _particuleFitness;

    /**
     * Values container
     */
  std::vector< std::vector<double> > _values;

  size_t partition(size_t p, size_t r);

  void quicksort(size_t p, size_t r);

};
 
#endif
