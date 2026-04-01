#pragma once // Prevents the compiler from including this header file multiple times, avoiding redefinition errors.
#include <iostream>
#include <string>

// Abstract Base Class: Acts as a strict blueprint for all future sensor types.
class Sensor{

// Protected means these variables are hidden from the outside world (like main.cpp), 
// but fully accessible to any child class (like Lidar or Radar) that inherits from Sensor
protected:
    std::string sensorID;
    bool isActive;

public:
    // Constructor with a Member Initializer List. 
    // It assigns the ID and sets the sensor to active BEFORE the object is fully created (highly optimized).
    Sensor(std::string sensing_identifier):sensorID(sensing_identifier), isActive(true)
    {}

    // Pure Virtual Function (= 0). Forces any derived class to write its own logic for loading data.
    // The Sensor class itself doesn't know how to load data, it just demands that its children do.
    virtual void loadRawData() = 0;

    // Pure Virtual Function (= 0). Forces any derived class to write its own specific noise filtering logic.
    virtual void applyNoiseFilter() = 0;

    // Virtual Destructor. Crucial for memory safety when deleting derived objects through a base class pointer.
    virtual ~Sensor() {};


};
