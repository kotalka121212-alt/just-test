#pragma once

#include "inc.h"


class Vector{
private:
    vector<double> data;

public:
    Vector() = default;
    Vector(size_t n, double init = 0.0) : data(n,init){}
    Vector(const vector<double>& v) : data(v) {}
    Vector(initializer_list<double> list) : data(list) {}

    size_t size() const {return data.size();}
    bool empty() const {return data.empty();}

    double& operator[](size_t i) {return data[i]; }
    const double& operator[](size_t i) const {return data[i]; }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size(); ++i) {
            std::cout << data[i];
            if (i != size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    Vector operator+(const Vector& other) const {
        assert(size() == other.size());
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
        result [i] = data[i] + other[i];
        return result;
    }

    Vector operator-(const Vector& other) const {
        assert(size() == other.size());
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
        result [i] = data[i] - other[i];
        return result;
    }    

    Vector operator*(double scalar) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] * scalar;
        return result;
    }    

    Vector operator/(double scalar) const {
        assert(scalar != 0.0);
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] / scalar;
        return result;
    }



    static double dot(const Vector& a, const Vector& b) {
    assert(a.size() == b.size());
    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}
};