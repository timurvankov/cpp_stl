#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class Matrix;

template<typename T>
class constMatrixIterator {
private:
    const Matrix<T>& matrix;
    size_t row, column;

public:
    constMatrixIterator(const Matrix<T>& m, size_t i, size_t j) : matrix(m), row(i), column(j) {}

    bool operator==(constMatrixIterator other) const {
        return row == other.row && column == other.column;
    }
    bool operator!=(constMatrixIterator other) const {
        return !(*this == other);
    }
    const T& operator*() const {
        return matrix[row][column];
    }
    constMatrixIterator& operator++() {
        ++column;
        if (column == matrix.size().second) {
            ++row;
            column = 0;
        }
        return *this;
    }
    const constMatrixIterator operator++(int) {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
};

template<typename T>
class MatrixIterator {
private:
    Matrix<T>& matrix;
    size_t row, column;

public:
    MatrixIterator(Matrix<T>& m, size_t i, size_t j) : matrix(m), row(i), column(j) {}

    bool operator==(MatrixIterator other) const {
        return row == other.row && column == other.column;
    }
    bool operator!=(MatrixIterator other) const {
        return !(*this == other);
    }
    T& operator*() {
        return matrix[row][column];
    }
    MatrixIterator& operator++() {
        ++column;
        if (column == matrix.size().second) {
            ++row;
            column = 0;
        }
        return *this;
    }
    const MatrixIterator operator++(int) {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
};

template<typename T>
class Matrix {
private:
    vector<vector<T>> matrix;

public:
    Matrix<T>() = default;
    Matrix<T>(const vector<vector<T>>& m) {
        matrix = m;
    }
    pair<size_t, size_t> size() const {
        if (matrix.size() == 0) {
            return {0, 0};
        }
        return {matrix.size(), matrix[0].size()};
    }

    constMatrixIterator<T> begin() const {
        return {*this, 0, 0};
    }
    constMatrixIterator<T> end() const {
        return {*this, this->size().first, 0};
    }
    MatrixIterator<T> begin() {
        return {*this, 0, 0};
    }
    MatrixIterator<T> end() {
        return {*this, this->size().first, 0};
    }
    const vector<T>& operator[](size_t i) const {
        return matrix[i];
    }
    vector<T>& operator[](size_t i) {
        return matrix[i];
    }
    Matrix<T>& operator+=(const Matrix<T>& n) {
        for (size_t i = 0; i != matrix.size(); ++i) {
            for (size_t j = 0; j != matrix[i].size(); ++j) {
                matrix[i][j] += n[i][j];
            }
        }
        return *this;
    }
    Matrix<T> operator+(const Matrix<T>& n) const {
        Matrix<T> ans = *this;
        return ans += n;
    }
    template <typename F>
    Matrix<T>& operator*=(const F& n) {
        size_t c = (*this).size().first;
        size_t r = (*this).size().second;
        for (size_t i = 0; i != c; ++i) {
            for (size_t j = 0; j != r; ++j) {
                (*this)[i][j] *= n;
            }
        }
        return *this;
    }
    template <typename F>
    Matrix<T> operator*(const F& n) const {
        Matrix<T> ans = *this;
        return ans *= n;
    }
    Matrix<T>& operator*=(const Matrix<T>& n) {
        size_t c = (*this).size().first;
        size_t r = n.size().second;
        size_t u = (*this).size().second;
        assert(u == n.size().first);
        Matrix<T> ans = Matrix<T>(vector<vector<T>>(c, vector<T>(r)));
        for (size_t i = 0; i != c; ++i) {
            for (size_t k = 0; k != u; ++k) {
                for (size_t j = 0; j != r; ++j) {
                    ans[i][j] += (*this)[i][k] * n[k][j];
                }
            }
        }
        *this = ans;
        return *this;
    }
    Matrix<T> operator*(const Matrix<T>& n) const {
        Matrix<T> ans = *this;
        return ans *= n;
    }

    Matrix<T>& transpose() {
        size_t c = (*this).size().first;
        size_t r = (*this).size().second;
        if (c > r) {
            for (vector<T>& v : matrix) {
                v.resize(c);
            }
        } else {
            matrix.resize(r);
            for (vector<T>& v : matrix) {
                v.resize(r);
            }
        }
        for (size_t i = 0; i != max(c, r); ++i) {
            for (size_t j = 0; j != i; ++j) {
                swap((*this)[i][j], (*this)[j][i]);
            }
        }
        if (c > r) {
            matrix.resize(r);
        } else {
            for (vector<T>& v : matrix) {
                v.resize(c);
            }
        }
        return *this;
    }
    Matrix<T> transposed() const {
        Matrix<T> ans = *this;
        return ans.transpose();
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
    for (size_t i = 0; i != m.size().first; ++i) {
        if (m.size().second != 0) {
            out << m[i][0];
        }
        for (size_t j = 1; j != m.size().second; ++j) {
            out << '\t' << m[i][j];
        }
        if (i + 1 != m.size().first) {
            out << '\n';
        }
    }
    return out;
}