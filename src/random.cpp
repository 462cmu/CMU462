#include "random.h"

#include <random>

#include "misc.h"

namespace CMU462 {

std::mt19937 *init_rand() {
  std::uniform_int_distribution<int> dist(0,INT_MAX);
  std::random_device rd;
  return new std::mt19937(dist(rd));
}

static std::mt19937 *gen = init_rand();

double random_uniform() {
  return std::uniform_real_distribution<double>()(*gen);
}

Vector2D random_disk() {
  double r = sqrt(random_uniform());
  double theta = 2 * PI * random_uniform();
  return Vector2D(r * cos(theta), r * sin(theta));
}

Vector3D random_uniform_sphere() {
  double r1 = random_uniform();
  double r2 = random_uniform();
  double sinTheta = 2 * sqrt(r1 * (1 - r1));
  double phi = 2 * PI * r2;
  return Vector3D(cos(phi) * sinTheta, sin(phi) * sinTheta, 1 - 2 * r1);
}

Vector3D random_uniform_hemisphere() {
  double r1 = random_uniform();
  double r2 = random_uniform();
  double sinTheta = sqrt(1 - r1 * r1);
  double phi = 2 * PI * r2;
  return Vector3D(cos(phi) * sinTheta, sin(phi) * sinTheta, r1);
}

Vector3D random_cosine_hemisphere() {
  const Vector2D& p = random_disk();
  return Vector3D(p.x, p.y, sqrt(1 - p.x * p.x - p.y * p.y));
}

Vector2D random_bcoords() {
  double r1 = random_uniform();
  double r2 = random_uniform();
  double sqrt1 = sqrt(r1);
  return Vector2D(1 - sqrt1, r2 * sqrt1);
}

} // namespace CMU462
