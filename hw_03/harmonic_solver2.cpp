#include <iostream>
#include <vector>
#include <stdexcept>

double const pi = 3.14;
// Parametr of differential equation
double const omega2 = 1.0;
bool const DEBUG = 0;

template <typename T>
class Matrix {
private:
    T** mat;
    size_t N, M;

public:
    Matrix(size_t N_, size_t M_);
    Matrix(const Matrix& lhs);
    ~Matrix();

    friend T& operator[](size_t idy, size_t idx);

    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
};

template <typename T>
Matrix<T>::Matrix(size_t N_, size_t M_): N(N_), M(M_) {
    mat = new T*[N];
    for (size_t i = 0; i < N; i++) {
        mat[i] = new T[M];
        for (size_t j = 0; j < M; j++) {
            mat[i][j] = static_cast<T>(0);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& lhs): N(lhs.N), M(lhs.M) {
    mat = new T*[N];
    for (size_t i = 0; i < N; i++) {
        mat[i] = new T[M];
        for (size_t j = 0; j < M; j++) {
            mat[i][j] = lhs[i, j];
        }
    }
}
template <typename T>
T& Matrix<T>::operator[](size_t idy, size_t idx) {
    return mat[idy][idx];
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.N != rhs.N || lhs.M != rhs.M) {
        throw std::runtime_error("Uncomparable size!");
    }

    Matrix t(lhs);
    for (size_t i = 0; i < t.N; i++) {
        for (size_t j = 0; j < t.M; j++) {
            t[i, j] += rhs[i, j];
        }
    }

    return t;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.N != rhs.N || lhs.M != rhs.M) {
        throw std::runtime_error("Uncomparable size!");
    }

    Matrix t(lhs);
    for (size_t i = 0; i < t.N; i++) {
        for (size_t j = 0; j < t.M; j++) {
            t[i, j] -= rhs[i, j];
        }
    }

    return t;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.M != rhs.N) {
        throw std::runtime_error("Uncomparable size!");
    }

    Matrix t(lhs.N, rhs.M);
    for (size_t i = 0; i < t.N; i++) {
        for (size_t j = 0; j < t.M; j++) {
            T val = 0;
            for (size_t k = 0; k < lhs.M; k++) {
                val += lhs[i, k] * rhs[k, j];
            }

            t[i, j] = val;
        }
    }

    return t;
}

template <typename T>
Matrix<T>::~Matrix() {
        for (size_t i = 0; i < N; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }

int main() {
    Matrix<int> m(2, 2);
    std::cout << m[0, 0];

    return 0;
}
