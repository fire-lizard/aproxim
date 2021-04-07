
#include "util.h"

void LinearParameters(double x, double y, double &x1, double &y1, unsigned char func, signed char n0)
{
	switch (func)
	{
	case 0:
		x1 = x;
		y1 = y;
		break;
	case 1:
		x1 = x;
		y1 = y;
		break;
	case 2:
		x1 = 1 / x;
		y1 = y;
		break;
	case 3:
		x1 = log(abs(x));
		y1 = log(abs(y));
		break;
	case 4:
		x1 = x;
		y1 = log(abs(y));
		break;
	case 5:
		x1 = x;
		y1 = log(abs(y));
		break;
	case 6:
		x1 = x;
		y1 = log(abs(y));
		break;
	case 7:
		x1 = x;
		y1 = log(abs(y));
		break;
	case 8:
		x1 = log(abs(x)) / 2.3;
		y1 = y;
		break;
	case 9:
		x1 = log(abs(x));
		y1 = y;
		break;
	case 10:
		x1 = 1 / x;
		y1 = 1 / y;
		break;
	case 11:
		x1 = 1 / x;
		y1 = 1 / y;
		break;
	case 12:
		x1 = x;
		y1 = 1 / y;
		break;
	case 13:
		x1 = x;
		y1 = log(abs(y));
		break;
	case 14:
		x1 = exp(-x);
		y1 = 1 / y;
		break;
	case 15:
		x1 = x;
		y1 = 1 / y;
		break;
	case 16:
		x1 = 1 / x;
		y1 = log(abs(y));
		break;
	case 17:
		x1 = 1 / x;
		y1 = log(abs(y));
		break;
	case 18:
		x1 = pow(x, n0);
		y1 = y;
		break;
	case 19:
		x1 = x;
		y1 = y;
		break;
	case 20:
		x1 = log(abs(x));
		y1 = log(abs(y));
		break;
	default:
		break;
	}
}

void CalculateParameters(double a, double b, double &a1, double &b1, unsigned char func)
{
	switch (func)
	{
	case 0:
		a1 = a;
		b1 = b;
		break;
	case 1:
		a1 = a;
		b1 = b;
		break;
	case 2:
		a1 = a;
		b1 = b;
		break;
	case 3:
		a1 = a;
		b1 = exp(b);
		break;
	case 4:
		a1 = a / log((double)10);
		b1 = b / log((double)10);
		break;
	case 5:
		a1 = a;
		b1 = b;
		break;
	case 6:
		a1 = a;
		b1 = exp(b);
		break;
	case 7:
		a1 = exp(a);
		b1 = exp(b);
		break;
	case 8:
		a1 = a;
		b1 = b;
		break;
	case 9:
		a1 = a;
		b1 = b;
		break;
	case 10:
		a1 = a;
		b1 = b;
		break;
	case 11:
		a1 = a / b;
		b1 = 1 / b;
		break;
	case 12:
		a1 = a;
		b1 = b;
		break;
	case 13:
		a1 = a / log((double)10);
		b1 = exp(b);
		break;
	case 14:
		a1 = a;
		b1 = b;
		break;
	case 15:
		a1 = b / a;
		b1 = 1 / a;
		break;
	case 16:
		a1 = a;
		b1 = exp(b);
		break;
	case 17:
		a1 = a / log((double)10);
		b1 = exp(b);
		break;
	case 18:
		a1 = a;
		b1 = b;
		break;
	case 20:
		a1 = b;
		b1 = exp(a);
		break;
	default:
		break;
	}
}

int LinearData(const vector<point> &src_data, vector<point> &linear_data, signed char n0, unsigned char f)
{
    int row = 0;
	for (const auto& index : src_data)
	{
        row++;
        const double x = index.x;
        const double y = index.y;
        double x1, y1;
        try
        {
            LinearParameters(x, y, x1, y1, f, n0);
        }
        catch (std::exception &ee)
        {
			QMessageBox::about(nullptr, "Error", ee.what());
        	return row;
        }
        linear_data.push_back(point(x1,y1));
    }
	return 0;
}

int LinearData(const vector<point> &src_data, vector<point3d> &linear_data_2, signed char n0, unsigned char f)
{
    int row = 0;
    for (const auto& index : src_data)
    {
        row++;
        const double x = index.x;
        const double y = index.y;
        double x1, y1;
        try
        {
            LinearParameters(x, y, x1, y1, f, n0);
        }
        catch (std::exception &ee)
        {
			QMessageBox::about(nullptr, "Error", ee.what());
			return row;
        }
        linear_data_2.push_back(point3d(x1, x, y1));
    }
	return 0;
}

