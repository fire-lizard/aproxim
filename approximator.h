//---------------------------------------------------------------------------

#ifndef ApproximatorH
#define ApproximatorH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/multi_array.hpp>
#include <QVector>
#include <QPointF>
using namespace std;
using namespace boost;

class Approximator
{
public:
    static double GetA(const QVector<QPointF> &data);
    static double GetB(const QVector<QPointF> &data);
    static double Delta(const QVector<QPointF> &data1, const QVector<QPointF> &data2);
    static double Sigma(const QVector<QPointF> &data);
    static double Correlation(const QVector<QPointF> &data);
    static bool GetPolynom(const QVector<QPointF> &data, vector<double> &mbx, signed char n);
    static double PolynomSigma(const QVector<QPointF> &data, const vector<double> &mbx, signed char n0);
    static double CorrelationRatio(const QVector<QPointF> &linear_data, const QVector<QPointF> &dst_data);
protected:
    static double GetParameter(const QVector<QPointF> &data, const string &operation);
private:
    static bool Zeidel(const multi_array<double, 2> &a, const vector<double> &b, vector<double> &x, unsigned char n);
};
#endif
