#include "ParticuleData.hpp"

using namespace std;
 
ParticuleData::ParticuleData() :
    _particuleFitness(),
    _values()
{
}

size_t ParticuleData::getNbParticule() const 
{
    return _particuleFitness.size();
}

double ParticuleData::getParticuleFitness(size_t indexParticule) const
{
    if(indexParticule < _particuleFitness.size()) {
        return _particuleFitness[indexParticule];
    }
    else {
        throw string("Unbound index");
    }
}

void ParticuleData::addParticule(double fitness)
{
    _particuleFitness.push_back(fitness);
    _values.push_back(vector<double>());
}

size_t ParticuleData::getParticuleNbValues(size_t indexParticule)
{
    return _values[indexParticule].size();
}

vector<double>& ParticuleData::getParticuleValues(size_t indexParticule)
{
    return _values[indexParticule];
}

double ParticuleData::getParticuleValue(size_t indexParticle, size_t indexValue)
{
    return _values[indexParticle][indexValue];
}

void ParticuleData::addParticuleValue(size_t indexParticle, size_t value)
{
    _values[indexParticle].push_back(value);
}

size_t ParticuleData::partition(size_t p, size_t r)
{
    double pivot = _particuleFitness[r];
    while ( p < r )
    {
        while ( _particuleFitness[p] < pivot )
            p++;

        while ( _particuleFitness[r] > pivot )
            r--;

        if ( _particuleFitness[p] == _particuleFitness[r] )
            p++;
        else if ( p < r )
        {
            double tmp = _particuleFitness[p];
            _particuleFitness[p] = _particuleFitness[r];
            _particuleFitness[r] = tmp;

	    vector<double> tmp2 = _values[p];
	    _values[p] = _values[r];
	    _values[r] = tmp2;
        }
    }

    return r;
}

void ParticuleData::quicksortValuesByFitness()
{
  size_t p = 0,r = getNbParticule()-1;
  quicksort(p,r);
}

void ParticuleData::quicksort(size_t p, size_t r){
  if ( p < r )
    {
      size_t j = partition(p, r);   
      if(j>0)
        quicksort(p, j-1);
      quicksort(j+1, r);
	
    }
}
