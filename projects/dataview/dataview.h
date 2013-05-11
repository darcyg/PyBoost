#ifndef DATAVIEW_DATAVIEW_H
#define DATAVIEW_DATAVIEW_H

#include <cinttypes>
#include <iostream>
#include <string>
#include <boost/format.hpp>

using namespace std;

namespace vfp {

    class Data {
        public:
            uint8_t* data; 
            int rows;
            int cols;

            Data() {}

            Data(uint8_t* _data, int _rows, int _cols) {
                data = _data;
                rows = _rows;
                cols = _cols;
            }

            Data(int _rows, int _cols) {
                rows = _rows;
                cols = _cols;
                data = new uint8_t[_rows*_cols]();

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        int index = i * cols + j;
                        data[index] = (uint8_t)index;
                    }
                } 
            };

            void print() {
                cout << "\n[" << endl;
                for (int i = 0; i < rows; i++) {
                    cout << "\t[ ";
                    for (int j = 0; j < cols; j++) {
                        int index = i * cols + j;
                        cout << boost::format("%d,\t") % (int)data[index];
                    }
                    cout << "],\n" << endl;
                }
                cout << "]" << endl;
            }
    };

    template <class T>
    class DataView {
        public:
            
            T* data;
            int rows;
            int cols;

            // view a Data object
            DataView(Data _data) {
                rows = _data.rows; 
                cols = _data.cols/sizeof(T);
                this->data = reinterpret_cast<T*>(_data.data);
            }

            Data getRawData() {
                int newRows = rows;
                int newCols = cols*sizeof(T);
                uint8_t* newData = reinterpret_cast<uint8_t*>(data);

                // TODO: Use memcpy or std::copy
                Data d = Data(newRows, newCols);
                for (int i = 0; i < newRows; i++) {
                    for (int j = 0; j < newCols; j++) {
                        int index = i * newCols + j;
                        d.data[index] = newData[index];
                    }
                } 

                return d;
            }

            // allocates mem 
            DataView(int _rows, int _cols) {
                rows = _rows;
                cols = _cols;
                data = new T[_rows*_cols]();
            };

            DataView(int _rows, int _cols, T defaultValue) {
                rows = _rows;
                cols = _cols;
                data = new T[_rows*_cols]();
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        int index = i * cols + j;
                        data[index] = index;
                    }
                } 
            };

            int get(int y, int x) {
                int index = x + y * cols;
                return data[index];
            }
            int get(int y) {
                int index = y * cols;
                return data[index];
            }

            // destructor 
            ~DataView() {
                delete data;
            };

            void print() {
                cout << "\n[" << endl;
                for (int i = 0; i < rows; i++) {
                    cout << "\t[ ";
                    for (int j = 0; j < cols; j++) {
                        int index = i * cols + j;
                        cout << boost::format("%d,\t") % data[index];
                    }
                    cout << "],\n" << endl;
                }
                cout << "]" << endl;
            }
    };

} // namespace vfp

#endif  // DATAVIEW_DATAVIEW_H
