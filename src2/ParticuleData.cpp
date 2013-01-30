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


