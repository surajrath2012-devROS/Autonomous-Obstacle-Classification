#include <iostream>
#include <vector>
#include <memory>
#include "../include/Lidar.h"
#include "../include/DataCleaner.h"

int main()
{
    // 1. Create the Universal Box
    std::vector<std::unique_ptr<Sensor>> sensorSuite;

    // 2. Build a Lidar on the Heap, and put its smart pointer into the box
    sensorSuite.push_back(std::make_unique<Lidar>("Roof_Top_Lidar", 120.5, 64));

    // 3. The Processing Loop 
    std::cout << "\n--- STARTING SENSOR FUSION ENGINE ---\n";
    for (const auto& sensorPtr : sensorSuite) {
        sensorPtr->loadRawData();
        sensorPtr->applyNoiseFilter();
    }
    std::cout << "--- ENGINE SHUTTING DOWN ---\n\n";

    std::cout << "\n--- STARTING DATA INGESTION ---\n";
    DataCleaner cleaner;
    // Pass the relative path to our Kaggle file
    cleaner.loadCSV("../data/train.csv"); 
    cleaner.removeOutliers();
    cleaner.printSummary();
    std::cout << "--- INGESTION COMPLETE ---\n\n";

    return 0; 
}