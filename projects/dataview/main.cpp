#include <iostream>
#include <string>

#include <cinttypes>
#include "dataview.h"
#include <boost/format.hpp>

using namespace std;
using namespace vfp;

void initMat(Mat* d) {
    for (int i = 0; i < d->rows<uint32_t>(); i++) {
        for (int j = 0; j < d->cols<uint32_t>(); j++) {
            d->at<uint32_t>(i, j) = i * d->cols<uint32_t>() + j;
        }
    } 
}

int main() {
    cout << "Starting\n" << endl;
    // ---------------------------------------------------------------------

    //Mat* d = new Mat(7, 5, 0, 4);
    Mat* d = new Mat(7, 5, VFP_INTEGER, VFP_32);

    initMat(d);

    d->print<uint8_t>();
    d->print<uint32_t>();

    cout << "\n-------------------------------" << endl;
    cout << "Getting element 5,3 as uint32_t" << endl;
    cout << d->at<uint32_t>(5,3) << endl;

    cout << "\n-------------------------------" << endl;
    cout << "Getting element 3,2 as uint32_t" << endl;
    cout << d->at<uint32_t>(3,2) << endl;

    cout << "\n-------------------------------" << endl;
    cout << "Setting element 3,2 as uint32_t" << endl;
    d->at<uint32_t>(3,2) = 7;

    d->print<uint32_t>();

    delete d;

    // ---------------------------------------------------------------------
    cout << "\nDone\n" << endl;
    return 0;
}
