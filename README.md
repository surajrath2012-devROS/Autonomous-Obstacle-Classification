Autonomous Obstacle Classification Pipeline
A high-performance, memory-safe sensor fusion and classification pipeline built for autonomous vehicle data. This project demonstrates a production-grade hybrid architecture, utilizing C++ for high-speed data ingestion and Python for Machine Learning and 3D visualization.

Architecture Overview
Processing millions of LiDAR data points purely in Python introduces severe latency due to the Global Interpreter Lock (GIL) and dynamic typing overhead. This project solves that bottleneck by delegating the heavy I/O and memory management to a compiled C++ engine, which feeds clean data directly into Python memory via PyBind11.

1. The C++ Backend (Sensor Engine)
Object-Oriented Design: Implements a polymorphic class structure (Sensor base class extended by Lidar).

Memory Safety: Utilizes std::unique_ptr and virtual destructors to ensure dynamic dispatch and deterministic memory cleanup without manual delete operations.

Data Parsing: Reads and cleans over 630,000 unstructured strings from Kaggle autonomous datasets using optimized std::stringstream logic.

Performance Benchmark: Parses, cleans, and structures 638,179 bounding boxes in ~2.2 seconds.

2. The PyBind11 Bridge
Compiles the C++ engine into a Python-accessible Shared Object (.so).

Allows Python to directly invoke C++ class methods and retrieve std::vector data as native Python lists, eliminating disk I/O latency during the handoff.

3. The Python Frontend (ML & Visualization)
Machine Learning: Utilizes a RandomForestClassifier (Scikit-Learn) to categorize 3D objects (Car, Pedestrian, Truck, Bus) based on raw physical dimensions (width, length, height).

3D Rendering: Features a custom Matplotlib visualization dashboard. It calculates the 8 spatial corners of each bounding box and renders a localized 3D environment relative to the ego-vehicle.

Core Concepts Utilized
C++17: Polymorphism, Encapsulation, Smart Pointers, File Streams, Pass-by-Reference.

Build Systems: CMake for generating OS-specific build scripts and linking PyBind11.

Data Science: Pandas for tabular data manipulation, Scikit-Learn for ensemble modeling, handling data leakage and overfitting.

3D Geometry: Matrix transformations and spatial rendering.

Project Structure
Plaintext
├── CMakeLists.txt         # Master build script
├── include/               # C++ Header files (.h)
│   ├── DataCleaner.h
│   ├── Lidar.h
│   └── Sensor.h
├── src/                   # C++ Implementation files (.cpp)
│   ├── DataCleaner.cpp
│   └── Lidar.cpp
├── pybind_module/         # PyBind11 wrapper logic
│   └── bindings.cpp
├── python_scripts/        # Python ML and Visualization
│   ├── train_model.py
│   └── visualize_3d.py
└── data/                  # Target directory for the raw dataset
How to Run
1. Install Dependencies

Bash
sudo apt update
sudo apt install cmake pybind11-dev python3-pybind11 python3-dev
sudo apt install python3-pandas python3-sklearn python3-matplotlib python3-numpy
2. Build the C++ Engine

Bash
mkdir build
cd build
cmake ..
make
3. Run the ML Pipeline or Visualization

Bash
python3 train_model.py
# or
python3 visualize_3d.py
Note: You must supply your own train.csv from the Lyft 3D Object Detection Kaggle dataset and place it in the /data directory.
