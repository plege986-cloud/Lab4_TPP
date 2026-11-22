
#include "integration.h"
#include <cmath>
#include <limits>

double rectangle(MathFunction f, double a, double b, int n)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || n <= 0 || !std::isfinite(a) || !std::isfinite(b))
        return invalid;

    try
    {
        double h = (b - a) / n;
        double sum = 0.0;

        for (int i = 0; i < n; i++)
        {
            double x = a + (i + 0.5) * h;
            sum += f(x);
        }

        return sum * h;
    }
    catch (...)
    {
        return invalid;
    }
}

double trapezoid(MathFunction f, double a, double b, int n)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || n <= 0 || !std::isfinite(a) || !std::isfinite(b))
        return invalid;

    try
    {
        double h = (b - a) / n;
        double sum = (f(a) + f(b)) / 2.0;

        for (int i = 1; i < n; i++)
            sum += f(a + i * h);

        return sum * h;
    }
    catch (...)
    {
        return invalid;
    }
}

double simpson(MathFunction f, double a, double b, int n)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || n <= 0 || n % 2 != 0 ||
        !std::isfinite(a) || !std::isfinite(b))
        return invalid;

    try
    {
        double h = (b - a) / n;
        double sum = f(a) + f(b);

        for (int i = 1; i < n; i++)
        {
            double x = a + i * h;
            sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
        }

        return sum * h / 3.0;
    }
    catch (...)
    {
        return invalid;
    }
}

double integrationError(double approximate, double exact)
{
    if (!std::isfinite(approximate) || !std::isfinite(exact))
        return std::numeric_limits<double>::quiet_NaN();

    return std::abs(approximate - exact);
}
