#include <iostream>
#include <string>

#include <cinttypes>
#include "dataview.h"

using namespace std;
using namespace vfp;

int main() {
    cout << "Starting" << endl;

    //Data d = Data(12,24);
    //d.print();
   
    //DataView<uint32_t>* data = new DataView<uint32_t>(12, 6, 0);    
    //data->print();

    Data* d = new Data(8,16);
    d->print();

    DataView<uint32_t>* newData = (DataView<uint32_t>*)d;
    cout << newData->rows << endl;
    cout << newData->cols << endl;

    cout << "Done" << endl;
    return 0;
}
