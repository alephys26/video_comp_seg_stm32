#include <iostream>
#include <vector>
#include <algorithm>
class Conv2dLayer {
private:
    std::vector<std::vector<double>> kernel;
    int input_channels;
    int output_channels;
    int kernel_size;

public:
    Conv2dLayer(int in_channels, int out_channels, int k_size) :
        input_channels(in_channels), output_channels(out_channels), kernel_size(k_size)
    {
        // Initialize kernel weights randomly or with specific values as per your requirement
        kernel.resize(output_channels, std::vector<double>(input_channels * kernel_size * kernel_size));
        // Fill in kernel weights with appropriate values
        // This can be done randomly or with specific initialization techniques
        // For simplicity, let's initialize it randomly here
        for (int i = 0; i < output_channels; ++i) {
            for (int j = 0; j < input_channels * kernel_size * kernel_size; ++j) {
                kernel[i][j] = rand() % 10; // Random weights between 0 and 9
            }
        }
    }

    // Forward pass function with ReLU activation, MaxPool2d, and Upsample
    std::vector<std::vector<double>> forward(std::vector<std::vector<double>>& input) {
        int input_height = input.size();
        int input_width = input[0].size();
        int output_height = input_height - kernel_size + 1;
        int output_width = input_width - kernel_size + 1;

        std::vector<std::vector<double>> output(output_height, std::vector<double>(output_width));

        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                for (int oc = 0; oc < output_channels; ++oc) {
                    double sum = 0.0;
                    for (int ic = 0; ic < input_channels; ++ic) {
                        for (int ki = 0; ki < kernel_size; ++ki) {
                            for (int kj = 0; kj < kernel_size; ++kj) {
                                sum += input[i + ki][j + kj] * kernel[oc][ic * kernel_size * kernel_size + ki * kernel_size + kj];
                            }
                        }
                    }
                    // Apply ReLU activation
                    output[i][j] += std::max(0.0, sum);
                }
            }
        }

        // MaxPool2d
        int pool_size = 2; // Pool size for MaxPool2d
        std::vector<std::vector<double>> pooled_output(output_height / pool_size, std::vector<double>(output_width / pool_size));

        for (int i = 0; i < output_height; i += pool_size) {
            for (int j = 0; j < output_width; j += pool_size) {
                double max_val = output[i][j];
                for (int pi = i; pi < i + pool_size; ++pi) {
                    for (int pj = j; pj < j + pool_size; ++pj) {
                        max_val = std::max(max_val, output[pi][pj]);
                    }
                }
                pooled_output[i / pool_size][j / pool_size] = max_val;
            }
        }

        // Upsample
        int upsample_factor = 2;
        std::vector<std::vector<double>> upsampled_output(output_height * upsample_factor, std::vector<double>(output_width * upsample_factor));

        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                for (int fi = 0; fi < upsample_factor; ++fi) {
                    for (int fj = 0; fj < upsample_factor; ++fj) {
                        upsampled_output[i * upsample_factor + fi][j * upsample_factor + fj] = pooled_output[i][j];
                    }
                }
            }
        }

        return upsampled_output;
    }
};

int main() {
    int input_channels = 1;
    int output_channels = 1;
    int kernel_size = 3;

    Conv2dLayer conv_layer(input_channels, output_channels, kernel_size);

    // Example input image (3x3)
    std::vector<std::vector<double>> input = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Perform forward pass
    std::vector<std::vector<double>> output = conv_layer.forward(input);

    // Print output
    for (const auto& row : output) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
