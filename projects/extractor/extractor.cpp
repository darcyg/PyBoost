#include <boost/python.hpp>
#include "boost/numpy.hpp"
#include <boost/python/numeric.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "keypoint.h"

using namespace std;
using namespace boost::python;

using Pyboost::Keypoint;
using Pyboost::KeypointVector;

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

BOOST_PYTHON_MODULE(extractor)
{
    //using namespace boost::python;
    //boost::python::numeric::array::set_module_and_type("numpy", "ndarray");

    def("extract", &blah);

    // class Keypoint
    class_<Keypoint>("Keypoint", init<float, float, float>())
        .def_readwrite("x", &Keypoint::x)
        .def_readwrite("y", &Keypoint::y)
        .def_readwrite("scale", &Keypoint::scale)
        .def("__repr__", &Keypoint::toString)
        ;
}
