# 1. SET THE FOUNDATION
cmake_minimum_required(VERSION 3.10)
project(ObstacleClassificationPipeline)

# 2. ENFORCE THE C++ STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. LINK THE BLUEPRINTS
include_directories(include)

# 4. FIND PYBIND11 (This looks for the package we just installed via apt)
find_package(pybind11 REQUIRED)

# 5. BUILD THE PYTHON MODULE
# Instead of building an executable (.exe / binary), we build a Shared Object (.so)
# We name the module "sensor_engine" (this MUST match the name in bindings.cpp)
# We include the binding file, and all the C++ logic files it needs.
# Note: We do NOT include main.cpp anymore, because Python is our new "main"!
pybind11_add_module(sensor_engine 
    pybind_module/bindings.cpp 
    src/DataCleaner.cpp 
    src/Lidar.cpp
)