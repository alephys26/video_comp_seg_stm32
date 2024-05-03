#include "kmeans.h"
double distance(const kMeans::RGBPixel &a, const kMeans::RGBPixel &b)
{
    return sqrt(pow(a.r - b.r, 2) + pow(a.g - b.g, 2) + pow(a.b - b.b, 2));
}

void kMeansClustering(vector<kMeans::RGBPixel> &image, int k, int maxIterations)
{
    int width, height;
    vector<kMeans::Cluster> clusters(k);
    vector<size_t> assignments(image.size());
    int i = 0;
    for (auto &cluster : clusters)
    {
        cluster.centroid = image[i++];
    }
    for (int iter = 0; iter < maxIterations; ++iter)
    {
        // Assign pixels to the nearest cluster
        for (size_t i = 0; i < image.size(); ++i)
        {
            double bestDistance = numeric_limits<double>::max();
            size_t bestCluster = 0;
            for (size_t j = 0; j < clusters.size(); ++j)
            {
                double dist = distance(image[i], clusters[j].centroid);
                if (dist < bestDistance)
                {
                    bestDistance = dist;
                    bestCluster = j;
                }
            }
            assignments[i] = bestCluster;
            clusters[bestCluster].points.push_back(image[i]);
        }

        // Calculate new centroids
        for (auto &cluster : clusters)
        {
            if (!cluster.points.empty())
            {
                double sumR = 0, sumG = 0, sumB = 0;
                for (const auto &point : cluster.points)
                {
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
    for (size_t i = 0; i < image.size(); ++i)
    {
        image[i] = clusters[assignments[i]].centroid;
    }
}

vector<kMeans::RGBPixel> load_image(const vector<vector<vector<int>>> &image, int &width, int &height)
{
    int channels = image.size();
    width = image[0].size();
    height = image[0][0].size();
    std::vector<kMeans::RGBPixel> rgb_image(width * height);

    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            int r = image[0][w][h]; // Red channel
            int g = image[1][w][h]; // Green channel
            int b = image[2][w][h]; // Blue channel

            // Set the RGB values for the corresponding pixel in rgb_image
            rgb_image[w * height + h] = {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b)};
        }
    }

    return rgb_image;
}

void saveImage(const string &filename, const vector<kMeans::RGBPixel> &image, int width, int height)
{
    ofstream file(filename, ios::binary);
    file << "P6\n"
         << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char *>(image.data()), width * height * 3);
}