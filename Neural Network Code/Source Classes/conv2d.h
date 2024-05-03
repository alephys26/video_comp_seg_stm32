#ifndef CONV2D_LAYER_H
#define CONV2D_LAYER_H

#include <vector>
#include <algorithm>

class Conv2dLayer {
private:
    std::vector<std::vector<double>> kernel;
    int input_channels;
    int output_channels;
    int kernel_size;

public:
    Conv2dLayer(int in_channels, int out_channels, int k_size);

    std::vector<std::vector<double>> forward(std::vector<std::vector<double>>& input);
};

#endif