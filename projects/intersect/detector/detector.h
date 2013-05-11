#ifndef DETECTOR_DETECTOR_H
#define DETECTOR_DETECTOR_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include "../common/common.h"

/*#include <boost/archive/text_oarchive.hpp>*/
/*#include <boost/archive/text_iarchive.hpp>*/
/*#include <boost/archive/binary_oarchive.hpp>*/
/*#include <boost/archive/binary_iarchive.hpp>*/
/*#include <boost/serialization/vector.hpp>*/

using namespace std;

namespace intersect {

    // Extract a set of features from an image

    class Detector {
        public:

            std::vector<Keypoint> keypoints;

            ~Detector() {}

            void fakeDetect(std::vector<Keypoint> &kps) {
                keypoints = kps;
            }

            void detect(Image &image) {
                //return detectKeypoints(image);
                // Fake it for now 
                for (int i = 0; i < 18; i+=3) {
                    float s = (float)i;
                    Keypoint k = Keypoint(s, s+1.0f, s+2.0f);
                    keypoints.push_back(k);
                }
            }


        private:
    };

}  // namespace pyboost

#endif  // DETECTOR_DETECTOR_H

