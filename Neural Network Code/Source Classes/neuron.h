/*
-------------------------------------
Yash Shrivastava, B21CS079
-------------------------------------
EEL3090: Embedded Systems
Course Project
-------------------------------------
Helper code for neuron behaviour
-------------------------------------
Currently useless
-------------------------------------
*/

#ifndef __NEURON
#define __NEURON
#include <iostream>
using namespace std;
class Neuron
{
private:
    double weight;
    double bias;


protected:
    const double get_weight()
    {
        return weight;
    }

    void set_weight(const double w)
    {
        weight = w;
    }

    const double get_bias()
    {
        return bias;
    }

    void set_bias(const double b)
    {
        bias = b;
    }

    const double calculate(const double input)
    {
        return weight * input + bias;
    }
};
#endif