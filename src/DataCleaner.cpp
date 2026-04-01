#include <iostream>
#include <sstream>
#include "../include/DataCleaner.h"

// 1. Implementation of loadCSV
void DataCleaner::loadCSV(const std::string& filepath) {
    std::ifstream file(filepath);
    
    // Safety check: Did the file actually open?
    if (!file.is_open()) {
        std::cerr << "[DataCleaner] ERROR: Could not open file " << filepath << std::endl;
        return;
    }

    std::string line;
    // Read and ignore the very first line (the header: "Id,PredictionString")
    std::getline(file, line);

    std::cout << "[DataCleaner] Parsing Kaggle dataset... This might take a second!" << std::endl;

    // Loop through every line in the file
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string id, predictionString;

        // Cut the line at the comma ','
        // id gets the left side, predictionString gets the right side
        if (std::getline(lineStream, id, ',') && std::getline(lineStream, predictionString)) {

            // Now put that massive space-separated string into a NEW stream
            std::stringstream predStream(predictionString);
            BoundingBox box;
            float yaw; // We extract it to keep the stream moving, even if we don't save it in our struct right now

            // The '>>' operator automatically jumps from space to space!
            // It reads exactly 8 items at a time. If it successfully reads 8 items, it saves the box.
            while (predStream >> box.x >> box.y >> box.z >> box.width >> box.length >> box.height >> yaw >> box.objectClass) {
                dataset.push_back(box); // Save it to our private master dataset!
            }
        }
    }
    std::cout << "[DataCleaner] Successfully loaded " << dataset.size() << " raw bounding boxes." << std::endl;
}

// 2. Implementation of removeOutliers
void DataCleaner::removeOutliers() {
    std::cout << "[DataCleaner] Filtering out impossible boxes (e.g., negative widths)..." << std::endl;
    
    std::vector<BoundingBox> cleanData; // A temporary clean bucket

    for (const auto& box : dataset) {
        // Basic physics check: Objects must have positive dimensions.
        // Also, a normal car isn't 50 meters wide, so let's filter out crazy glitches.
        if (box.width > 0 && box.length > 0 && box.width < 20.0 && box.length < 30.0) {
            cleanData.push_back(box);
        }
    }

    // Replace the dirty dataset with our clean bucket
    dataset = cleanData; 
    std::cout << "[DataCleaner] Filter complete." << std::endl;
}

// 3. Implementation of printSummary
void DataCleaner::printSummary() const {
    std::cout << "[DataCleaner] Total valid bounding boxes ready for Python: " << dataset.size() << std::endl;
}

    // 4. Implementation of getDataset
    const std::vector<BoundingBox>& DataCleaner::getDataset() const {
    return dataset;
}