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

#include "conv2d.h"

Conv2dLayer::Conv2dLayer(int in_channels, int out_channels, int k_size) : input_channels(in_channels), output_channels(out_channels), kernel_size(k_size)
{
}

void Conv2dLayer::setWeights(std::vector<std::vector<double>> weights)
{
    kernel = weights;
}

std::vector<std::vector<double>> Conv2dLayer::forward(std::vector<std::vector<double>> &input)
{
    {
        int input_height = input.size();
        int input_width = input[0].size();
        int output_height = input_height - kernel_size + 1;
        int output_width = input_width - kernel_size + 1;

        std::vector<std::vector<double>> output(output_height, std::vector<double>(output_width));

        for (int i = 0; i < output_height; ++i)
        {
            for (int j = 0; j < output_width; ++j)
            {
                for (int oc = 0; oc < output_channels; ++oc)
                {
                    double sum = 0.0;
                    for (int ic = 0; ic < input_channels; ++ic)
                    {
                        for (int ki = 0; ki < kernel_size; ++ki)
                        {
                            for (int kj = 0; kj < kernel_size; ++kj)
                            {
                                sum += input[i + ki][j + kj] * kernel[oc][ic * kernel_size * kernel_size + ki * kernel_size + kj];
                            }
                        }
                    }
                    // Apply ReLU activation
                    output[i][j] += std::max(0.0, sum);
                }
            }
        }
    }
}