int CalculateData(vector<point> &src_data, vector<point> &dst_data, double &a1, double &b1, double &b2, signed char n0, vector<double> &mbx, unsigned char f)
{
    vector<point> linear_data;
    vector<point3d> linear_data_2;
    const signed char sign = n0 >= 0 ? 1 : -1;
    linear_data.clear();
    dst_data.clear();
    linear_data_2.clear();
	int res = 0;
    if (f <= 19) res = LinearData(src_data, linear_data, n0, f);
    if (f == 20) res = LinearData(src_data, linear_data_2, n0, f);
	if (res != 0) return res;
    double a = 0;
	double b = 0;
    if (f == 19)
    {
        if (!Approximator::GetPolynom(linear_data, mbx, n0 + sign))
        {
			return -1;
        }
    }
    if (f <= 18)
    {
        a = Approximator::GetA(linear_data);
        b = Approximator::GetB(linear_data);
    }
    if (f == 20)
    {
        a = Approximator_2::GetA(linear_data_2);
        b = Approximator_2::GetB(linear_data_2);
        b2 = Approximator_2::GetB2(linear_data_2);
    }
    CalculateParameters(a, b, a1, b1, f);
    func deps[17] = {Func1,Func2,Func3,Func4,Func5,Func6,Func7,Func8,
        Func9,Func10,Func11,Func12,Func13,Func14,Func15,Func16,Func17};
    for (auto& index : src_data)
    {
        const double x1 = index.x;
		double y1 = 0;
        if (f <= 1)
        {
            y1 = deps[0](a1, b1, x1);
        }
        else
        {
            if (f < 18)
            {
                y1 = deps[f - 1](a1, b1, x1);
            }
            else
            {
                if (f == 18)
                {
                    y1 = Func18(a1, b1, x1, n0);
                }
                if (f == 19)
                {
                    y1 = Func19(mbx, x1, n0);
                }
                if (f == 20)
                {
                    y1 = Func20(a1, b1, b2, x1);
                }
            }
        }
        dst_data.push_back(point(x1,y1));
    }
	return 0;
}

void CalculateCoefficients(const vector<point> &src_data, const vector<point> &dst_data, const vector<double> &mbx, signed char n0, double &delta, double &sigma, double &r, double &nu, unsigned char f)
{
    vector<point> linear_data;
    vector<point3d> linear_data_2;
    linear_data.clear();
    linear_data_2.clear();
    const signed char sign = n0 >= 0 ? 1 : -1;
    if (f <= 18)
    {
        LinearData(src_data, linear_data, n0, f);
		delta = Approximator::Delta(src_data, dst_data);
        sigma = Approximator::Sigma(linear_data);
        r = Approximator::Correlation(linear_data);
    }
    if (f == 19)
    {
        LinearData(src_data, linear_data, n0, f);
        delta = Approximator::Delta(src_data, dst_data);
        sigma = Approximator::PolynomSigma(linear_data, mbx, n0 + sign);
        nu = Approximator::CorrelationRatio(linear_data, dst_data);
    }
    if (f == 20)
    {
        LinearData(src_data, linear_data_2, n0, f);
        delta = Approximator::Delta(src_data, dst_data);
        sigma = Approximator_2::Sigma(linear_data_2);
        r = Approximator_2::Correlation(linear_data_2);
    }
}

point CalculateMax(const vector<point> &data)
{
	int f;
    point result = data[0];
	do
	{
		f = 0;
		for (const auto& index : data)
		{
            if (result.x < index.x)
			{
                result.x = index.x;
				f = 1;
			}
            if (result.y < index.y)
			{
                result.y = index.y;
				f = 1;
			}
		}
	}
	while (f == 1);
	return result;
}

point CalculateMin(const vector<point> &data)
{
	int f;
    point result = data[0];
	do
	{
		f = 0;
		for (const auto& index : data)
		{
            if (result.x > index.x)
			{
                result.x = index.x;
				f = 1;
			}
            if (result.y > index.y)
			{
                result.y = index.y;
				f = 1;
			}
		}
	}
	while (f == 1);
	return result;
}

point GetLesserThan(const vector<point> &data, double x)
{
    point result = data[0];
	for (const auto& index : data)
	{
        if (abs(result.x - x) > abs(index.x - x) && index.x < x)
		{
			result = index;
		}
	}
	return result;
}

point GetGreaterThan(const vector<point> &data, double x)
{
    point result = data[0];
	for (const auto& index : data)
	{
        if (abs(result.x - x) > abs(index.x - x) && index.x > x)
		{
			result = index;
		}
	}
	return result;
}

point3d GetParameters(double v1, double v2)
{
	const double ar = (v1 + v2) / 2;
	const double geom = sqrt(v1 * v2);
	const double garm = 2 * v1 * v2 / (v1 + v2);
    const point3d result(ar, geom, garm);
	return result;
}

double Interpolation(double x1, double x2, double y1, double y2, double xar)
{
	return y1 + (((y2 - y1) / (x2 - x1)) * (xar - x1));
}

double GetParameter(const vector<point> &data, double xparam)
{
    const point p1 = GetLesserThan(data, xparam);
    const point p2 = GetGreaterThan(data, xparam);
    return Interpolation(p1.x, p2.x, p1.y, p2.y, xparam);
}

unsigned char Epsilon(const vector<point> &data)
{
    const double xminval = CalculateMin(data).x;
    const double xmaxval = CalculateMax(data).x;
    const double yminval = CalculateMin(data).y;
    const double ymaxval = CalculateMax(data).y;
    point3d xtuple = GetParameters(xminval, xmaxval);
    point3d ytuple = GetParameters(yminval, ymaxval);
    const double ar = GetParameter(data, xtuple.x);
    const double geom = GetParameter(data, xtuple.y);
    const double garm = GetParameter(data, xtuple.z);
    double arr[] = {abs(ar - ytuple.x), abs(ar - ytuple.y), abs(ar - ytuple.z),
                    abs(geom - ytuple.x), abs(geom - ytuple.y),
                    abs(garm - ytuple.x), abs(garm - ytuple.z)};
	valarray<double> epsilons(arr, 7);
	const double minvalue = epsilons.min();
	for (unsigned index = 0; index < epsilons.size(); index++)
	{
		if (minvalue == epsilons[index])
		{
			return index + 1;
		}
	}
	return 0;
}
