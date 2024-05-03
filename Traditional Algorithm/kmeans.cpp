#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>

// Define a structure to represent a pixel in RGB color space
struct RGBPixel {
    unsigned char r, g, b;
};

// Define a structure to represent a cluster
struct Cluster {
    RGBPixel centroid;
    std::vector<RGBPixel> points;
};

// Function to load an image from a PPM file
std::vector<RGBPixel> loadImage(const std::string &filename, int &width, int &height) {
    std::ifstream file(filename, std::ios::binary);
    std::string line;
    std::getline(file, line); // Read the magic number
    std::getline(file, line); // Read the width and height
    std::istringstream iss(line);
    iss >> width >> height;
    std::getline(file, line); // Read the max value
    std::vector<RGBPixel> image(width * height);
    file.read(reinterpret_cast<char*>(image.data()), width * height * 3);
    return image;
}

// Function to save an image to a PPM file
void saveImage(const std::string &filename, const std::vector<RGBPixel> &image, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(image.data()), width * height * 3);
}

// Function to calculate the Euclidean distance between two pixels
double distance(const RGBPixel &a, const RGBPixel &b) {
    return std::sqrt(std::pow(a.r - b.r, 2) + std::pow(a.g - b.g, 2) + std::pow(a.b - b.b, 2));
}

// Function to perform KMeans clustering
void kMeansClustering(std::vector<RGBPixel> &image, int k, int maxIterations) {
    int width, height;
    std::vector<Cluster> clusters(k);
    std::vector<size_t> assignments(image.size());

    // Initialize cluster centroids randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, image.size() - 1);
    for (auto &cluster : clusters) {
        cluster.centroid = image[dis(gen)];
    }

    for (int iter = 0; iter < maxIterations; ++iter) {
        // Assign pixels to the nearest cluster
        for (size_t i = 0; i < image.size(); ++i) {
            double bestDistance = std::numeric_limits<double>::max();
            size_t bestCluster = 0;
            for (size_t j = 0; j < clusters.size(); ++j) {
                double dist = distance(image[i], clusters[j].centroid);
                if (dist < bestDistance) {
                    bestDistance = dist;
                    bestCluster = j;
                }
            }
            assignments[i] = bestCluster;
            clusters[bestCluster].points.push_back(image[i]);
        }

        // Calculate new centroids
        for (auto &cluster : clusters) {
            if (!cluster.points.empty()) {
                double sumR = 0, sumG = 0, sumB = 0;
                for (const auto &point : cluster.points) {
                    sumR += point.r;
                    sumG += point.g;
                    sumB += point.b;
                }
                cluster.centroid.r = static_cast<unsigned char>(sumR / cluster.points.size());
                cluster.centroid.g = static_cast<unsigned char>(sumG / cluster.points.size());
                cluster.centroid.b = static_cast<unsigned char>(sumB / cluster.points.size());
                cluster.points.clear();
            }
        }
    }

    // Assign the centroid's color to each pixel
    for (size_t i = 0; i < image.size(); ++i) {
        image[i] = clusters[assignments[i]].centroid;
    }
}

int main() {
    int width, height;
    std::vector<RGBPixel> image = loadImage("path_to_image.ppm", width, height);

    kMeansClustering(image, 3, 100); // Example: 3 clusters, 100 iterations

    saveImage("path_to_output.ppm", image, width, height);

    return 0;
}
