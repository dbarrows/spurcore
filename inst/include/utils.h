#pragma once

#include <Rcpp.h>

namespace core {

using namespace std;
using namespace arma;

inline double scale(double t, double lower, double upper) {
    return (t - lower) / (upper - lower);
}

template <typename T>
inline T interp(double w, T lower, T upper) {
    return round((1 - w)*lower + w*upper);
}

inline vec seq(double start, double stop, uint length_out) {
    auto seq_R = Rcpp::Function("seq");
    return Rcpp::as<vec>(seq_R(start, stop, Rcpp::_["length.out"] = length_out));
}

}
