
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <cmath>

using MathFunction = double (*)(double);
using IntegrationMethod = double (*)(MathFunction, double, double, int);
using ErrorMethod = double (*)(double, double);
using DifferentiationMethod = double (*)(MathFunction, double, double);

double function(double x)
{
    return x * x;
}

int main()
{
    HMODULE integration = LoadLibraryW(L"IntegrationLib.dll");
    HMODULE differentiation = LoadLibraryW(L"DifferentiationLib.dll");

    if (!integration || !differentiation)
    {
        std::cerr << "DLL loading failed. Error: "
            << GetLastError() << '\n';

        if (integration)
            FreeLibrary(integration);

        if (differentiation)
            FreeLibrary(differentiation);

        return 1;
    }

    auto rectangle = reinterpret_cast<IntegrationMethod>(
        GetProcAddress(integration, "rectangle"));

    auto trapezoid = reinterpret_cast<IntegrationMethod>(
        GetProcAddress(integration, "trapezoid"));

    auto simpson = reinterpret_cast<IntegrationMethod>(
        GetProcAddress(integration, "simpson"));

    auto integrationError = reinterpret_cast<ErrorMethod>(
        GetProcAddress(integration, "integrationError"));

    auto forwardDifference = reinterpret_cast<DifferentiationMethod>(
        GetProcAddress(differentiation, "forwardDifference"));

    auto backwardDifference = reinterpret_cast<DifferentiationMethod>(
        GetProcAddress(differentiation, "backwardDifference"));

    auto centralDifference = reinterpret_cast<DifferentiationMethod>(
        GetProcAddress(differentiation, "centralDifference"));

    auto secondDerivative = reinterpret_cast<DifferentiationMethod>(
        GetProcAddress(differentiation, "secondDerivative"));

    if (!rectangle || !trapezoid || !simpson ||
        !integrationError || !forwardDifference ||
        !backwardDifference || !centralDifference ||
        !secondDerivative)
    {
        std::cerr << "Function loading failed.\n";
        FreeLibrary(integration);
        FreeLibrary(differentiation);
        return 1;
    }

    std::cout << std::fixed << std::setprecision(10);

    const double exact = 1.0 / 3.0;

    std::cout << "=== EXPLICIT DLL LOADING ===\n";

    double r = rectangle(function, 0.0, 1.0, 100);
    double t = trapezoid(function, 0.0, 1.0, 100);
    double s = simpson(function, 0.0, 1.0, 100);

    std::cout << "\nINTEGRATION\n";
    std::cout << "Rectangle: " << r << '\n';
    std::cout << "Trapezoid: " << t << '\n';
    std::cout << "Simpson:   " << s << '\n';
    std::cout << "Simpson error: "
        << integrationError(s, exact) << '\n';

    std::cout << "\nDIFFERENTIATION\n";
    std::cout << "Forward:  "
        << forwardDifference(function, 2.0, 0.001) << '\n';
    std::cout << "Backward: "
        << backwardDifference(function, 2.0, 0.001) << '\n';
    std::cout << "Central:  "
        << centralDifference(function, 2.0, 0.001) << '\n';
    std::cout << "Second:   "
        << secondDerivative(function, 2.0, 0.001) << '\n';

    FreeLibrary(integration);
    FreeLibrary(differentiation);

    std::cout << "\nDLL unloaded successfully.\n";

    return 0;
}
