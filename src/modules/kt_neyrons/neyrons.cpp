#include "neyrons.h"

using namespace std;
using namespace neyrons;

double neyron::Processinput(double input)
{
return (input * neyron::weight) + neyron::bias;
}

double neyron::Restoreinput(double output)
{
return (output - neyron::bias) / neyron::weight;
}

void neyron::train(double input, double result)
{
    double actResult = Processinput(input);
    neyron::lastError = result - actResult;

    double delta_w = neyron::smooth * neyron::lastError * input;
    double delta_b = neyron::smooth * neyron::lastError;


    neyron::weight += delta_w;
    neyron::bias   += delta_b;
}

void neyron::processSave(const string &a){


}
