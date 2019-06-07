#include "ProjectMath.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

static const double WGS84_e = 0.081819190842622;
static const double WGS84_e2 = WGS84_e * WGS84_e;
static const double WGS84_a = 6378137.0;
static const double WGS84_C0 = 6367449.1458;
static const double WGS84_C2 = 16038.5086;
static const double WGS84_C4 = 16.8326;
static const double WGS84_C6 = 0.022;

double DeltaAngle(double a, double b)
{
    double result = a - b;
    if (result > M_PI) result -= 2 * M_PI;
    if (result <= -M_PI) result += 2 * M_PI;

    return result;
}

bool IsDoubleEqual(double a, double b)
{
    return fabs(a - b) < 0.00001;
}

static double CalcQ(double B)
{
    return log(tan(M_PI / 4 + B / 2) *
        sqrt((1 - WGS84_e * sin(B)) / (1 + WGS84_e * sin(B))));
}

static double CalcX(double B)
{
    return WGS84_C0 * B + WGS84_C2 * sin(2 * B) +
            WGS84_C4 * sin(4 * B) + WGS84_C6 * sin(6 * B);
}

double GetDistance(double B1, double L1, double B2, double L2)
{
    double result;

    double deltaL = DeltaAngle(L2, L1);

    // В зависимости от допуска
    if (IsDoubleEqual(B2, B1))
    {
        double N = WGS84_a / sqrt(1 - WGS84_e2 * sin(B1) * sin(B1));
        result = N * cos(B1) * deltaL;
    }
    else
    {
        double q1 = CalcQ(B1);

        double q2 = CalcQ(B2);

        double A = atan2(deltaL, q2 - q1);

        double X1 = CalcX(B1);

        double X2 = CalcX(B2);

        result = (X2 - X1) / cos(A);
    }

    return fabs(result);

}

std::tuple<char, int, int, int> GradMinSec(double value)
{
    char sign = value > 0 ? '+' : '-';
    value = fabs(value);
    int grad = static_cast<int>(value);
    double _min = (value - grad) * 60;
    int min = static_cast<int>(_min);
    int sec = static_cast<int>((_min - min) * 60);

    return std::tuple<char, int, int, int>(sign, grad, min, sec);
}
