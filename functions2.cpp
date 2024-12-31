//---------------------------------------------------------------------------

#include "functions2.h"

//---------------------------------------------------------------------------

double Func21(double a, double b, double x, double y)
{
    return a * x + b * y;
}

double Func22(double a, double b, double x, double y)
{
    return a / (x + y) + b;
}

double Func23(double a, double b, double x, double y)
{
    return b * pow(x + y, a);
}

double Func24(double a, double b, double x, double y)
{
    return pow(10, b + a * (x + y));
}

double Func25(double a, double b, double x, double y)
{
    return exp(a * (x + y) + b);
}

double Func26(double a, double b, double x, double y)
{
    return b * exp(a * (x + y));
}

double Func27(double a, double b, double x, double y)
{
    return b * pow(a, x + y);
}

double Func28(double a, double b, double x, double y)
{
    return b + a * log(abs(x + y)) / log(10);
}

double Func29(double a, double b, double x, double y)
{
    return b + a * log(abs(x + y));
}

double Func30(double a, double b, double x, double y)
{
    return (x + y) / (a * (x + y) + b);
}

double Func31(double a, double b, double x, double y)
{
    return b * (x + y) / (a + x + y);
}

double Func32(double a, double b, double x, double y)
{
    return 1 / (b + a * (x + y));
}

double Func33(double a, double b, double x, double y)
{
    return b * pow(10, a * (x + y));
}

double Func34(double a, double b, double x, double y)
{
    return 1 / (b + a * exp(-(x + y)));
}

double Func35(double a, double b, double x, double y)
{
    return b / (a + x + y);
}

double Func36(double a, double b, double x, double y)
{
    return b * exp(a / (x + y));
}

double Func37(double a, double b, double x, double y)
{
    return b * pow(10, a / (x + y));
}

double Func38(double a, double b, double x, double y, signed char n0)
{
    return b + a * pow(x + y, n0);
}

double Func39(const vector<double>& mbxy, double x, double y, signed char n0)
{
    double r = 0;
    signed char sign = n0 >= 0 ? 1 : -1;
    for (signed char index = sign; index != n0 + sign; index += sign)
    {
        r += mbxy[abs(index)] * pow(x + y, index);
    }
    return mbxy[0] + r;
}

double Func40(double a, double b1, double b2, double x, double y)
{
    return a * pow(x + y, b1) * exp(b2 * (x + y));
}
