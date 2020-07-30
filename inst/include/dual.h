#pragma once

#include <iostream>

namespace core {

using namespace std;
using namespace arma;

// --- definition ---------------------------------------------------------------------------------

struct dual {
    double r;
    double e;
    dual() : r(0), e(0) {}
    dual(double r) : r(r), e(0) {}
    dual(double r, double e) : r(r), e(e) {}
};

// --- operators ----------------------------------------------------------------------------------

// --- + ----------------------------------------
inline dual operator+(const dual &x, const dual &y) {
    return dual(x.r + y.r, x.e + y.e);
}
template <typename A>
inline dual operator+(const dual &x, const A &a) {
    return dual(x.r + a, x.e);
}
template <typename A>
inline dual operator+(const A &a, const dual &x) {
    return x + a;
}

// --- - ----------------------------------------
inline dual operator-(const dual &x, const dual &y) {
    return dual(x.r - y.r, x.e - y.e);
}
template <typename A>
inline dual operator-(const dual &x, const A &a) {
    return dual(x.r - a, x.e);
}
template <typename A>
inline dual operator-(const A &a, const dual &x) {
    return dual(a - x.r, -x.e);
}

// --- * ----------------------------------------
inline dual operator*(const dual &x, const dual &y) {
    return dual(x.r*y.r, x.e*y.r + x.r*y.e);
}
template <typename A>
inline dual operator*(const dual &x, const A &a) {
    return dual(x.r*a, x.e*a);
}
template <typename A>
inline dual operator*(const A &a, const dual &x) {
    return x*a;
}

// --- / ----------------------------------------
inline dual operator/(const dual &x, const dual &y) {
    return dual(x.r/y.r, (x.r*y.e + x.e*y.r)/(y.r*y.r));
}
template <typename A>
inline dual operator/(const dual &x, const A &a) {
    return dual(x.r/a, x.e/a);
}
template <typename A>
inline dual operator/(const A &a, const dual &x) {
    return dual(a/x.r, (a*x.e)/(x.r*x.r));
}

// --- << ---------------------------------------
ostream& operator<<(ostream& os, const dual& x) {
    os << "(" << x.r << " + " << x.e << "e)";
    return os;
}

// --- arma ---------------------------------------------------------------------------------------

vector<dual> dual_vec(vec& av) {
    auto v = vector<dual>(av.size());
    for (uint i = 0; i < v.size(); i++)
        v[i] = dual(av[i]);
    return v;
}

}
