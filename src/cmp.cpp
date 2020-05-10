#include "cmp.hh"
#include <cmath>

/*******************************************
 Accurate comparison
********************************************/

bool cmp(double var1, double var2)
{
    return (fabs(var1 - var2) < eps) ? true : false;
}
