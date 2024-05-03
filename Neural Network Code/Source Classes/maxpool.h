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

#ifndef MAX_POOL_LAYER_H
#define MAX_POOL_LAYER_H

#include <vector>
#include <algorithm>

class MaxPoolLayer {
private:
    int pool_size;

public:
    MaxPoolLayer(int size);

    std::vector<std::vector<double>> max_pool(std::vector<std::vector<double>>& input);
};

#endif
