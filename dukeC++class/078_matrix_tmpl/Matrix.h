#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows.resize(r);
    T a;
    for (int i = 0; i < r; ++i) {
      // rows[i].resize(c);
      // if ((int)rows[i].size() != c) {
      for (int j = 0; j < c; ++j) {
        rows[i].push_back(a);
        // }
      }
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}
  ~Matrix() {}
  Matrix & operator=(const Matrix & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(-1 < index && index < this->getRows());
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(-1 < index && index < this->getRows());
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    for (unsigned int i = 0; i < rows.size(); ++i) {
      for (unsigned int j = 0; j < rows[i].size(); ++j) {
        if (rows[i][j] != rhs.rows[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix temp(*this);
    for (unsigned int i = 0; i < rows.size(); ++i) {
      for (unsigned int j = 0; j < rows[i].size(); ++j) {
        temp[i][j] += rhs[i][j];
      }
    }
    return temp;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() < 1) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; ++i) {
    s << "{";
    for (int j = 0; j < rhs.getColumns() - 1; ++j) {
      s << rhs[i][j] << ", ";
    }
    s << rhs[i][rhs.getColumns() - 1];
    s << "},\n";
  }
  s << "{";
  for (int j = 0; j < rhs.getColumns() - 1; ++j) {
    s << rhs[rhs.getRows() - 1][j] << ", ";
  }
  s << rhs[rhs.getRows() - 1][rhs.getColumns() - 1];
  s << "} ]";
  return s;
}

#endif
