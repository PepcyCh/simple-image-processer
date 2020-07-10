#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>

template <typename T>
class Mat {
  public:
    Mat(size_t rs = 1, size_t cs = 1, T filled = static_cast<T>(0)) : rs(rs), cs(cs) {
        data = new T[rs * cs];
        std::fill(data, data + rs * cs, filled);
    }
    ~Mat() {
        delete[] data;
    }

    Mat(const Mat<T> &rhs) {
        rs = rhs.rs;
        cs = rhs.cs;
        data = new T[rs * cs];
        std::copy(rhs[0], rhs[0] + rs * cs, data);
    }

    Mat &operator=(const Mat<T> &rhs) {
        rs = rhs.rs;
        cs = rhs.cs;
        T *p_new = new T[rs * cs];
        std::copy(rhs[0], rhs[0] + rs * cs, p_new);
        delete[] data;
        data = p_new;
        return *this;
    }

    void Create(size_t rs, size_t cs, T filled = static_cast<T>(0)) {
        this->rs = rs;
        this->cs = cs;
        delete[] data;
        data = new T[rs * cs];
        std::fill(data, data + rs * cs, filled);
    }

    size_t Rows() const { return rs; }
    size_t Cols() const { return cs; }

    T *operator[](size_t i) { return data + i * cs; }
    const T *operator[](size_t i) const { return data + i * cs; }

    Mat operator+(const Mat<T> &rhs) const {
        if (rs != rhs.Rows() || cs != rhs.Cols()) {
            return *this;
        }
        Mat<T> res(rs, cs, 0);
        for (int i = 0; i < rs; i++) {
            for (int j = 0; j < cs; j++) {
               res = (*this)[i][j] + rhs[i][j];
            }
        }
        return res;
    }
    Mat operator-(const Mat<T> &rhs) const {
        if (rs != rhs.Rows() || cs != rhs.Cols()) {
            return *this;
        }
        Mat<T> res(rs, cs, 0);
        for (int i = 0; i < rs; i++) {
            for (int j = 0; j < cs; j++) {
               res = (*this)[i][j] - rhs[i][j];
            }
        }
        return res;
    }
    Mat operator*(const Mat<T> &rhs) const {
        if (cs != rhs.Rows()) {
            return *this;
        }
        Mat<T> res(rs, rhs.Cols(), 0);
        for (int i = 0; i < rs; i++) {
            for (int j = 0; j < cs; j++) {
                for (int k = 0; k < rhs.cs; k++) {
                    res[i][k] += (*this)[i][j] * rhs[j][k];
                }
            }
        }
        return res;
    }

    Mat operator*(T scale) const {
        Mat<T> res(rs, cs);
        for (int i = 0; i < rs; i++) {
            for (int j = 0; j < cs; j++) {
               res[i][j] = (*this)[i][j] * scale;
            }
        }
        return res;
    }
    Mat operator/(T scale) const {
        if (scale == 0) {
            return *this;
        }
        Mat<T> res(rs, cs);
        for (int i = 0; i < rs; i++) {
            for (int j = 0; j < cs; j++) {
               res[i][j] = (*this)[i][j] / scale;
            }
        }
        return res;
    }

    Mat Transposed() const {
        Mat<T> res(cs, rs);
        for (int i = 0; i < rs; i++) {
            for (int j = 0; j < cs; j++) {
               res[j][i] = (*this)[i][j];
            }
        }
        return res;
    }

  private:
    size_t rs, cs;
    T *data = nullptr;
};