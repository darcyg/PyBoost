#ifndef PYBOOST_COMMON_H
#define PYBOOST_COMMON_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <assert.h>
#include <boost/format.hpp>

using namespace std;

namespace Pyboost {

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

            std::string toString() const {
                std::string str = (boost::format("X: %s, Y: %s, Scale: %s") % x % y % scale).str();
                return str;
            }

            void print() const {
                std::cout << boost::format("Keypoint(%s)") % this->toString() << std::endl;
            }
    };
    typedef std::vector<Keypoint> KeypointVector;

    // Descriptor information
    class Descriptor {

        public:
            // TODO: convert this to vector
            std::vector<float> values;

            std::string toString() const {
                //std::string str = (boost::format("X: %s, Y: %s, Scale: %s") % x % y % scale).str();

                std::string str = (boost::format("Length = %s, Values = [ ") % values.size()).str();
                for(int i = 0; i < values.size(); i++) {
                    str += (boost::format("%s, ") % values[i]).str();
                }
                str += "]";
                return str;
            }

            void print() const {
                std::cout << boost::format("Descriptor(%s)") % this->toString() << std::endl;
            }
    };
    typedef std::vector<Keypoint> DescriptorContainer;

}  // namespace pyboost

#endif  // PYBOOST_COMMON_H

