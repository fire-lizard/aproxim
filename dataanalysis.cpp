#include "dataanalysis.h"

DataAnalysis::DataAnalysis() = default;


DataAnalysis::~DataAnalysis() = default;


double DataAnalysis::Lagrange(const QVector<QPointF> &data, double t, double &p)
{
    vector <double> x;
	vector <double> f;
	for (const auto& index : data)
	{
		x.push_back(index.x());
		f.push_back(index.y());
	}
	int i;
	int n = data.size();
    vector <double> df(n + 1);

    n = n-1;
    for(i = 0; i <= n; i++)
    {
        df[i] = 0;
    }
    for(int m = 1; m <= n; m++)
    {
        for(i = 0; i <= n-m; i++)
        {
            df[i] = ((t-x[i + m]) * df[i] + f[i] + (x[i] - t) * df[i + 1]-f[i + 1]) / (x[i] - x[i + m]);
            f[i] = ((t-x[i + m]) * f[i] + (x[i] - t) * f[i + 1]) / (x[i] - x[i + m]);
        }
    }
    p = f[0];
	return df[0];
}


double DataAnalysis::Simpson(double a, double b, const QVector<QPointF> &data)
{
	const double epsilon = 0.0001;
	double x;

    double s2 = 1;
    double h = b - a;
    double s = LagrangeI(data, a) + LagrangeI(data, b);
    do
    {
        const double s3 = s2;
        h = double(h) / double(2);
        double s1 = 0;
        x = a + h;
        do
        {
            s1 = s1 + 2 * LagrangeI(data, x);
            x = x + 2 * h;
        }
        while(x < b);
        s = s + s1;
        s2 = double((s + s1) * h) / double(3);
        x = double(fabs(s3 - s2)) / double(15);
    }
    while(x > epsilon);
    return s2;
}

double DataAnalysis::LagrangeI(const QVector<QPointF> &data, double t)
{
	double res;
	Lagrange(data, t, res);
	return res;
}

double DataAnalysis::LagrangeD(const QVector<QPointF> &data, double t)
{
	double p;
	return Lagrange(data, t, p);
}
