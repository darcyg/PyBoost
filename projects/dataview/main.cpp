#include <iostream>
#include <string>

#include <cinttypes>
#include "dataview.h"
#include <boost/format.hpp>

using namespace std;
using namespace vfp;

int main() {
    cout << "Starting" << endl;

    Mat* d = new Mat(8,16);
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

    cout << "Done" << endl;
    return 0;
}
