#pragma once

#include <vector>


class MathUtil {
  public:
    inline static const double PI = 3.1415926535897932;

    static double Radians(double deg);
    static double Degree(double rad);

    static int Interpolate(const std::vector<std::pair<int, int>> &points, int x);

    static double Gauss(double x, double sigma);
    static double GaussSqr(double xsqr, double sigma);
};
