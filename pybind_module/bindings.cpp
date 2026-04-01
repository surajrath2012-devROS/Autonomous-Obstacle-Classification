#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // This is MAGIC. It automatically converts C++ std::vector into Python Lists!
#include "../include/DataCleaner.h"

namespace py = pybind11;

// "sensor_engine" is the name of the module we will import in Python.
PYBIND11_MODULE(sensor_engine, m) {
    m.doc() = "C++ Backend for Autonomous Obstacle Classification";

    // 1. Bind the BoundingBox Struct
    // This tells Python what a BoundingBox is and lets Python read its variables.
    py::class_<BoundingBox>(m, "BoundingBox")
        .def_readonly("x", &BoundingBox::x)
        .def_readonly("y", &BoundingBox::y)
        .def_readonly("z", &BoundingBox::z)
        .def_readonly("width", &BoundingBox::width)
        .def_readonly("length", &BoundingBox::length)
        .def_readonly("height", &BoundingBox::height)
        .def_readonly("objectClass", &BoundingBox::objectClass);

    // 2. Bind the DataCleaner Class
    // This exposes our C++ functions so Python can call them like normal methods.
    py::class_<DataCleaner>(m, "DataCleaner")
        .def(py::init<>()) // Binds the default constructor
        .def("loadCSV", &DataCleaner::loadCSV, "Load the Kaggle CSV file")
        .def("removeOutliers", &DataCleaner::removeOutliers, "Clean the data")
        .def("getDataset", &DataCleaner::getDataset, "Return the clean data to Python");
}