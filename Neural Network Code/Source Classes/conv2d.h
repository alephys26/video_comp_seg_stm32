/*
-------------------------------------
Yash Shrivastava, B21CS079
-------------------------------------
EEL3090: Embedded Systems
Course Project
-------------------------------------
Helper code for Layer behaviour
-------------------------------------
Currently useful
Models Conv2D Layer with ReLU activation
-------------------------------------
*/
#ifndef CONV2D_LAYER_H
#define CONV2D_LAYER_H

#include <vector>
#include <algorithm>

class Conv2dLayer
{
private:
    int input_channels;
    int output_channels;
    int kernel_size;

public:
    std::vector<std::vector<double>> kernel;
    Conv2dLayer(int in_channels, int out_channels, int k_size);
    std::vector<std::vector<double>> forward(std::vector<std::vector<double>> &input);
};
#endif