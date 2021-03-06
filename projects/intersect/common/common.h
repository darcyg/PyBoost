#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <assert.h>
#include <boost/format.hpp>
#include <boost/numpy.hpp>
#include <boost/python.hpp>
#include <fstream>

/*#include <boost/archive/text_oarchive.hpp>*/
/*#include <boost/archive/text_iarchive.hpp>*/
/*#include <boost/archive/binary_oarchive.hpp>*/
/*#include <boost/archive/binary_iarchive.hpp>*/
/*#include <boost/serialization/vector.hpp>*/

extern "C" {
#include "hiredis.h"
}

using namespace std;

namespace intersect {

    // Extract a set of features from an image

    class Keypoint {
        public:
            float x;
            float y;
            float scale;

            float scale1;
            float scale2;
            float scale3;

            float s1;
            float s2;
            float s3;
            float s4;
            float s5;
            float s6;

            /*float s7;*/
            /*float s8;*/
            /*float s9;*/
            /*float s10;*/

            //Keypoint() : Keypoint(0.0f, 0.0f, 0.0f) {}
            Keypoint() {
                x = 0.0f;
                y = 0.0f;
                scale = 0.0f;
            }

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

        private:
    };
    typedef std::vector<Keypoint> KeypointVector;

    // Holds Image Data
    // -----------------------------------
    class Image {
        public:
            int width;
            int height;
            uint8_t* data;

            const char* getCharData() {
                //return (char*)data;
                return (char*)data;
            }

            PyObject* getBuffer() {
                return PyBuffer_FromMemory((void*)data, width*height);
            }

            void saveToRedis(std::string key) {

                int database = 0;

                // Connect to Redis
                redisContext *m_context;
                m_context = redisConnect("127.0.0.1", 6379);

                // select DB
                redisReply *reply = (redisReply*) redisCommand(m_context, "SELECT %d", database);
                freeReplyObject(reply);

                // insert into DB
                reply = (redisReply*) redisCommand(m_context, "SET %b %b", key.c_str(), key.length(), (char*)data, width*height);
                 
            }

            //Image(int wwidth, int hheight) {
            Image(int wwidth, int hheight, boost::numpy::ndarray const &numpyData) {
                width = wwidth;
                height = hheight;
                getData(numpyData);
            } 

            void fuck() {
                //std::string str = (boost::format("X: %s, Y: %s, Scale: %s") % x % y % scale).str();
                
                data[3] = 100; 
            }

            ~Image() {}

        private:

            void getData(boost::numpy::ndarray const &numpyData) {
                if (numpyData.get_dtype() != boost::numpy::dtype::get_builtin<uint8_t>()) {
                    PyErr_SetString(PyExc_TypeError, "Incorrect array data type");
                    boost::python::throw_error_already_set();
                }
                /*
                if (numpyData.get_nd() != 2) {
                    PyErr_SetString(PyExc_TypeError, "Incorrect number of dimensions");
                    boost::python::throw_error_already_set();
                }
                */
                data = reinterpret_cast<uint8_t*>(numpyData.get_data());

                 
            }

    };


}  // namespace intersect

#endif  // COMMON_COMMON_H

