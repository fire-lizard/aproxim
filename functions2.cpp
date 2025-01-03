//---------------------------------------------------------------------------

#include "functions2.h"

//---------------------------------------------------------------------------

double Func21(double a, double b, double x, double y)
{
    return a * x + b * y;
}
double Func22(double a, double b, double x, double y)
{
    return a * y / x + b;
}
double Func23(double a, double b, double x, double y)
{
    return b * y * pow(x, a);
}
double Func24(double a, double b, double x, double y)
{
    return y * pow(10, b + a * x);
}
double Func25(double a, double b, double x, double y)
{
    return y * exp(a * x + b);
}
double Func26(double a, double b, double x, double y)
{
    return b * y * exp(a * x);
}
double Func27(double a, double b, double x, double y)
{
    return b * y * pow(a, x);
}
double Func28(double a, double b, double x, double y)
{
    return b + a * y * log(abs(x)) / log(10);
}
double Func29(double a, double b, double x, double y)
{
    return b + a * y * log(abs(x));
}
double Func30(double a, double b, double x, double y)
{
    return x / (a * x + b * y);
}
double Func31(double a, double b, double x, double y)
{
    return b * x / (a + x + y);
}
double Func32(double a, double b, double x, double y)
{
    return 1 / (a * x + b * y);
}
double Func33(double a, double b, double x, double y)
{
    return b * y * pow(10, a * x);
}
double Func34(double a, double b, double x, double y)
{
    return 1 / (b + a * y * exp(-x));
}
double Func35(double a, double b, double x, double y)
{
    return b / (a + x + y);
}
double Func36(double a, double b, double x, double y)
{
    return b * exp(a * y / x);
}
double Func37(double a, double b, double x, double y)
{
    return b * pow(10, a * y / x);
}
double Func38(double a, double b, double x, double y, signed char n0)
{
    return b + a * pow(x, n0) + y;
}
double Func39(const vector<double>& mbx, double x, double y, signed char n0)
{
    double r = 0;
    const signed char sign = n0 >= 0 ? 1 : -1;
    for (signed char index = sign; index != n0 + sign; index += sign)
    {
        r += mbx[(signed char)abs((float)index)] * pow(x, index);
    }
    return mbx[0] + y + r;
}
double Func40(double a, double b, double x, double y)
{
    return a * pow(x + y, b) * exp(y);
}
