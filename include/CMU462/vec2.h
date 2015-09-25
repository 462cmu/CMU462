#ifndef CMU462_VEC2_H
#define CMU462_VEC2_H

#include <ostream>
#include <cmath>

namespace CMU462 {

/** 
 * Defines 2D vectors.
 */
class Vec2 { 
 public:
  
  // components
  double x, y;

  /**
   * Constructor.
   * Initializes to vector (0,0).
   */
  Vec2() : x( 0.0 ), y( 0.0 ) { }

  /**
   * Constructor.
   * Initializes to vector (a,b).
   */
  Vec2( double x, double y ) : x( x ), y( y ) { }

  /**
   * Constructor.
   * Copy constructor. Creates a copy of the given vector.
   */
  Vec2( const Vec2& v ) : x( v.x ), y( v.y ) { }

  // additive inverse
  inline Vec2 operator-( void ) const {
    return Vec2( -x, -y );
  } 

  // addition
  inline Vec2 operator+( const Vec2& v ) const {
    Vec2 u = *this;
    u += v;
    return u;
  }
  
  // subtraction
  inline Vec2 operator-( const Vec2& v ) const {
    Vec2 u = *this;
    u -= v;
    return u;
  }

  // right scalar multiplication
  inline Vec2 operator*( double r ) const {
    Vec2 vr = *this;
    vr *= r;
    return vr;
  }
  
  // scalar division
  inline Vec2 operator/( double r ) const {
    Vec2 vr = *this;
    vr /= r;
    return vr;
  }

  // add v
  inline void operator+=( const Vec2& v ) {
    x += v.x;
    y += v.y;
  }

  // subtract v
  inline void operator-=( const Vec2& v ) {
    x -= v.x;
    y -= v.y;
  }

  // scalar multiply by r
  inline void operator*=( double r ) {
    x *= r;
    y *= r;
  }

  // scalar divide by r
  inline void operator/=( double r ) {
    x /= r;
    y /= r;
  }

  /**
   * Returns norm.
   */
  inline double norm( void ) const {
    return sqrt( x*x + y*y );
  }

  /**
   * Returns norm squared.
   */
  inline double norm2( void ) const {
    return x*x + y*y;
  }

  /** 
   * Returns unit vector parallel to this one.
   */
  inline Vec2 unit( void ) const {
    return *this / this->norm();
  }


}; // clasd Vec2

// left scalar multiplication
inline Vec2 operator*( double r, const Vec2& v ) {
   return v*r;
}

// inner product
inline double dot( const Vec2& v1, const Vec2& v2 ) {
  return v1.x*v2.x + v1.y*v2.y;
}

// cross product
inline double cross( const Vec2& v1, const Vec2& v2 ) {
  return v1.x*v2.y - v1.y*v2.x;
}

// prints components
std::ostream& operator<<( std::ostream& os, const Vec2& v );
   
} // namespace CMU462

#endif // CMU462_VEC2_H
