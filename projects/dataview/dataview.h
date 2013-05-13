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
            int m_rows;
            int m_cols;

            Data() {}

            // init data with stuff
            Data(uint8_t* _data, int _rows, int _cols) {
                data = _data;
                m_rows = _rows;
                m_cols = _cols;
            }

            // init data and fill in each cell with its index
            Data(int _rows, int _cols) {
                m_rows = _rows;
                m_cols = _cols;
                data = new uint8_t[_rows*_cols]();

                for (int i = 0; i < m_rows; i++) {
                    for (int j = 0; j < m_cols; j++) {
                        int index = i * m_cols + j;
                        data[index] = (uint8_t)index;
                    }
                } 
            };

            // print the data
            void print() {
                cout << "\n[" << endl;
                for (int i = 0; i < m_rows; i++) {
                    cout << "\t[ ";
                    for (int j = 0; j < m_cols; j++) {
                        int index = i * m_cols + j;
                        cout << boost::format("%d,\t") % (int)data[index];
                    }
                    cout << "],\n" << endl;
                }
                cout << "]" << endl;
            }
    };

    template <class T>
    class DataView : public Data {
        public:

            int cols() { return m_cols/sizeof(T); }
            int rows() { return m_rows; }
            void rows(int y) { m_rows = y; }
            void cols(int x) { m_cols = x; }

            T* view() {
                return reinterpret_cast<T*>(data);
            }

            int get(int y, int x) {
                T* m_data = view();
                int index = x + y * cols();
                return m_data[index];
            }
            int get(int y) {
                T* m_data = view();
                int index = y * cols();
                return m_data[index];
            }
            int set(int y, int x, T value) {
                T* m_data = view();
                int index = x + y * cols();
                m_data[index] = value;
            }

            void print() {
                T* m_data = view();

                cout << "\n[" << endl;
                for (int i = 0; i < rows(); i++) {
                    cout << "\t[ ";
                    for (int j = 0; j < cols(); j++) {
                        int index = i * cols() + j;
                        cout << boost::format("%d,\t") % m_data[index];
                    }
                    cout << "],\n" << endl;
                }
                cout << "]" << endl;
            }
    };

} // namespace vfp

#endif  // DATAVIEW_DATAVIEW_H
