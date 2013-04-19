#include <boost/python.hpp>
#include "boost/numpy.hpp"
#include <boost/python/numeric.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "common/common.h"
#include "detector/detector.h"

using namespace std;
using namespace boost::python;

using intersect::Keypoint;
using intersect::Image;

using intersect::Detector;

// gets keypoints, returns descriptors 
void blah(boost::python::list &keypoints)
{
    for (int i = 0; i < boost::python::len(keypoints); i++) {
        Keypoint &keypoint = boost::python::extract<Keypoint&>(keypoints[i]);
        //--------------------------------------------

        keypoint.x += 1.0f;         
        keypoint.y += 1.0f;         
        keypoint.scale += 1.0f;         

        //--------------------------------------------
    } 
}

BOOST_PYTHON_MODULE(intersect)
{
    //using namespace boost::python;
    //boost::python::numeric::array::set_module_and_type("numpy", "ndarray");

    boost::numpy::initialize();  // have to put this in any module that uses Boost.NumPy
    def("extract", &blah);

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
        ;

    class_<std::vector<Keypoint> >("KeypointVector")
        .def(vector_indexing_suite<std::vector<Keypoint> >())
        ;

    // class Detector
    class_<Detector>("Detector")
        .def("detect", &Detector::detect)
        .staticmethod("detect")
        ;
}
