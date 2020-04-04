//---------------------------------------------------------------------------


#include "approximator.h"
//---------------------------------------------------------------------------

double Approximator::GetParameter(const QVector<QPointF> &data, const string &operation)
{
    double result = 0;
    const int n = data.size();
    for (auto index = data.begin();index != data.end();++index)
    {
        if (operation == "AV_X")
        {
            result += (*index).x() / n;
        }
        if (operation == "AV_Y")
        {
            result += (*index).y() / n;
        }
        if (operation == "SUM_X")
        {
            result += (*index).x();
        }
        if (operation == "SUM_Y")
        {
            result += (*index).y();
        }
        if (operation == "SUM_XY")
        {
            result += (*index).x() * (*index).y();
        }
        if (operation == "SUM_X2")
        {
            result += pow((*index).x(), 2);
        }
        if (operation == "SIGMA_X")
        {
            result += pow((*index).x() - GetParameter(data, "AV_X"), 2);
        }
        if (operation == "SIGMA_Y")
        {
            result += pow((*index).y() - GetParameter(data, "AV_Y"), 2);
        }
        if (operation == "SIGMA_XY")
        {
            const double val1 = (*index).x() - GetParameter(data, "AV_X");
			const double val2 = (*index).y() - GetParameter(data, "AV_Y");
            result += val1 * val2;
        }
    }
    if (operation == "SIGMA_X" || operation == "SIGMA_Y" || operation == "SIGMA_XY")
    {
        result /= n;
        result = sqrt(abs(result));
    }
    return result;
}

double Approximator::GetA(const QVector<QPointF> &data)
{
	const int n = data.size();
	const double sx = GetParameter(data, "SUM_X");
	const double sy = GetParameter(data, "SUM_Y");
	const double sxy = GetParameter(data, "SUM_XY");
	const double sx2 = GetParameter(data, "SUM_X2");
	double result = sx * sy - n * sxy;
    result /= (pow(sx, 2) - n * sx2);
    return result;
}

double Approximator::GetB(const QVector<QPointF> &data)
{
	const int n = data.size();
	const double sx = GetParameter(data, "SUM_X");
	const double sy = GetParameter(data, "SUM_Y");
	const double sxy = GetParameter(data, "SUM_XY");
	const  double sx2 = GetParameter(data, "SUM_X2");
	double result = sx * sxy - sy * sx2;
    result /= (pow(sx, 2) - n * sx2);
    return result;
}

double Approximator::Delta(const QVector<QPointF> &data1, const QVector<QPointF> &data2)
{
    double result = 0;
	const int n = data1.size();
    for (int index = 0;index < n;index++)
    {
        result += (100 * abs(data1[index].y() - data2[index].y())) / data1[index].y();
    }
    result /= n;
    return result;
}

double Approximator::Sigma(const QVector<QPointF> &data)
{
    double result = 0;
	const int n = data.size();
	const double a = GetA(data);
	const double b = GetB(data);
    for (const auto& index : data)
    {
        result += pow(index.y() - b - a * index.x(), 2);
    }
    result /= n;
    result = sqrt(abs(result));
    return result;
}

double Approximator::PolynomSigma(const QVector<QPointF> &data, const vector<double> &mbx, signed char n0)
{
    double result = 0;
	const int n = data.size();
    for (const auto& index : data)
    {
        double r = 0;
		const signed char sign = n0 >= 0 ? 1 : -1;
        for (signed char idx = sign;idx != n0;idx += sign)
        {
            r += mbx[abs(idx)] * pow(index.x(), idx);
        }
        r += mbx[0];
        result += pow(index.y() - r, 2);
    }
    result /= n;
    result = sqrt(abs(result));
    return result;
}

double Approximator::Correlation(const QVector<QPointF> &data)
{
	double result = pow(GetParameter(data, "SIGMA_XY"), 2);
    result /= GetParameter(data, "SIGMA_X");
    result /= GetParameter(data, "SIGMA_Y");
    return result;
}

double Approximator::CorrelationRatio(const QVector<QPointF> &linear_data, const QVector<QPointF> &dst_data)
{
	const int n = dst_data.size();
	const double sry = GetParameter(dst_data, "AV_Y");
    double sigma2 = 0;
    double lambda2 = 0;
    for (const auto& index : dst_data)
    {
        sigma2 += pow(index.y() - sry, 2);
    }
    sigma2 /= n;
    for (const auto& index : linear_data)
    {
        lambda2 += pow(index.y() - sry, 2);
    }
    lambda2 /= n;
    return sqrt(sigma2 / lambda2);
}

bool Approximator::Zeidel(const multi_array<double, 2> &a, const vector<double> &b, vector<double> &x, unsigned char n)
{
	const double e = 0.0001;
	unsigned char j;
	double m;
	int iCount = 0;
	do
	{
		m = 0;
		for (unsigned char i = 0;i < n;i++)
		{
			double s1 = 0;
			double s2 = 0;
			for (j = 0;j < i;j++) s1 += a[i][j] * x[j];
			for (j = i;j < n;j++) s2 += a[i][j] * x[j];
			const double v = x[i];
			x[i] -= ((double)1 / a[i][i]) * (s1 + s2 - b[i]);
			if (fabs(v - x[i]) > m) m = fabs(v - x[i]);
		}
		iCount++;
		if (iCount > 1000000) return false;
	}
	while (m >= e);
	return true;
}

bool Approximator::GetPolynom(const QVector<QPointF> &data, vector<double> &mbx, signed char n)
{
    vector<double> sy;
    sy.resize(abs(n), 0);
    vector<double> sx;
    sx.resize(2 * abs(n) - 1, 0);
	multi_array<double, 2> a(extents[n][n]);
	mbx.clear();
    mbx.resize(abs(n), 0);
    const signed char sign = n >= 0 ? 1 : -1;
    for (signed char index = 0;index != 2 * n - sign;index += sign)
    {
        for (const auto& idx : data)
        {
            sx[abs(index)] += pow(idx.x(), index);
        }
    }
    for (signed char index = 0;index != n;index += sign)
    {
        for (const auto& idx : data)
        {
            sy[abs(index)] += idx.y() * pow(idx.x(), index);
        }
    }
    for (signed char i = 0;i < abs(n);i++)
    {
        for (signed char j = 0;j < abs(n);j++)
        {
			a[i][j] = sx[i+j];           
        }
    }
    return Zeidel(a, sy, mbx, abs(n));
}

