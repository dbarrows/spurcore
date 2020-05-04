#pragma once

#include <Rcpp.h>

namespace core {

inline double urand() {
    return R::runif(0, 1);
}
inline uint prand(double lambda) {
    return R::rpois(lambda);
}

}
