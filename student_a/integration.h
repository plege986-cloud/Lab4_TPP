
#pragma once

#ifdef _WIN32
#ifdef INTEGRATION_STATIC
#define INTEGRATION_API
#elif defined(INTEGRATION_EXPORTS)
#define INTEGRATION_API __declspec(dllexport)
#else
#define INTEGRATION_API __declspec(dllimport)
#endif
#else
#define INTEGRATION_API
#endif

using MathFunction = double (*)(double);

extern "C" {
    INTEGRATION_API double rectangle(MathFunction f, double a, double b, int n);
    INTEGRATION_API double trapezoid(MathFunction f, double a, double b, int n);
    INTEGRATION_API double simpson(MathFunction f, double a, double b, int n);
    INTEGRATION_API double integrationError(double approximate, double exact);
}
