//---------------------------------------------------------------------------

#ifndef Approximator2H
#define Approximator2H
//---------------------------------------------------------------------------

#include <vector>
#include "approximator.h"
using namespace std;
using namespace boost;

class Approximator2 : public Approximator
{
public:
    static double GetA(const vector<point3d> &data);
    static double GetB(const vector<point3d> &data);
    static double GetB2(const vector<point3d> &data);
    static double Delta(const vector<point3d> &data1, const vector<point3d> &data2);
    static double Sigma(const vector<point3d> &data);
    static double Correlation(const vector<point3d> &data);
protected:
    static double GetParameter(const vector<point3d> &data, const string &operation);
};
#endif

