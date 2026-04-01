#pragma once // Prevents the compiler from including this header file multiple times, avoiding redefinition errors.
#include <iostream>
#include <string>
#include "Sensor.h" // Crucial: We must include the parent blueprint to inherit from it.

// Lidar publicly inherits from Sensor. 
// It automatically gets 'sensorID' and 'isActive' from the parent class.
class Lidar : public Sensor {

private:
    // Lidar-specific attributes. Encapsulated to prevent outside tampering.
    float maxRange;
    int numLasers;

public: 
    // Constructor: Catches the 'id' and passes it up to the parent Sensor constructor immediately.
    // Then it uses the Member Initializer List to set its own specific variables highly efficiently.
    Lidar(std::string id, float range, int lasers) : Sensor(id), maxRange(range), numLasers(lasers) {}

    // Fulfilling the Contract: We MUST override the pure virtual functions from the Sensor class.
    // The 'override' keyword forces the compiler to double-check our spelling against the parent class.
    void loadRawData() override;
    void applyNoiseFilter() override;

    // Destructor: Overriding the parent's virtual destructor.
    // This ensures that when a Lidar is deleted via a Sensor pointer, Lidar's memory cleans up first.
    ~Lidar() override;
};