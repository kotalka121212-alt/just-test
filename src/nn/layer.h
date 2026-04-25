#pragma once

#include "activate.h"
#include "matrix.h"
#include <boost/random.hpp>

class Layer {
private:
    Matrix weights;
    Vector bias;

    static double randomWeight() {
        static boost::random::mt19937 gen;
        static boost::random::normal_distribution<double> dist(0.0, 0.5);
        return dist(gen);
    }

public:
    Layer(size_t numInputs, size_t numNeurons)
        : weights(numNeurons, numInputs), bias(numNeurons) {
        for (size_t i = 0; i < numNeurons; ++i) {
            for (size_t j = 0; j < numInputs; ++j) {
                weights(i, j) = randomWeight();
            }
            bias[i] = randomWeight();
        }
    }

    Vector forward(const Vector& input) const {
        Vector z = weights * input + bias;
        Vector output(z.size());
        for (size_t i = 0; i < z.size(); ++i)
            output[i] = sigmoid(z[i]);
        return output;
    }

    const Matrix& getWeights() const { return weights; }
    const Vector& getBias() const { return bias; }
    Matrix& getWeights() { return weights; }
    Vector& getBias() { return bias; }

    size_t numInputs() const { return weights.numCols(); }
    size_t numNeurons() const { return weights.numRows(); }

    void print() const {
        std::cout << "Weights:\n";
        weights.print();
        std::cout << "Bias: ";
        bias.print();
    }
};