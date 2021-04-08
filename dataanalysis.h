#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

/**
@author Anatoly Sova,,,
*/

#include <math.h>
#include <vector>
#include "common.h"
using namespace std;

class DataAnalysis{
public:
    static double LagrangeI(const vector<point> &data, double t);
    static double LagrangeD(const vector<point> &data, double t);
    static double Simpson(double a, double b, const vector<point> &data);
protected:
    DataAnalysis();
    ~DataAnalysis();
private:
    static double Lagrange(const vector<point> &data, double t, double &p);
};

#endif
