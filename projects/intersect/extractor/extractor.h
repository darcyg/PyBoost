#ifndef EXTRACTOR_EXTRACTOR_H
#define EXTRACTOR_EXTRACTOR_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "../common/common.h"

#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <boost/shared_ptr.hpp>

/*#include <boost/archive/text_oarchive.hpp>*/
/*#include <boost/archive/text_iarchive.hpp>*/
/*#include <boost/archive/binary_oarchive.hpp>*/
/*#include <boost/archive/binary_iarchive.hpp>*/
/*#include <boost/serialization/vector.hpp>*/

using namespace std;
namespace p = boost::python;
namespace np = boost::numpy;

namespace intersect {

    // Extract a set of features from an image
    const int FEATURE_DIMENSION = 10;

    class Extractor {
        public:
            //typedef uint8_t dtype;
            typedef float dtype;

            dtype* features;
            int numFeatures;

            dtype mul_data[3][4];

            Extractor() {
                np::initialize();
                Py_Initialize();
                for (int i = 1; i <= 3; i++) {
                    for (int j = 1; j <= 4; j++) {
                        mul_data[i-1][j-1] = (dtype)(i * j);
                    }
                }
            }
            ~Extractor() {
                delete features;
            }

            // Extracts and populates dtype* features
            void extract(std::vector<Keypoint> &keypoints) {
                numFeatures = keypoints.size();

                cout << boost::format("Extracting from %s keypoints") % numFeatures << endl;

                const int x = numFeatures;
                const int y = FEATURE_DIMENSION;

                features = new dtype[x*y];

                for (int i = 0; i < numFeatures; i++) {
                    for (int j = 0; j < FEATURE_DIMENSION; j++) {
                        features[i*FEATURE_DIMENSION + j] = (dtype)(i + j);
                        cout << features[i*FEATURE_DIMENSION + j] << "\t";
                    }
                    cout << endl;
                }
            }

            void fuckWithFeatures() {
                features[FEATURE_DIMENSION + 1] = (dtype)1000;
            }

            // wraps dtype* features into numpy array
            np::ndarray getFeatures() {

                const int xSize = numFeatures;
                const int ySize = FEATURE_DIMENSION;

                cout << "Dtype* Features: " << endl;
                cout << "------------------------------" << endl;
                for (int i = 0; i < numFeatures; i++) {
                    for (int j = 0; j < FEATURE_DIMENSION; j++) {
                        cout << features[i*FEATURE_DIMENSION + j] << "\t";
                    }
                    cout << endl;
                }
                cout << "------------------------------" << endl;

                // Now let's create an array of 3x2 elements, picking the first and third elements from each row
                // For that, the shape will be 3x2
                p::tuple shape = p::make_tuple(xSize,ySize) ;
                // The strides will be 4x2 i.e. 4 bytes to go to the next desired row, and 2 bytes to go to the next desired column

                int x = sizeof(dtype)*ySize;
                int y = sizeof(dtype);
                p::tuple stride = p::make_tuple(x,y) ; 

                //cout << boost::format("Stride(%s, %s)") % x % y << endl;
                cout << endl;

                // Get the numpy dtype for the built-in 8-bit integer data type
                np::dtype dt1 = np::dtype::get_builtin<dtype>();

                // First lets create and print out the ndarray as is
                np::ndarray mul_data_ex = np::from_data(features, dt1, shape, stride, p::object());
                std::cout << "C++" << std::endl << "--------------------------------\n" << p::extract < char const * > (p::str(mul_data_ex)) << std::endl ;

                return mul_data_ex;
            }

            std::string saveFeatures() {
                cout << "Saving Features" << endl;
                return "Blah";
                
            }

            void loadFeatures(std::string load) {
                cout << "Loading Features" << endl;
            }

        private:

    };

}  // namespace pyboost

#endif  // EXTRACTOR_EXTRACTOR_H

