#ifndef DETECTOR_DETECTOR_H
#define DETECTOR_DETECTOR_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <ios>
#include <fstream>
#include <assert.h>
#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include "../common/common.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;

namespace intersect {

    // Extract a set of features from an image

    class Detector {
        public:

            std::vector<Keypoint> keypoints;

            ~Detector() {}
            void detect(Image &image) {
                //return detectKeypoints(image);
                // Fake it for now 
                for (int i = 0; i < 18; i+=3) {
                    float s = (float)i;
                    Keypoint k = Keypoint(s, s+1.0f, s+2.0f);
                    keypoints.push_back(k);
                }
            }

            void saveKeypoints(string filename) {
                cout << "Saving Keypoints to file " << filename << endl;
                std::ofstream f(filename.c_str(), std::ios::binary);
                boost::archive::binary_oarchive oa(f);

                // save class state to archive
                //oa << keypoints;
            }

            void loadKeypoints(string filename) {
                cout << "Loading Keypoints from file " << filename << endl;
                std::ifstream ifs(filename.c_str(), std::ios::binary);
                //boost::archive::binary_iarchive ia(ifs);

                // read class state from archive
                //ia >> keypoints;
            }

            /*
            void saveKeypoints(string filename) {
                std::ofstream f(filename.c_str(), std::ios::binary);
                boost::archive::binary_oarchive oa(f);

                // save class state to archive
                oa << keypoints;
            }

            void loadKeypoints(string filename) {
                std::ifstream ifs(filename.c_str(), std::ios::binary);
                boost::archive::binary_iarchive ia(ifs);

                // read class state from archive
                ia >> keypoints;
            }
            */

        private:
            friend class boost::serialization::access;
            template <typename Archive> void serialize(Archive &ar, const unsigned int version) {
                ar & keypoints;
            }

    };

}  // namespace pyboost

namespace boost {
namespace serialization {
    template <class Archive> void serialize(Archive & ar, intersect::Keypoint & k, const unsigned int version) {
        ar & k.x;
        ar & k.y;
        ar & k.scale;
    }


    
}
}

#endif  // DETECTOR_DETECTOR_H

