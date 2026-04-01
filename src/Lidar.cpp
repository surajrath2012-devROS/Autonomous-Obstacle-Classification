#include <iostream>
#include "../include/Lidar.h"

void Lidar::loadRawData()
{
    std::cout << "[LIDAR] Loading 3D point cloud data for sensor: " << sensorID << std::endl;
};

void Lidar::applyNoiseFilter()
{
    std::cout << "[LIDAR] Filtering ghost points based on max range of " << maxRange << " meters." << std::endl;

}

Lidar::~Lidar()
{
    std::cout << "[LIDAR] Shutting down and cleaning memory for: " << sensorID << std::endl;

}