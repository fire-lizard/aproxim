//---------------------------------------------------------------------------

#ifndef Approximator_2H
#define Approximator_2H
//---------------------------------------------------------------------------

#include "approximator.h"
#include <QVector3D>

using namespace boost;

class Approximator_2 : public Approximator
{
public:
    static double GetA(const QVector<QVector3D> &data);
    static double GetB(const QVector<QVector3D> &data);
    static double GetB2(const QVector<QVector3D> &data);
    static double Delta(const QVector<QVector3D> &data1, const QVector<QVector3D> &data2);
    static double Sigma(const QVector<QVector3D> &data);
    static double Correlation(const QVector<QVector3D> &data);
protected:
    static double GetParameter(const QVector<QVector3D> &data, const string &operation);
};
#endif

