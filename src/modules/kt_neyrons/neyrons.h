#pragma once
#include <includes.h>



namespace neyrons{







class neyron
{
private:



double weight = 0.5;
public:

void save(const string& filename);

double lastError;
double smooth = 0.00001f;
double bias = 0.001;


double Processinput(double input);
double Restoreinput(double output);
void train(double input, double result);
void processSave(const std::string &a);
/*
void save(const string& filename);

*/




};
}