#include "MathUtil.h"

double MathUtil::Radians(double deg) {
    return deg * PI / 180.0;
}
double MathUtil::Degree(double rad) {
    return rad * 180.0 / PI;
}