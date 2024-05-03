#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>  // For file input/output operations
#include <string>   // For std::string
#include "kmeans.h" // Assuming RGBPixel is defined in kmeans.h

using namespace std;

class kMeans
{
public:
    struct RGBPixel
    {
        unsigned char r, g, b;
    };

    struct Cluster
    {
        RGBPixel centroid;
        vector<RGBPixel> points;
    };

    double distance(const RGBPixel &a, const RGBPixel &b);
    void kMeansClustering(const vector<RGBPixel> &image, int k, int maxIterations);
    vector<RGBPixel> load_image(const vector<vector<vector<int>>> &image, int &width, int &height);
    void saveImage(const string &filename, const vector<RGBPixel> &image, int width, int height);
};

#endif
