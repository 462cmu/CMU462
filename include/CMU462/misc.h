#ifndef CMU462_MISC_H
#define CMU462_MISC_H

#include <cmath>
#include <limits>
#include <utility>

#define PI (3.14159265358979323)
#define EPS_D (0.00000000001)
#define EPS_F (0.00001f)
#define INF_D (std::numeric_limits<double>::infinity())
#define INF_F (std::numeric_limits<float>::infinity())

namespace CMU462 {

/*
  Takes any kind of number and converts from degrees to radians.
*/
template<typename T>
inline T radians(T deg) {
  return deg * (PI / 180);
}

/*
  Takes any kind of number and converts from radians to degrees.
*/
template<typename T>
inline T degrees(T rad) {
  return rad * (180 / PI);
}

/*
  Takes any kind of number, as well as a lower and upper bound, and clamps the
  number to be within the bound.
  NOTE: x, lo, and hi must all be the same type or compilation will fail. A
        common mistake is to pass an int for x and size_ts for lo and hi.
*/
template<typename T>
inline T clamp(T x, T lo, T hi) {
  return std::min(std::max(x, lo), hi);
}

} // namespace CMU462

#endif // CMU462_MISCMATH_H
