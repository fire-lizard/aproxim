//---------------------------------------------------------------------------

#include "functions2.h"

//---------------------------------------------------------------------------

double Func21(double a, double b, double x, double y)
{
    return a * x + b * y;
}
double Func22(double a, double b, double x, double y)
{
    return a / x + b / y;
}
double Func23(double a, double b, double x, double y)
{
    return pow(x, a) * pow(y, b);
}
double Func24(double a, double b, double x, double y)
{
    return a * x + b / y;
}
double Func25(double a, double b, double x, double y)
{
    return exp(a * x + b * y);
}
double Func26(double a, double b, double x, double y)
{
    return b * y * exp(a * x);
}
double Func27(double a, double b, double x, double y)
{
    return pow(b, y) * pow(a, x);
}
double Func28(double a, double b, double x, double y)
{
    return pow(x, a) + b * y;
}
double Func29(double a, double b, double x, double y)
{
    return b * log(abs(y)) + a * log(abs(x));
}
double Func30(double a, double b, double x, double y)
{
    return y / (a * x + b);
}
double Func31(double a, double b, double x, double y)
{
    return b * y / (a + x);
}
double Func32(double a, double b, double x, double y)
{
    return 1 / (b *y + a * x);
}
double Func33(double a, double b, double x, double y)
{
    return pow(x, a) + b / y;
}
double Func34(double a, double b, double x, double y)
{
    return 1 / (b + a * exp(-x));
}
double Func35(double a, double b, double x, double y)
{
    return b * y / (a + x);
}
