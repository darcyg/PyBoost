#ifndef DATAVIEW_DATAVIEW_H
#define DATAVIEW_DATAVIEW_H

#include <cinttypes>
#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <stdexcept>      // std::out_of_range

#define VFP_INTEGER 0
#define VFP_DECIMAL 1

#define VFP_8 1
#define VFP_16 2
#define VFP_32 4
#define VFP_64 8

using namespace std;

namespace vfp {

    struct MatData {
        int rows;         // number of rows
        int cols;         // number of colums 
        int dtype;        // stores the dtype of the matrix (VFP_INTEGER or VFP_DECIMAL)
        int bytes;        // stores the dtype of the matrix, similar to cv::Mat
    };

    class Mat {

        public:
            Mat(int rows, int cols, int dtype, int bytes) {
                m_meta.rows = rows;
                m_meta.cols = cols;
                m_meta.dtype = dtype;
                m_meta.bytes = bytes;
                m_data = new uint8_t[rows*cols*bytes]();
            }

            ~Mat() { delete m_data; }

            // gets rows/cols in the given "template context"
            template<typename T> int rows() { return m_meta.rows; }
            template<typename T> int cols() { return (m_meta.cols * m_meta.bytes)/sizeof(T); }

            // Mimic the cv::Mat way of accessing specific element
            template<typename T> 
            T& at(int y, int x) {
                checkDimensions<T>(y,x);
                T* d = view<T*>();
                int index = x + y * cols<T>();
                return d[index];
            }

            // casts by the template arg
            template<typename T> T view() { return reinterpret_cast<T>(m_data); }

            // print the data
            template<typename T>
            void print() {
                T* data = view<T*>();
                int rowSize = rows<T>();
                int colSize = cols<T>();

                cout << "\n[" << endl;
                for (int i = 0; i < rowSize; i++) {
                    cout << "\t[ ";
                    for (int j = 0; j < colSize; j++) {
                        int index = i * colSize + j;
                        cout << boost::format("%s,\t") % (int)data[index];
                    }
                    cout << "],\n" << endl;
                }
                cout << "]" << endl;
            }

        protected:
            // instance vars
            uint8_t* m_data;    // char array that stores data of every kind
            MatData m_meta;     // contains other metadata. See struct MatData

            // check if the row and column index is valid
            template<typename T> void checkDimensions(int y, int x) {
                int maxRowIndex = rows<T>() - 1; int maxColIndex = cols<T>() - 1;
                if (y > maxRowIndex) { throw std::out_of_range((boost::format("vfp::Mat row index out of bounds: %d > %d") % y % maxRowIndex).str()); }
                if (x > maxColIndex) { throw std::out_of_range((boost::format("vfp::Mat col index out of bounds: %d > %d") % x % maxColIndex).str()); }
            }
    };

} // namespace vfp

#endif  // DATAVIEW_DATAVIEW_H
