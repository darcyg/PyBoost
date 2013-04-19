#ifndef DETECTOR_DETECTOR_H
#define DETECTOR_DETECTOR_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <assert.h>
#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include "../common/common.h"

using namespace std;

namespace intersect {

    // Extract a set of features from an image

    class Detector {
        public:

            ~Detector() {}
            static std::vector<Keypoint> detect(Image &image) {
                //return detectKeypoints(image);
                // Fake it for now 
                std::vector<Keypoint> keypoints;
                for (int i = 0; i < 18; i+=3) {
                    float s = (float)i;
                    Keypoint k = Keypoint(s, s+1.0f, s+2.0f);
                    keypoints.push_back(k);
                }
                return keypoints;
            }

        private:

            static std::vector<Keypoint>& detectKeypoints(Image &image) {

            }

    };

}  // namespace pyboost

#endif  // DETECTOR_DETECTOR_H

