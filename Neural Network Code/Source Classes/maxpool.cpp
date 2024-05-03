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
Models MaxPool
-------------------------------------
*/
#include "maxpool.h"

MaxPoolLayer::MaxPoolLayer(int size) : pool_size(size) {}

std::vector<std::vector<double>> MaxPoolLayer::max_pool(std::vector<std::vector<double>>& input) {
    int input_height = input.size();
    int input_width = input[0].size();
    int output_height = input_height / pool_size;
    int output_width = input_width / pool_size;

    std::vector<std::vector<double>> pooled_output(output_height, std::vector<double>(output_width));

    for (int i = 0; i < input_height; i += pool_size) {
        for (int j = 0; j < input_width; j += pool_size) {
            double max_val = input[i][j];
            for (int pi = i; pi < i + pool_size; ++pi) {
                for (int pj = j; pj < j + pool_size; ++pj) {
                    max_val = std::max(max_val, input[pi][pj]);
                }
            }
            pooled_output[i / pool_size][j / pool_size] = max_val;
        }
    }

    return pooled_output;
}
