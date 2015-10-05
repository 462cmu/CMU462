#ifndef CMU462_RANDOM_H
#define CMU462_RANDOM_H

#include "vector2d.h"
#include "vector3d.h"

namespace CMU462 {

/**
 * Returns a uniform random number from [0, 1).
 */
double random_uniform();

/**
 * Returns a uniform random point within the unit disk.
 */
Vector2D random_disk();

/**
 * Returns a uniform random point on the surface of the unit sphere.
 */
Vector3D random_uniform_sphere();

/**
 * Returns a uniform random point on the surface of the unit hemisphere.
 */
Vector3D random_uniform_hemisphere();

/**
 * Returns a random point on the surface of the unit hemisphere, where p(v) is
 * proportional to v's angle off of the vertical.
 */
Vector3D random_cosine_hemisphere();

/**
 * Returns two random barycentric coordinates, distributed such that all points
 * in a triangle are uniformly likely.
 */
Vector2D random_bcoords();

} // namespace CMU462

#endif //CMU462_RANDOM_H
