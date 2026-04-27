#include <cstddef>
#include <iostream>
#include <stdexcept>

using namespace std;

struct Complex {
    double real = 0, img = 0;

    Complex operator + (const Complex& others) const {
        return { 
            this->real + others.real, 
            this->img + others.img 
        };
    }

    Complex operator - (const Complex& others) const {
        return { 
            this->real - others.real,
            this->img - others.img 
        };
    }

    Complex operator * (const Complex& others) const {
        return { 
            this->real * others.real -  this->img * others.img,
            this->real * others.img + this->img * others.real
        };
    }

    Complex operator / (const Complex& others) const {
        double denom = others.real * others.real + others.img * others.img;
        if (denom == 0) return {};
        return {
            (this->real * others.real + this->img * others.img) / denom,
            (this->img * others.real - this->real * others.img) / denom
        };
    }

    friend ostream& operator << (ostream& os, Complex others) {
        os << others.real << " " << others.img;
        return os;
    }
};

class Vector {
private:
    size_t size;
    double* data;
public:
    Vector(size_t _size) : size(_size) {
        if (_size <= 0) {
            throw std::invalid_argument("Kich thuoc vector phai lon hon 0!");
        }
        data = new double[size](); 
    }

    ~Vector() {
        delete[] data;
    }

    Vector(const Vector& others) : size(others.size) {
        data = new double[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = others.data[i];
        }
    }

    Vector& operator = (const Vector& others) {
        if (this != &others) {
            delete[] data;
            
            size = others.size;
            data = new double[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = others.data[i];
            }
        }
        return *this;
    }

    double& operator[](size_t index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Truy cap vuot gioi han!");
        }
        return data[index];
    }

    const double& operator[](size_t index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Truy cap vuot gioi han!");
        }
        return data[index];
    }

    Vector operator + (const Vector& others) const {
        if (size != others.size) {
            throw invalid_argument("Hai vector khong cung kich thuoc!");
        }
        Vector result(size);
        for (size_t i = 0; i < size; i++) {
            result.data[i] = data[i] + others.data[i];
        }
        return result;
    }

    Vector operator - (const Vector& others) const {
        if (size != others.size) {
            throw invalid_argument("Hai vector khong cung kich thuoc!");
        }
        Vector result(size);
        for (size_t i = 0; i < size; i++) {
            result.data[i] = data[i] - others.data[i];
        }
        return result;
    }

    double operator * (const Vector& others) const {
        if (size != others.size) {
            throw invalid_argument("Hai vector khong cung kich thuoc!");
        }
        double result = 0;
        for (size_t i = 0; i < size; i++) {
            result += data[i] * others.data[i];
        }
        return result;
    }

    friend ostream& operator << (ostream& os, Vector others) {
        for (size_t i = 0; i < others.size; i++) {
            os << others.data[i] << " ";
        }
        return os;
    }

    size_t getSize() const {
        return size;
    }
};

class Matrix {
private:
    size_t rows, cols;
    double* data;
public:
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw invalid_argument("Kich thuoc hang hoac cot khong hop le!");
        }
        data = new double[rows * cols]();
    }

    ~Matrix() {
        delete[] data;
    }

    Matrix(const Matrix& others) : rows(others.rows), cols(others.cols) {
        data = new double[rows * cols];
        for (size_t i = 0; i < rows * cols; i++) {
            data[i] = others.data[i];
        }
    }

    Matrix& operator=(const Matrix& others) {
        if (this != &others) {
            delete[] data;

            rows = others.rows;
            cols = others.cols;
            data = new double[rows * cols];
            for (size_t i = 0; i < rows * cols; i++) {
                data[i] = others.data[i];
            }
        }
        return *this;
    }

    double& operator()(size_t r, size_t c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw out_of_range("Chi so ma tran khong hop le!");
        }
        return data[r * cols + c];
    }

    const double& operator()(size_t r, size_t c) const {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw out_of_range("Chi so ma tran khong hop le!");
        }
        return data[r * cols + c];
    }

    Matrix operator + (const Matrix& others) const {
        if (rows != others.rows || cols != others.cols) {
            throw invalid_argument("2 ma tran khong cung kich thuoc!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + others.data[i];
        }
        return result;
    }

    Matrix operator * (const Matrix& others) const {
        if (cols != others.rows) {
            throw invalid_argument("2 ma tran khong hop le");
        }
        Matrix result(rows, cols);

        for (size_t i = 0; i < rows ; i++) {
            for (size_t j = 0; j < others.cols; j++) {
                double sum = 0;
                for (size_t k = 0; k < others.rows; k++) {
                    sum += (*this)(i, k) * others(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
};

int main() {
    // do later
}