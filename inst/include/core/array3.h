#pragma once

#include <RcppArmadillo.h>

namespace core {

using namespace arma;
using namespace std;
using uint = unsigned int; // needed for compilation on Windows

template <typename T>
class array3 {
public:
    uvec3 dims;
    vector<T> data;

    array3() : array3(uvec3 { 0, 0, 0 }) {}
    array3(uvec3 dims, T seed = T()) : array3(dims[0], dims[1], dims[2], seed) {}
    array3(uint dx, uint dy, uint dz, T seed = T()) {
        dims = uvec3 { dx, dy, dz };
        data = vector<T>(dx*dy*dz, seed);
    }

    uint index(uint x, uint y, uint z) const {
        return x + y*dims[0] + z*dims[0]*dims[1];
    }
    uint index(uvec3 i) const {
        return index(i[0], i[1], i[2]);
    }
    uvec3 index3(uint i) const;
    uint size() const {
        return prod(dims);
    }

    T operator ()(uint x, uint y, uint z) const {return data[index(x, y, z)]; }
    T& operator ()(uint x, uint y, uint z) { return data[index(x, y, z)]; }

    T operator [](uint i) const { return data[i]; }
    T& operator [](uint i) { return data[i]; }

    T operator [](uvec3 i) const { return data[index(i)]; }
    T& operator [](uvec3 i) { return data[index(i)]; }

    array3<T>& operator=(const array3<T>& other);
};

template <typename T>
uvec3 array3<T>::index3(uint i) const {
    uint z = static_cast<uint>(floor(i / (dims[0]*dims[1])));
    uint y = static_cast<uint>(floor((i % (dims[0]*dims[1])) / dims[0]));
    uint x = static_cast<uint>(floor(i - (y*dims[0] + z*dims[0]*dims[1])));
    return { x, y, z };
}

template <typename T>
array3<T>& array3<T>::operator=(const array3<T>& other) {
    dims = other.dims;
    data = vector<T>(other.data.size());
    copy(other.data.begin(), other.data.end(), data.begin());
    return *this;
}

template <typename T>
array3<T> operator*(float x, array3<T>& a) {
    auto out = a;
    for (uint i = 0; i < a.size(); i++)
        out[i] = x*a[i];
    return out;
}
template <typename T>
array3<T> operator*(array3<T>& a, float x) {
    return x*a;
}

template <typename T>
array3<T> operator+(const array3<T>& x, const array3<T>& y) {
    auto out = x;
    for (uint i = 0; i < out.size(); i++)
        out[i] += y[i];
    return out;
}

template <typename T>
array3<T> round(const array3<T>& x) {
    auto out = x;
    for (uint i = 0; i < out.size(); i++)
        out[i] = round(x[i]);
    return out;
}

template <typename S>
static vector<S> flatten(array3<vector<S>>& a) {
    auto v = vector<S>();
    for (uint i = 0; i < a.size(); i++)
        for (uint j = 0; j < a[i].size(); j++)
            v.push_back(a[i][j]);
    return v;
}

}
