
#include "differentiation.h"
#include <cmath>
#include <limits>

double forwardDifference(MathFunction f, double x, double h)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || !std::isfinite(x) ||
        !std::isfinite(h) || h <= 0)
        return invalid;

    try
    {
        return (f(x + h) - f(x)) / h;
    }
    catch (...)
    {
        return invalid;
    }
}

double backwardDifference(MathFunction f, double x, double h)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || !std::isfinite(x) ||
        !std::isfinite(h) || h <= 0)
        return invalid;

    try
    {
        return (f(x) - f(x - h)) / h;
    }
    catch (...)
    {
        return invalid;
    }
}

double centralDifference(MathFunction f, double x, double h)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || !std::isfinite(x) ||
        !std::isfinite(h) || h <= 0)
        return invalid;

    try
    {
        return (f(x + h) - f(x - h)) / (2.0 * h);
    }
    catch (...)
    {
        return invalid;
    }
}

double secondDerivative(MathFunction f, double x, double h)
{
    const double invalid = std::numeric_limits<double>::quiet_NaN();

    if (!f || !std::isfinite(x) ||
        !std::isfinite(h) || h <= 0)
        return invalid;

    try
    {
        return (f(x + h) - 2.0 * f(x) + f(x - h)) / (h * h);
    }
    catch (...)
    {
        return invalid;
    }
}
