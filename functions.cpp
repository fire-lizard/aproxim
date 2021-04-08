//---------------------------------------------------------------------------

#include "functions.h"

//---------------------------------------------------------------------------

double Func1(double a, double b, double x)
{
    return a * x + b;
}
double Func2(double a, double b, double x)
{
    return a / x + b;
}
double Func3(double a, double b, double x)
{
    return b * pow(x, a);
}
double Func4(double a, double b, double x)
{
    return pow(10, b + a * x);
}
double Func5(double a, double b, double x)
{
    return exp(a * x + b);
}
double Func6(double a, double b, double x)
{
    return b * exp(a * x);
}
double Func7(double a, double b, double x)
{
    return b * pow(a, x);
}
double Func8(double a, double b, double x)
{
    return b + a * log((double)abs(x)) / log((double)10);
}
double Func9(double a, double b, double x)
{
    return b + a * log(abs(x));
}
double Func10(double a, double b, double x)
{
    return x / (a * x + b);
}
double Func11(double a, double b, double x)
{
    return b * x / (a + x);
}
double Func12(double a, double b, double x)
{
    return 1 / (b + a * x);
}
double Func13(double a, double b, double x)
{
    return b * pow(10, a * x);
}
double Func14(double a, double b, double x)
{
    return 1 / (b + a * exp(-x));
}
double Func15(double a, double b, double x)
{
    return b / (a + x);
}
double Func16(double a, double b, double x)
{
    return b * exp(a / x);
}
double Func17(double a, double b, double x)
{
    return b * pow(10,a / x);
}
double Func18(double a, double b, double x, signed char n0)
{
    return b + a * pow(x, n0);
}
double Func19(vector<double> &mbx, double x, signed char n0)
{
    double r = 0;
    const signed char sign = n0 >= 0 ? 1 : -1;
    for (signed char index = sign; index != n0 + sign; index += sign)
    {
        r += mbx[(signed char)abs((float)index)] * pow(x, index);
    }
    return mbx[0] + r;
}
double Func20(double a, double b1, double b2, double x)
{
    return a * pow(x, b1) * exp(b2 * x);
}


