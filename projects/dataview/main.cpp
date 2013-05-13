#include <iostream>
#include <string>

#include <cinttypes>
#include "dataview.h"
#include <boost/format.hpp>

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
    cout << newData->m_rows << endl;
    cout << newData->m_cols << endl;

    cout << "-------------" << endl;

    cout << newData->rows() << endl;
    cout << newData->cols() << endl;

    cout << "-------------" << endl;
    newData->print();

    cout << "-------------" << endl;
    cout << "Getting element 5, 3" << endl;
    cout << newData->get(5,3) << endl;

    cout << "-------------" << endl;
    cout << "Setting element 5, 3 to 50462976" << endl;
    newData->set(5,3, 50462976);

    cout << "-------------" << endl;
    cout << "Getting element 5, 3 again" << endl;
    cout << newData->get(5,3) << endl;

    cout << "-------------" << endl;
    newData->print();

    cout << "-------------" << endl;
    cout << "The Data object should also change" << endl;
    d->print();


    cout << "Done" << endl;
    return 0;
}
