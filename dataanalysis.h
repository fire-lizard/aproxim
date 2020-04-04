#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

/**
@author Anatoly Sova,,,
*/

#include <math.h>
#include <QVector>
#include <QPointF>
using namespace std;

class DataAnalysis{
public:
	static double LagrangeI(const QVector<QPointF> &data, double x);
	static double LagrangeD(const QVector<QPointF> &data, double x);
	static double Simpson(double a, double b, const QVector<QPointF> &data);
protected:
    DataAnalysis();
    ~DataAnalysis();
private:
	static double Lagrange(const QVector<QPointF> &data, double x, double &p);
};

#endif
