#include "MathUtil.h"
#include <cmath>

int MathUtil::Interpolate(const std::vector<std::pair<int, int>>& points, int x) {
    double res = 0;
    for (auto p : points) {
        double l = p.second;
        for (auto q : points) if (p.first != q.first) {
            l *= double(x - q.first) / (p.first - q.first);
        }
        res += l;
    }
    return round(res);
}

double MathUtil::Gauss(double x, double sigma) {
    return std::exp(-x * x / 2 / sigma) / (std::sqrt(2 * PI) * sigma);
}
double MathUtil::GaussSqr(double xsqr, double sigma) {
    return std::exp(-xsqr / 2 / sigma) / (std::sqrt(2 * PI) * sigma);
}