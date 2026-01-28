#include "roots.hpp"

bool bisection(std::function<double(double)> f,
               double a, double b,
               double *root) {
    return false;
}

bool regula_falsi(std::function<double(double)> f,
                  double a, double b,
                  double *root) {
    return false;
}

bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root) {
    return false;
}

bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root) {
    return false;
}

#include "roots.hpp"
#include <cmath>
#include <functional>
#include <limits>

bool bisection(std::function<double(double)> f,
               double a, double b,
               double *root)
{
    const double tol = 1e-6;
    const int max_iter = 1000000;

    double fa = f(a);
    double fb = f(b);

    if (fa * fb > 0)
        return false; // no sign change

    for (int i = 0; i < max_iter; i++)
    {
        double c = 0.5 * (a + b);
        double fc = f(c);

        if (std::fabs(fc) < tol)
        {
            *root = c;
            return true;
        }

        if (fa * fc < 0)
        { // if fa and fc have opposite signs, then keep them
          // by updating b
            b = c;
            fb = fc;
        }
        else
        { // fa and fc have same sign, 
          // so keep fc and fb by updating a
            a = c;
            fa = fc;
        }
    }

    return false; // did not converge
}


bool regula_falsi(std::function<double(double)> f,
                  double a, double b,
                  double *root)
{
    const double tol = 1e-6;
    const int max_iter = 1000000;

    double fa = f(a);
    double fb = f(b);

    if (fa * fb > 0)
        return false;

    for (int i = 0; i < max_iter; i++)
    {
        double c = (a * fb - b * fa) / (fb - fa); // rearraged from equation of a line
        double fc = f(c);

        if (std::fabs(fc) < tol)
        {
            *root = c;
            return true;
        }

        if (fa * fc < 0)
        { // if fa and fc have opposite signs, then keep them
          // by updating b
            b = c;
            fb = fc;
        }
        else
        { // fa and fc have same sign, 
          // so keep fc and fb by updating a
            a = c;
            fa = fc;
        }
    }

    return false;
}

bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root)
{
    const double tol = 1e-6;
    const int max_iter = 1000000;

    for (int i = 0; i < max_iter; i++)
    {
        double fc = f(c);
        if (std::fabs(fc) < tol)
        {
            *root = c;
            return true;
        }

        double gc = g(c);
        if (gc == 0)
            return false;

        c = c - fc / gc; // Newton-Raphson formula, finds root of tangent line

        if (c < a || c > b)
            return false;
    }

    return false;
}

bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root)
{
    const double tol = 1e-6;
    const int max_iter = 1000000;

    double x0 = a;
    double x1 = b;

    for (int i = 0; i < max_iter; i++)
    {
        double f0 = f(x0);
        double f1 = f(x1);

        if (std::fabs(f1) < tol)
        {
            *root = x1;
            return true;
        }

        if (f1 - f0 == 0)
            return false;
        // finds root of secant line
        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0); // Secant method formula
        
        // updates, (no need for different signs here)
        x0 = x1;
        x1 = x2;
    }

    return false;
}
