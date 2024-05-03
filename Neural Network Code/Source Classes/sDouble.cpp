/*
-------------------------------------
Yash Shrivastava, B21CS079
-------------------------------------
EEL3090: Embedded Systems
Course Project
-------------------------------------
Currently useful
Generates a new DataType SingleByteFloat
-------------------------------------
*/
#include <iostream>
#include <cstdint>

class SingleByteDouble {
private:
    uint8_t rawValue; // Store the raw bytes of the custom data type

public:
    // Default constructor
    SingleByteDouble() : rawValue(0) {}

    // Constructor that initializes the custom data type with a double value
    SingleByteDouble(double value) {
        setValue(value);
    }

    // Set the value of the custom data type based on a double value
    void setValue(double value) {
        // Convert the double value to a uint8_t value by scaling and truncating
        rawValue = static_cast<uint8_t>(value * 10); // Example scaling factor, adjust as needed
    }

    // Get the value of the custom data type as a double
    double getValue() const {
        // Convert the uint8_t value back to a double by reversing the scaling
        return static_cast<double>(rawValue) / 10.0; // Example reverse scaling, adjust as needed
    }
};

int main() {
    SingleByteDouble sbd(3.14159);
    std::cout << "Original double value: " << 3.14159 << std::endl;
    std::cout << "Single byte double value: " << sbd.getValue() << std::endl;

    return 0;
}
