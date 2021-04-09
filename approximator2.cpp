//---------------------------------------------------------------------------


#include "approximator2.h"

//---------------------------------------------------------------------------

double Approximator2::GetParameter(const vector<point3d> &data, const string &operation)
{
    double result = 0;
    const int n = data.size();
    for (auto index = data.begin(); index != data.end(); ++index)
    {
        if (operation == "AV_X1")
        {
            result += index->x;
        }
        if (operation == "AV_X2")
        {
            result += index->y;
        }
        if (operation == "AV_Y")
        {
            result += index->z;
        }
        if (operation == "SUM_X1X2")
        {
            const double sx1 = GetParameter(data, "AV_X1");
            const double sx2 = GetParameter(data, "AV_X2");
            const double v1 = index->x - sx1;
            const double v2 = index->y - sx2;
            result += v1 * v2;
        }
        if (operation == "SUM_X1Y")
        {
            const double sx1 = GetParameter(data, "AV_X1");
            const double sy = GetParameter(data, "AV_Y");
            const double v1 = index->x - sx1;
            const double v2 = index->z - sy;
            result += v1 * v2;
        }
        if (operation == "SUM_X2Y")
        {
            const double sx2 = GetParameter(data, "AV_X2");
            const double sy = GetParameter(data, "AV_Y");
            const double v1 = index->y - sx2;
            const double v2 = index->z - sy;
            result += v1 * v2;
        }
        if (operation == "SUM_X12")
        {
            const double sx1 = GetParameter(data, "AV_X1");
            result += pow(index->x - sx1, 2);
        }
        if (operation == "SUM_X22")
        {
            const double sx2 = GetParameter(data, "AV_X2");
            result += pow(index->y - sx2, 2);
        }
        if (operation == "SIGMA_X")
        {
            const double b = GetB(data);
            const double b2 = GetB2(data);
            const double sx1 = GetParameter(data, "AV_X1");
            const double sx2 = GetParameter(data, "AV_X2");
            const double v1 = (b / b2) * (index->x - sx1);
            const double v2 = (b2 / b) * (index->y - sx2);
            const double s = v1 + v2;
            result += pow(s, 2);
        }
        if (operation == "SIGMA_Y")
        {
            const double sy = GetParameter(data, "AV_Y");
            result += pow(index->z - sy, 2);
        }
        if (operation == "SIGMA_XY")
        {
            const double b = GetB(data);
            const double b2 = GetB2(data);
            const double sx1 = GetParameter(data, "AV_X1");
            const double sx2 = GetParameter(data, "AV_X2");
            const double sy = GetParameter(data, "AV_Y");
            const double v1 = (b / b2) * (index->x - sx1);
            const double v2 = (b2 / b) * (index->y - sx2);
            const double s = v1 + v2;
            result += s * (index->z - sy);
        }
    }
    if (operation == "SIGMA_X" || operation == "SIGMA_Y" || operation == "SIGMA_XY")
    {
        result /= n;
        result = sqrt(abs(result));
    }
    return result;
}

double Approximator2::GetA(const vector<point3d> &data)
{
    const double sx1 = GetParameter(data, "AV_X1");
    const double sx2 = GetParameter(data, "AV_X2");
    const double sy = GetParameter(data, "AV_Y");
    const double b = GetB(data);
    const double b2 = GetB2(data);
    return sy - b2 * sx1 - b * sx2;
}

double Approximator2::GetB(const vector<point3d> &data)
{
    const double sx1x2 = GetParameter(data, "SUM_X1X2");
    const double sx1y = GetParameter(data, "SUM_X1Y");
    const double sx2y = GetParameter(data, "SUM_X2Y");
    const double sx12 = GetParameter(data, "SUM_X12");
    const double sx22 = GetParameter(data, "SUM_X22");
    double result = sx12 * sx2y - sx1x2 * sx1y;
    result /= (sx12 * sx22 - pow(sx1x2, 2));
    return result;
}

double Approximator2::GetB2(const vector<point3d> &data)
{
    const double sx1x2 = GetParameter(data, "SUM_X1X2");
    const double sx1y = GetParameter(data, "SUM_X1Y");
    const double sx2y = GetParameter(data, "SUM_X2Y");
    const double sx12 = GetParameter(data, "SUM_X12");
    const double sx22 = GetParameter(data, "SUM_X22");
    double result = sx1y * sx22 - sx2y * sx1x2;
    result /= (sx12 * sx22 - pow(sx1x2, 2));
    return result;
}

double Approximator2::Delta(const vector<point3d> &data1, const vector<point3d> &data2)
{
    double result = 0;
    const int n = data1.size();
    for (int index = 0; index < n; index++)
    {
        if (data1[index].z != 0)
        {
            result += 100 * abs(data1[index].z - data2[index].z) / data1[index].z;
        }
    }
    result /= n;
    return result;
}

double Approximator2::Sigma(const vector<point3d> &data)
{
    double result = 0;
    const int n = data.size();
    const double a = GetA(data);
    const double b = GetB(data);
    const double b2 = GetB2(data);
    for (const auto& index : data)
    {
        result += pow(index.z - a - b * index.x - b2 * index.y, 2);
    }
    result /= n;
    result = sqrt(abs(result));
    return result;
}

double Approximator2::Correlation(const vector<point3d> &data)
{
    double result = pow(GetParameter(data, "SIGMA_XY"), 2);
    result /= GetParameter(data, "SIGMA_X");
    result /= GetParameter(data, "SIGMA_Y");
    return result;
}
