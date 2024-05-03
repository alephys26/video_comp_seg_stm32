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
#ifndef UPSAMPLE_LAYER_H
#define UPSAMPLE_LAYER_H

#include <vector>

class UpsampleLayer {
private:
    int upsample_factor;

public:
    UpsampleLayer(int factor);

    std::vector<std::vector<double>> upsample(std::vector<std::vector<double>>& input);
};

#endif
