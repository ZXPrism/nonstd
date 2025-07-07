#pragma once

#include <math/linalg/nstd_matrix.h>

/*
 * ! assumptions !
 * 1. use a right-handed Cartesian coordinate system
 * 2. vectors are all column vectors (i.e. Nx1)
 * 3. use row-major ordering storage layout
 */

namespace nstd {

namespace linalg {

using vector2i = matrix<int, 2, 1, false>;
using vector3i = matrix<int, 3, 1, false>;
using vector4i = matrix<int, 4, 1, false>;

using vector2ll = matrix<long long, 2, 1, false>;
using vector3ll = matrix<long long, 3, 1, false>;
using vector4ll = matrix<long long, 4, 1, false>;

using vector2ull = matrix<unsigned long long, 2, 1, false>;
using vector3ull = matrix<unsigned long long, 3, 1, false>;
using vector4ull = matrix<unsigned long long, 4, 1, false>;

using vector2f = matrix<float, 2, 1, false>;
using vector3f = matrix<float, 3, 1, false>;
using vector4f = matrix<float, 4, 1, false>;

using vector2d = matrix<double, 2, 1, false>;
using vector3d = matrix<double, 3, 1, false>;
using vector4d = matrix<double, 4, 1, false>;

}  // namespace linalg

}  // namespace nstd
