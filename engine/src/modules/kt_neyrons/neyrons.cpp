#include "neyrons.h"

using namespace std;
using namespace neyrons;

double neyron::Processinput(double input)
{
return (input * weight) + bias;
}

double neyron::Restoreinput(double output)
{
return (output - bias) / weight;
}

void neyron::train(double input, double result)
{
    double actResult = Processinput(input);
    lastError = result - actResult;

    double delta_w = smooth * lastError * input;
    double delta_b = smooth * lastError;


    weight += delta_w;
    bias   += delta_b;
}



/*
void neyron::save(const string& filename){
json file;
file["weight"] = weight;
file["bias"] = bias;
file["smooth"] = smooth;

ofstream fil(filename);
fil << file.dump(4);
fil.close();

}*/