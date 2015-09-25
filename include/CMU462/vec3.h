#ifndef CMU462_VEC3_H
#define CMU462_VEC3_H

#include <ostream>
#include <cmath>

namespace CMU462 {

/** 
 * Defines 3D vectors.
 */
class Vec3 {
 public:

  // components
  double x, y, z;

  /**
   * Constructor.
   * Initializes tp vector (0,0,0).
   */
  Vec3() : x( 0.0 ), y( 0.0 ), z( 0.0 ) { }

  /**
   * Constructor.
   * Initializes to vector (x,y,z).
   */
  Vec3( double x, double y, double z) : x( x ), y( y ), z( z ) { }

  /**
   * Constructor.
   * Initializes to vector (c,c,c)
   */
  Vec3( double c ) : x( c ), y( c ), z( c ) { }

  /**
   * Constructor.
   * Initializes from existing vector
   */
  Vec3( const Vec3& v ) : x( v.x ), y( v.y ), z( v.z ) { }
   
  // returns reference to the specified component (0-based indexing: x, y, z)
  inline double& operator[] ( const int& index ) {
    return ( &x )[ index ];
  }
  
  // returns const reference to the specified component (0-based indexing: x, y, z)
  inline const double& operator[] ( const int& index ) const {
    return ( &x )[ index ];
  }

  // negation
  inline Vec3 operator-( void ) const {
    return Vec3( -x, -y, -z );
  }

  // addition
  inline Vec3 operator+( const Vec3& v ) const {
    return Vec3( x + v.x, y + v.y, z + v.z );
  }

  // subtraction
  inline Vec3 operator-( const Vec3& v ) const {
    return Vec3( x - v.x, y - v.y, z - v.z );
  }

  // right scalar multiplication
  inline Vec3 operator*( const double& c ) const {
    return Vec3( x * c, y * c, z * c );
  }

  // scalar division
  inline Vec3 operator/( const double& c ) const {
    const double rc = 1.0/c;
    return Vec3( rc * x, rc * y, rc * z );
  }

  // addition / assignment
  inline void operator+=( const Vec3& v ) {
    x += v.x; y += v.y; z += v.z;
  }

  // subtraction / assignment
  inline void operator-=( const Vec3& v ) {
    x -= v.x; y -= v.y; z -= v.z;
  }

  // scalar multiplication / assignment
  inline void operator*=( const double& c ) {
    x *= c; y *= c; z *= c;
  }

  // scalar division / assignment
  inline void operator/=( const double& c ) {
    (*this) *= ( 1./c );
  }

  /**
   * Returns Euclidean length.
   */
  inline double norm( void ) const {
    return sqrt( x*x + y*y + z*z );
  }

  /**
   * Returns Euclidean length squared.
   */
  inline double norm2( void ) const {
    return x*x + y*y + z*z;
  }

  /**
   * Returns unit vector.
   */
  inline Vec3 unit( void ) const {
    double rNorm = 1. / sqrt( x*x + y*y + z*z );
    return Vec3( rNorm*x, rNorm*y, rNorm*z );
  }

  /**
   * Divides by Euclidean length.
   */
  inline void normalize( void ) {
    (*this) /= norm();  
  }

}; // class Vec3

// left scalar multiplication
inline Vec3 operator* ( const double& c, const Vec3& v ) {
  return Vec3( c * v.x, c * v.y, c * v.z );
}

// dot product (a.k.a. inner or scalar product)
inline double dot( const Vec3& u, const Vec3& v ) {
  return u.x*v.x + u.y*v.y + u.z*v.z ;
}

// cross product
inline Vec3 cross( const Vec3& u, const Vec3& v ) {
  return Vec3( u.y*v.z - u.z*v.y,
                   u.z*v.x - u.x*v.z,
                   u.x*v.y - u.y*v.x );
}

// prints components
std::ostream& operator<<( std::ostream& os, const Vec3& v );

} // namespace CMU462

#endif // CMU462_VEC3_H
