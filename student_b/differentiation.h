
#pragma once

#ifdef _WIN32
#ifdef DIFFERENTIATION_STATIC
#define DIFFERENTIATION_API
#elif defined(DIFFERENTIATION_EXPORTS)
#define DIFFERENTIATION_API __declspec(dllexport)
#else
#define DIFFERENTIATION_API __declspec(dllimport)
#endif
#else
#define DIFFERENTIATION_API
#endif

using MathFunction = double (*)(double);

extern "C" {
    DIFFERENTIATION_API double forwardDifference(MathFunction f, double x, double h);
    DIFFERENTIATION_API double backwardDifference(MathFunction f, double x, double h);
    DIFFERENTIATION_API double centralDifference(MathFunction f, double x, double h);
    DIFFERENTIATION_API double secondDerivative(MathFunction f, double x, double h);
}
