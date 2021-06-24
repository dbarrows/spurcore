#pragma once

#include <Rcpp.h>

namespace core {

using namespace std;
using namespace arma;

inline double scale(double t, double lower, double upper) {
    return (t - lower)/(upper - lower);
}

template <typename T>
inline T interp(double w, T lower, T upper) {
    return round((1 - w)*lower + w*upper);
}

inline vec seq(double start, double stop, unsigned int length_out) {
    vec s = vec(length_out);
    s[0] = start;
    double step = (stop - start)/static_cast<double>(length_out - 1);
    for (uint i = 1; i < length_out - 1; i++)
        s[i] = start + step*i;
    s[length_out - 1] = stop;
    return s
}

template <typename VOUT, typename VIN>
inline VOUT vector_cast(VIN v) {
    VOUT out = VOUT(v.size());
    for (unsigned int i = 0; i < v.size(); i++)
        out[i] = v[i];
    return out;
}

}
