
#ifndef UtilH
#define UtilH

#include <vector>
#include <valarray>
#include <QMessageBox>

#include "common.h"
#include "functions.h"
#include "approximator.h"
#include "approximator_2.h"

void LinearParameters(double x, double y, double &x1, double &y1, unsigned char func, signed char n0);
int LinearData(const vector<point> &src_data, vector<point> &linear_data, signed char n0, unsigned char f);
int LinearData(const vector<point> &src_data, vector<point3d> &linear_data_2, signed char n0, unsigned char f);
void CalculateParameters(double a, double b, double &a1, double &b1, unsigned char func);
int CalculateData(vector<point> &src_data, vector<point> &dst_data, double &a1, double &b1, double &b2, signed char n0, vector<double> &mbx, unsigned char f);
void CalculateCoefficients(const vector<point> &src_data, const vector<point> &dst_data, const vector<double> &mbx, signed char n0, double &delta, double &sigma, double &r, double &nu, unsigned char f);
point CalculateMax(const vector<point> &data);
point CalculateMin(const vector<point> &data);

point GetLesserThan(const vector<point> &data, double x);
point GetGreaterThan(const vector<point> &data, double x);
point3d GetParameters(double v1, double v2);
double Interpolation(double x1, double x2, double y1, double y2, double xar);
double GetParameter(const vector<point> &data, double xparam);
unsigned char Epsilon(const vector<point> &data);

#endif
