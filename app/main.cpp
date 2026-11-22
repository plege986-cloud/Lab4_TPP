
#include <iostream>
#include <iomanip>
#include <cmath>
#include "integration.h"
#include "differentiation.h"

double function(double x)
{
    return x * x;
}

int main()
{
    const double a = 0.0;
    const double b = 1.0;
    const int n = 100;
    const double exact = 1.0 / 3.0;

    std::cout << std::fixed << std::setprecision(10);

    std::cout << "=== INTEGRATION ===\n";

    double r = rectangle(function, a, b, n);
    double t = trapezoid(function, a, b, n);
    double s = simpson(function, a, b, n);

    std::cout << "Rectangle: " << r << '\n';
    std::cout << "Trapezoid: " << t << '\n';
    std::cout << "Simpson:   " << s << '\n';
    std::cout << "Exact:     " << exact << '\n';

    std::cout << "Rectangle error: "
        << integrationError(r, exact) << '\n';

    std::cout << "Trapezoid error: "
        << integrationError(t, exact) << '\n';

    std::cout << "Simpson error: "
        << integrationError(s, exact) << '\n';

    std::cout << "\n=== DIFFERENTIATION ===\n";

    const double x = 2.0;
    const double h = 0.001;

    std::cout << "Forward:  "
        << forwardDifference(function, x, h) << '\n';

    std::cout << "Backward: "
        << backwardDifference(function, x, h) << '\n';

    std::cout << "Central:  "
        << centralDifference(function, x, h) << '\n';

    std::cout << "Second:   "
        << secondDerivative(function, x, h) << '\n';

    std::cout << "Exact first derivative: 4.0\n";
    std::cout << "Exact second derivative: 2.0\n";

    std::cout << "\n=== ERROR TESTS ===\n";

    std::cout << "Rectangle n=0: "
        << rectangle(function, 0.0, 1.0, 0) << '\n';

    std::cout << "Simpson n=3: "
        << simpson(function, 0.0, 1.0, 3) << '\n';

    std::cout << "Forward h=0: "
        << forwardDifference(function, 2.0, 0.0) << '\n';

    std::cout << "Central nullptr: "
        << centralDifference(nullptr, 2.0, 0.001) << '\n';

    std::cout << "\n=== TEST COMPLETED ===\n";

    return 0;
}
