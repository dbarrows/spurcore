#pragma once

// Note: do not put these structs into another namespace - compilation will break

#include <RcppArmadillo.h>

// hashing and equality functions for arma::uvec3.
// Required to use arma::uvec3 as a key in std::map.

namespace core {

using namespace std;
using namespace arma;

template <typename VOUT, typename VIN>
inline VOUT vector_cast(VIN v) {
    VOUT out = VOUT(v.size());
    for (uint i = 0; i < v.size(); i++)
        out[i] = v[i];
    return out;
}

}

namespace std {

template <>
struct hash<typename arma::uvec3> {
    std::size_t operator()(const typename arma::uvec3& k) const {
        size_t res = 17;
        res *= 31 + std::hash<uint>()(k[0]);
        res *= 31 + std::hash<uint>()(k[1]);
        res *= 31 + std::hash<uint>()(k[2]);
        return res;
    }
};
template <>
struct equal_to<typename arma::uvec3> {
    bool operator()(const typename arma::uvec3& a, const typename arma::uvec3& b) const {
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }
};
template<>
struct less<typename arma::uvec3> {
    bool operator() (const typename arma::uvec3& a, const typename arma::uvec3& b) const{
        return a[2] < b[2] ||
            (a[2] == b[2] && a[1] < b[1]) ||
            (a[2] == b[2] && a[2] == b[2] && a[0] < b[0]);
    }
};

}
