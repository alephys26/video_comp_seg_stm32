/*
-------------------------------------
Yash Shrivastava, B21CS079
-------------------------------------
EEL3090: Embedded Systems
Course Project
-------------------------------------
Helper code for Layer behaviour
-------------------------------------
Currently not useful
Models MLP Hidden Layer
-------------------------------------
*/
#ifndef __HIDDENLAYER
#define __HIDDENLAYER
using namespace std;
#include <vector>
#include<string.h>
class HiddenLayer
{
private:
    char *activation_func;
    int num_neurons;
    int output_size;
    pair<int, int> input_size;
    vector<vector<double>> normalising_scalar;
    vector<vector<double>> weights;
    vector<vector<double>> bias;
    vector<vector<double>> outputs;
    vector<vector<double>> inputs;

protected:
    void set_num_next_layer_neurons(const int num_next_layer_neurons)
    {
        output_size = num_next_layer_neurons;
    }

    void set_num_neurons(const int neurons_number)
    {
        num_neurons = neurons_number;
    }

    void set_activation_function(const char *activation_function)
    {
        strcpy(activation_func, activation_function);
    }

    void set_inputs(const vector<vector<double>> &inp)
    {
        inputs = inp;
        input_size = {inputs.size(), inputs[0].size()};
    }

    const int get_num_next_layer_neurons()
    {
        return output_size;
    }

    const int get_num_neurons()
    {
        return num_neurons;
    }

    const vector<vector<double>> get_inputs()
    {
        return inputs;
    }

    const char *get_activation_function()
    {
        return activation_func;
    }

    const vector<vector<double>> calculate()
    {
        int n = num_neurons;
        int m = input_size.second;
        int k = input_size.first;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                double sum = 0.0;
                for (int l = 0; l < k; ++l)
                {
                    sum += weights[i][l] * inputs[l][j];
                }
                outputs[i][j] = sum + bias[i][j];
            }
        }
        return outputs;
    }
};
#endif