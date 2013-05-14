#ifndef DATAVIEW_DATAVIEW_H
#define DATAVIEW_DATAVIEW_H

#include <cinttypes>
#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <stdexcept>      // std::out_of_range

using namespace std;

namespace vfp {

    class Mat {
        public:
            uint8_t* data; 
            int rows;
            int cols;

            Mat() {}

            // init data with stuff
            Mat(uint8_t* _data, int _rows, int _cols) {
                data = _data;
                rows = _rows;
                cols = _cols;
            }

            // init data and fill in each cell with its index
            Mat(int _rows, int _cols) {
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

            // Mimic the cv::Mat way of accessing specific element
            template<typename T> 
            T& at(int y, int x) {
                checkDimensions<T>(y,x);
                T* d = view<T*>();
                int index = x + y * (cols/sizeof(T));
                return d[index];
            }

            // casts by the template arg
            template<typename T>
            T view() {
                return reinterpret_cast<T>(data);
            }

            // print the data
            template<typename T>
            void print() {
                T* m_data = view<T*>();
                int m_rows = rows;
                int m_cols = cols/sizeof(T);

                cout << "\n[" << endl;
                for (int i = 0; i < m_rows; i++) {
                    cout << "\t[ ";
                    for (int j = 0; j < m_cols; j++) {
                        int index = i * m_cols + j;
                        cout << boost::format("%s,\t") % (int)m_data[index];
                    }
                    cout << "],\n" << endl;
                }
                cout << "]" << endl;
            }
        protected:
            template<typename T> void checkDimensions(int y, int x) {
                // check if the row and column index is valid
                int maxRowIndex = rows - 1;
                int maxColIndex = cols/sizeof(T) - 1;

                if (y > maxRowIndex) { throw std::out_of_range((boost::format("vfp::Mat row index out of bounds: %d > %d") % y % maxRowIndex).str()); }
                if (x > maxColIndex) { throw std::out_of_range((boost::format("vfp::Mat col index out of bounds: %d > %d") % x % maxColIndex).str()); }
            }
    };

} // namespace vfp

#endif  // DATAVIEW_DATAVIEW_H
