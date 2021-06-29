#pragma once

#include <RcppArmadillo.h>
#include <random>

namespace core {

using namespace std;
using uint = unsigned int;

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

class rng {
public:
    rng() {
        random_device rd;
        gen = mt19937(rd());
    }
    double uniform(double min = 0, double max = 1) {
        return u(gen, uniform_real_distribution<>::param_type(min, max));
    }
    double normal(double mean = 0, double sd = 1) {
        return n(gen, normal_distribution<>::param_type(mean, sd));
    }
    int poisson(double lambda = 1) {
        return p(gen, poisson_distribution<>::param_type(lambda));
    }
protected:
    uniform_real_distribution<> u;
    normal_distribution<> n;
    poisson_distribution<> p;
    mt19937 gen;
};


}
