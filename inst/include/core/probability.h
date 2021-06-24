#pragma once

#include <RcppArmadillo.h>

namespace core {

inline double runif() {
    return R::runif(0, 1);
}

inline unsigned int rpois(double lambda) {
    return R::rpois(lambda);
}

inline double rnorm(double mean, double sd) {
    return R::rnorm(mean, sd);
}

inline vec rnorm(vec mean, vec sd) {
    vec r = vec(mean.size());
    for (uint i = 0; i < r.size(); i++)
        r[i] = rnorm(mean[i], sd[i]);
    return r;
}

inline double dnorm(double x, double mean, double sd, bool log = false) {
    return R::dnorm(x, mean, sd, log);
}

inline vec dnorm(vec x, vec mean, vec sd, bool log = false) {
    vec p = vec(x.size());
    for (uint i = 0; i < p.size(); i++)
        p[i] = dnorm(x[i], mean[i], sd[i], log);
    return p;
}

}
