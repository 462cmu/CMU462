#ifndef CMU462_MAT3_H
#define CMU462_MAT3_H

#include <iosfwd>

#include "vec3.h"

namespace CMU462 {

/**
 * Defines a 3x3 matrix.
 * 3x3 matrices are extremely useful in computer graphics.
 */
class Mat3 {

  public:

  // The default constructor.
  Mat3(void) { }

  // Constructor for row major form data.
  // Transposes to the internal column major form.
  // REQUIRES: data should be of size 9 for a 3 by 3 matrix..
  Mat3(double * data)
  {
    for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 3; j++ )
    {
	  // Transpostion happens within the () query.
	  (*this)(i,j) = data[i*3 + j];
    }

  }



  /**
   * Sets all elements to val.
   */
  void zero(double val = 0.0 );

  /**
   * Returns the determinant of A.
   */
  double det( void ) const;

  /**
   * Returns the Frobenius norm of A.
   */
  double norm( void ) const;

  /**
   * Returns the 3x3 identity matrix.
   */
  static Mat3 identity( void );

  /**
   * Returns a matrix representing the (left) cross product with u.
   */
  static Mat3 crossProduct( const Vec3& u );

  /**
   * Returns the ith column.
   */
        Vec3& column( int i );
  const Vec3& column( int i ) const;

  /**
   * Returns the transpose of A.
   */
  Mat3 T( void ) const;

  /**
   * Returns the inverse of A.
   */
  Mat3 inv( void ) const;

  // accesses element (i,j) of A using 0-based indexing
        double& operator()( int i, int j );
  const double& operator()( int i, int j ) const;

  // accesses the ith column of A
        Vec3& operator[]( int i );
  const Vec3& operator[]( int i ) const;

  // increments by B
  void operator+=( const Mat3& B );

  // returns -A
  Mat3 operator-( void ) const;

  // returns A-B
  Mat3 operator-( const Mat3& B ) const;

  // returns c*A
  Mat3 operator*( double c ) const;

  // returns A*B
  Mat3 operator*( const Mat3& B ) const;

  // returns A*x
  Vec3 operator*( const Vec3& x ) const;

  // divides each element by x
  void operator/=( double x );

  protected:

  // column vectors
  Vec3 entries[3];

}; // class Mat3

// returns the outer product of u and v
Mat3 outer( const Vec3& u, const Vec3& v );

// returns c*A
Mat3 operator*( double c, const Mat3& A );

// prints entries
std::ostream& operator<<( std::ostream& os, const Mat3& A );

} // namespace CMU462

#endif // CMU462_MAT3_H
