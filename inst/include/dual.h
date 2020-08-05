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
inline dual operator+(const dual& x, const dual& y) {
    return dual(x.r + y.r, x.e + y.e);
}
template <typename A>
inline dual operator+(const dual& x, const A& a) {
    return dual(x.r + a, x.e);
}
template <typename A>
inline dual operator+(const A& a, const dual& x) {
    return x + a;
}
inline vector<dual> operator+(const vector<dual>& xv, const vector<dual>& yv) {
    auto v = vector<dual>(xv.size());
    for (uint i = 0; i < v.size(); i++)
        v[i] = xv[i] + yv[i];
    return v;
}

// --- - ----------------------------------------
inline dual operator-(const dual& x, const dual& y) {
    return dual(x.r - y.r, x.e - y.e);
}
template <typename A>
inline dual operator-(const dual& x, const A& a) {
    return dual(x.r - a, x.e);
}
template <typename A>
inline dual operator-(const A& a, const dual& x) {
    return dual(a - x.r, -x.e);
}
inline vector<dual> operator-(const vector<dual>& xv, const vector<dual>& yv) {
    auto v = vector<dual>(xv.size());
    for (uint i = 0; i < v.size(); i++)
        v[i] = xv[i] - yv[i];
    return v;
}

// --- * ----------------------------------------
inline dual operator*(const dual& x, const dual& y) {
    return dual(x.r*y.r, x.e*y.r + x.r*y.e);
}
template <typename A>
inline dual operator*(const dual& x, const A& a) {
    return dual(x.r*a, x.e*a);
}
template <typename A>
inline dual operator*(const A& a, const dual& x) {
    return x*a;
}
inline vector<dual> operator*(const vector<dual>& xv, const vector<dual>& yv) {
    auto v = vector<dual>(xv.size());
    for (uint i = 0; i < v.size(); i++)
        v[i] = xv[i]*yv[i];
    return v;
}
inline vector<dual> operator*(const dual& x, const vector<dual>& v) {
    auto xv = vector<dual>(v.size());
    transform(v.begin(), v.end(), xv.begin(),
              [x](const dual& ve){ return x*ve; });
    return xv;
}
inline vector<dual> operator*(const vector<dual>& v, const dual& x) {
    return x*v;
}

// --- / ----------------------------------------
inline dual operator/(const dual& x, const dual& y) {
    return dual(x.r/y.r, (x.r*y.e + x.e*y.r)/(y.r*y.r));
}
template <typename A>
inline dual operator/(const dual& x, const A& a) {
    return dual(x.r/a, x.e/a);
}
template <typename A>
inline dual operator/(const A& a, const dual& x) {
    return dual(a/x.r, (a*x.e)/(x.r*x.r));
}

// --- << ---------------------------------------
inline ostream& operator<<(ostream& os, const dual& x) {
    os << "(" << x.r << " + " << x.e << "e)";
    return os;
}

// --- arma converters ----------------------------------------------------------------------------

inline vector<dual> dual_vec(const vec& sv) {
    auto dv = vector<dual>(sv.size());
    transform(sv.begin(), sv.end(), dv.begin(),
              [](const double s){ return dual(s); });
    return dv;
}

inline vec single_vec(const vector<dual>& dv) {
    vec sv = vec(dv.size());
    transform(dv.begin(), dv.end(), sv.begin(),
              [](const dual& d){ return d.r; });
    return sv;
}

}
