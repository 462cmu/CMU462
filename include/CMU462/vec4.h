#ifndef CMU462_VEC4_H
#define CMU462_VEC4_H

#include <ostream>
#include <cmath>
#include "vec3.h"

namespace CMU462 {

/**
 * Defines 4D standard vectors.
 */
class Vec4 {
 public:

  // components
  double x, y, z, w;

  /**
   * Constructor.
   * Initializes tp vector (0,0,0, 0).
   */
 Vec4() : x( 0.0 ), y( 0.0 ), z( 0.0 ), w( 0.0 ) { }

  /**
   * Constructor.
   * Initializes to vector (x,y,z,w).
   */
 Vec4( double x, double y, double z, double w) : x( x ), y( y ), z( z ), w( w ) { }

  /**
   * Constructor.
   * Initializes to vector (x,y,z,0).
   */
 Vec4( double x, double y, double z) : x( x ), y( y ), z( z ), w( 0.0 ) { }


  /**
   * Constructor.
   * Initializes to vector (c,c,c,c)
   */
 Vec4( double c ) : x( c ), y( c ), z( c ), w ( c ) { }

  /**
   * Constructor.
   * Initializes from existing Vec4.
   */
 Vec4( const Vec4& v ) : x( v.x ), y( v.y ), z( v.z ), w( v.w ) { }

  /**
   * Constructor.
   * Initializes from existing Vec3.
   */
 Vec4( const Vec3& v ) : x( v.x ), y( v.y ), z( v.z ), w( 0.0 ) { }

  // returns reference to the specified component (0-based indexing: x, y, z)
  inline double& operator[] ( const int& index ) {
    return ( &x )[ index ];
  }

  // returns const reference to the specified component (0-based indexing: x, y, z)
  inline const double& operator[] ( const int& index ) const {
    return ( &x )[ index ];
  }

  // negation
  inline Vec4 operator-( void ) const {
    return Vec4( -x, -y, -z, -w);
  }

  // addition
  inline Vec4 operator+( const Vec4& v ) const {
    return Vec4( x + v.x, y + v.y, z + v.z, w + v.w);
  }

  // subtraction
  inline Vec4 operator-( const Vec4& v ) const {
    return Vec4( x - v.x, y - v.y, z - v.z, w - v.w );
  }

  // right scalar multiplication
  inline Vec4 operator*( const double& c ) const {
    return Vec4( x * c, y * c, z * c, w * c );
  }

  // scalar division
  inline Vec4 operator/( const double& c ) const {
    const double rc = 1.0/c;
    return Vec4( rc * x, rc * y, rc * z, rc * w );
  }

  // addition / assignment
  inline void operator+=( const Vec4& v ) {
    x += v.x; y += v.y; z += v.z; z += v.w;
  }

  // subtraction / assignment
  inline void operator-=( const Vec4& v ) {
    x -= v.x; y -= v.y; z -= v.z; w -= v.w;
  }

  // scalar multiplication / assignment
  inline void operator*=( const double& c ) {
    x *= c; y *= c; z *= c; z *= c;
  }

  // scalar division / assignment
  inline void operator/=( const double& c ) {
    (*this) *= ( 1./c );
  }

  /**
   * Returns Euclidean distance metric extended to 4 dimensions.
   */
  inline double norm( void ) const {
    return sqrt( x*x + y*y + z*z + w*w );
  }

  /**
   * Returns Euclidean length squared.
   */
  inline double norm2( void ) const {
    return x*x + y*y + z*z + w*w;
  }

  /**
   * Returns unit vector. (returns the normalized copy of this vector.)
   */
  inline Vec4 unit( void ) const {
    double rNorm = 1. / sqrt( x*x + y*y + z*z + w*w);
    return Vec4( rNorm*x, rNorm*y, rNorm*z );
  }

  /**
   * Divides by Euclidean length.
   * This vector will be of unit length i.e. "normalized" afterwards.
   */
  inline void normalize( void ) {
    (*this) /= norm();
  }

  /**
   * Converts this vector to a 3D vector ignoring the w component.
   */
  Vec3 to3D();

}; // class Vec4

// left scalar multiplication
inline Vec4 operator* ( const double& c, const Vec4& v ) {
  return Vec4( c * v.x, c * v.y, c * v.z, c*v.w );
}

// dot product (a.k.a. inner or scalar product)
inline double dot( const Vec4& u, const Vec4& v ) {
  return u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w;;
}

// prints components
std::ostream& operator<<( std::ostream& os, const Vec3& v );

} // namespace CMU462

#endif // CMU462_VEC4_H
