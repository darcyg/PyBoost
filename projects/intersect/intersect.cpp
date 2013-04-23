#include <boost/python.hpp>
#include "boost/numpy.hpp"
#include <boost/python/numeric.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "common/common.h"
#include "detector/detector.h"
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
using namespace boost::python;

using intersect::Keypoint;
using intersect::Image;

using intersect::Detector;

BOOST_PYTHON_MODULE(intersect)
{
    //using namespace boost::python;
    //boost::python::numeric::array::set_module_and_type("numpy", "ndarray");

    boost::numpy::initialize();  // have to put this in any module that uses Boost.NumPy

    // class Keypoint
    class_<Keypoint>("Keypoint", init<float, float, float>())
        .def_readwrite("x", &Keypoint::x)
        .def_readwrite("y", &Keypoint::y)
        .def_readwrite("scale", &Keypoint::scale)
        .def("__repr__", &Keypoint::toString)
        ;

    // class Image
    class_<Image>("Image", init<int, int, const boost::numpy::ndarray&>())
        .def_readwrite("width", &Image::width)
        .def_readwrite("height", &Image::height)
        .def_readwrite("data", &Image::data)
        .def("fuck", &Image::fuck)
        .def("getData", &Image::getCharData)
        .def("getBuffer", &Image::getBuffer)
        .def("saveToRedis", &Image::saveToRedis)
        ;

    class_<std::vector<Keypoint> >("KeypointVector")
        .def(vector_indexing_suite<std::vector<Keypoint> >())
        ;

    // class Detector
    class_<Detector>("Detector")
        .def("detect", &Detector::detect)
        .def("fake_detect", &Detector::fakeDetect)
        .def("loadKeypoints", &Detector::loadKeypoints)
        .def("saveKeypoints", &Detector::saveKeypoints)
        .def_readwrite("keypoints", &Detector::keypoints)
        ;
}
