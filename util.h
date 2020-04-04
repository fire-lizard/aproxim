
#ifndef UtilH
#define UtilH

#include <vector>
#include <valarray>
#include <QVector>
#include <QVector3D>
#include <QMessageBox>

#include "approximator.h"
#include "approximator_2.h"
#include "functions.h"

void LinearParameters(double x, double y, double &x1, double &y1, unsigned char func, signed char n0);
int LinearData(const QVector<QPointF> &src_data, QVector<QPointF> &linear_data, signed char n0, unsigned char f);
int LinearData(const QVector<QPointF> &src_data, QVector<QVector3D> &linear_data_2, signed char n0, unsigned char f);
void CalculateParameters(double a, double b, double &a1, double &b1, unsigned char func);
int CalculateData(QVector<QPointF> &src_data, QVector<QPointF> &dst_data, double &a1, double &b1, double &b2, signed char n0, vector<double> &mbx, unsigned char f);
void CalculateCoefficients(const QVector<QPointF> &src_data, const QVector<QPointF> &dst_data, const vector<double> &mbx, signed char n0, double &delta, double &sigma, double &r, double &nu, unsigned char f);
QPointF CalculateMax(const QVector<QPointF> &data);
QPointF CalculateMin(const QVector<QPointF> &data);

QPointF GetLesserThan(const QVector<QPointF> &data, double x);
QPointF GetGreaterThan(const QVector<QPointF> &data, double x);
QVector3D GetParameters(double v1, double v2);
double Interpolation(double x1, double x2, double y1, double y2, double xar);
double GetParameter(const QVector<QPointF> &data, double xparam);
unsigned char Epsilon(const QVector<QPointF> &data);

#endif
