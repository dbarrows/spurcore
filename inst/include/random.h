#pragma once

#include <Rcpp.h>

namespace core {

inline double runif() {
    return R::runif(0, 1);
}
inline uint rpois(double lambda) {
    return R::rpois(lambda);
}

}
