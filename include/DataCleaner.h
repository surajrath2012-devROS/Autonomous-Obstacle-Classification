#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// A lightweight structure to hold exactly what one row of our CSV looks like.
// Structs are public by default, which is perfect for raw data objects.
struct BoundingBox {
    float x, y, z;
    float width, length, height;
    std::string objectClass;
};

class DataCleaner {

private:
    // The master dataset. Hidden from the outside world so no one can accidentally delete data.
    std::vector<BoundingBox> dataset;

public:
    // Constructor
    DataCleaner() = default;

    // Returns a reference to the dataset so Python can read it.
    const std::vector<BoundingBox>& getDataset() const;

    // Pass-by-Reference (&): We pass the file path address to save memory.
    // 'const' ensures we don't accidentally modify the string inside the function.
    void loadCSV(const std::string& filepath);

    // Filters the data
    void removeOutliers();

    // The 'const' at the end means: "I promise this function will only READ data, not modify it."
    void printSummary() const;
};