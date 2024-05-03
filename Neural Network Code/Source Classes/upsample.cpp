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
Models Upsample
-------------------------------------
*/
#include "upsample.h"

UpsampleLayer::UpsampleLayer(int factor) : upsample_factor(factor) {}

std::vector<std::vector<double>> UpsampleLayer::upsample(std::vector<std::vector<double>>& input) {
    int input_height = input.size();
    int input_width = input[0].size();
    int output_height = input_height * upsample_factor;
    int output_width = input_width * upsample_factor;

    std::vector<std::vector<double>> upsampled_output(output_height, std::vector<double>(output_width));

    for (int i = 0; i < input_height; ++i) {
        for (int j = 0; j < input_width; ++j) {
            for (int fi = 0; fi < upsample_factor; ++fi) {
                for (int fj = 0; fj < upsample_factor; ++fj) {
                    upsampled_output[i * upsample_factor + fi][j * upsample_factor + fj] = input[i][j];
                }
            }
        }
    }

    return upsampled_output;
}
