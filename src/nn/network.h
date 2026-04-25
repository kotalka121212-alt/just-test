#pragma once

#include "inc.h"
#include "layer.h"


class NeuralNetwork {
private:
    std::vector<Layer> layers;
    double learningRate;

public:
    NeuralNetwork(double lr = 0.1) : learningRate(lr) {}

    void addLayer(size_t numInputs, size_t numNeurons) {
        layers.emplace_back(numInputs, numNeurons);
    }

    Vector predict(Vector input) {
        for (Layer& layer : layers) {
            input = layer.forward(input);
        }
        return input;
    }

    void train(const Vector& input, const Vector& target) {
        // Прямой проход с сохранением выходов
        std::vector<Vector> outputs;
        outputs.push_back(input);

        for (Layer& layer : layers) {
            outputs.push_back(layer.forward(outputs.back()));
        }

        // Ошибка выходного слоя
        Vector error(outputs.back().size());
        for (size_t i = 0; i < error.size(); ++i) {
            double out = outputs.back()[i];
            error[i] = (out - target[i]) * out * (1.0 - out);
        }

        // Обратный проход только для последнего слоя (пока один скрытый + выходной)
        // Идём с конца
        for (int l = layers.size() - 1; l >= 0; --l) {
            Layer& layer = layers[l];
            const Vector& prev = outputs[l];
            Matrix& w = layer.getWeights();
            Vector& b = layer.getBias();

            // Обновляем веса и bias
            for (size_t i = 0; i < layer.numNeurons(); ++i) {
                for (size_t j = 0; j < layer.numInputs(); ++j) {
                    w(i, j) -= learningRate * error[i] * prev[j];
                }
                b[i] -= learningRate * error[i];
            }

            // Если это не первый слой — считаем ошибку для предыдущего
            if (l > 0) {
                Vector prevError(layer.numInputs(), 0.0);
                for (size_t j = 0; j < layer.numInputs(); ++j) {
                    double sum = 0.0;
                    for (size_t i = 0; i < layer.numNeurons(); ++i) {
                        sum += w(i, j) * error[i];
                    }
                    double out = prev[j];
                    prevError[j] = sum * out * (1.0 - out);
                }
                error = prevError;
            }
        }
    }
};




