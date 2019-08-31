#include "mymath.h"

int myadd(int a, int b)
{
    return a + b;
}

double get_trace(const Eigen::Matrix3d& v)
{
    return v.diagonal().sum();
}