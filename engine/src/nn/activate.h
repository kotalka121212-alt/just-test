#pragma once
#include "inc.h"

inline double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

inline double sigmoidDerivative(double x){
    double s = sigmoid(x);
    return s * (1.0 - s);
}