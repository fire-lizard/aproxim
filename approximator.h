//---------------------------------------------------------------------------

#ifndef ApproximatorH
#define ApproximatorH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/multi_array.hpp>
#include "common.h"
using namespace std;
using namespace boost;

class Approximator
{
public:
    static double GetA(const vector<point> &data);
    static double GetB(const vector<point> &data);
    static double Delta(const vector<point> &data1, const vector<point> &data2);
    static double Sigma(const vector<point> &data);
    static double Correlation(const vector<point> &data);
    static bool GetPolynom(const vector<point> &data, vector<double> &mbx, signed char n);
    static double PolynomSigma(const vector<point> &data, const vector<double> &mbx, signed char n0);
    static double CorrelationRatio(const vector<point> &linear_data, const vector<point> &dst_data);
protected:
    static double GetParameter(const vector<point> &data, const string &operation);
private:
    static bool Zeidel(const multi_array<double, 2> &a, const vector<double> &b, vector<double> &x, unsigned char n);
};
#endif
