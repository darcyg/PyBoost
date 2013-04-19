#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <assert.h>
#include <boost/format.hpp>
#include <boost/numpy.hpp>

using namespace std;

namespace intersect {

    // Extract a set of features from an image

    class Keypoint {
        public:
            float x;
            float y;
            float scale;

            Keypoint(float xx, float yy, float sscale) {
                x = xx;
                y = yy;
                scale = sscale;
            }
            ~Keypoint() {}

            bool operator==(const Keypoint& other) const {
                return this->x == other.x
                    && this->y == other.y
                    && this->scale == other.scale;
            }

            std::string toString() const {
                std::string str = (boost::format("X: %s, Y: %s, Scale: %s") % x % y % scale).str();
                return str;
            }

            void print() const {
                std::cout << boost::format("Keypoint(%s)") % this->toString() << std::endl;
            }
    };
    typedef std::vector<Keypoint> KeypointVector;


    // Holds Image Data
    // -----------------------------------
    class Image {
        public:
            int width;
            int height;
            float* data;

            //Image(int wwidth, int hheight) {
            Image(int wwidth, int hheight, boost::numpy::ndarray const &numpyData) {
                width = wwidth;
                height = hheight;
                getData(numpyData);
            } 

            ~Image() {}

        private:

            void getData(boost::numpy::ndarray const &numpyData) {
                if (numpyData.get_dtype() != boost::numpy::dtype::get_builtin<double>()) {
                    PyErr_SetString(PyExc_TypeError, "Incorrect array data type");
                    boost::python::throw_error_already_set();
                }
                /*
                if (numpyData.get_nd() != 2) {
                    PyErr_SetString(PyExc_TypeError, "Incorrect number of dimensions");
                    boost::python::throw_error_already_set();
                }
                */
                data = reinterpret_cast<float*>(numpyData.get_data());
                 
            }

    };















}  // namespace intersect

#endif  // COMMON_COMMON_H

