#ifndef CMU462_MAT4_H
#define CMU462_MAT4_H

#include <iosfwd>

#include "vec4.h"

namespace CMU462 {

/**
 * Defines a 4x4 matrix.
 * 4x4 matrices are also extremely useful in computer graphics.
 * Written by Bryce Summers on 9/10/2015.
 * Adapted from the Mat3 class.
 *
 * EXTEND_ME : It might be nice to add some combined operations
 *             such as multiplying then adding,
 *             etc to increase arithmetic intensity.
 * I have taken the liberty of removing cross product functionality form 4D Matrices and Vectors.
 */
class Mat4 {

  public:


  // The default constructor.
  Mat4(void) { }

  // Constructor for row major form data.
  // Transposes to the internal column major form.
  // REQUIRES: data should be of size 16.
  Mat4(double * data)
  {
    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
	  // Transpostion happens within the () query.
	  (*this)(i,j) = data[i*4 + j];
    }

  }


  /**
   * Sets all elements to val.
   */
  void zero(double val = 0.0);

  /**
   * Returns the determinant of A.
   */
  double det( void ) const;

  /**
   * Returns the Frobenius norm of A.
   */
  double norm( void ) const;

  /**
   * Returns a fresh 4x4 identity matrix.
   */
  static Mat4 identity( void );

  // No Cross products for 4 by 4 matrix.

  /**
   * Returns the ith column.
   */
        Vec4& column( int i );
  const Vec4& column( int i ) const;

  /**
   * Returns the transpose of A.
   */
  Mat4 T( void ) const;

  /**
   * Returns the inverse of A.
   */
  Mat4 inv( void ) const;

  // accesses element (i,j) of A using 0-based indexing
  // where (i, j) is (row, column).
        double& operator()( int i, int j );
  const double& operator()( int i, int j ) const;

  // accesses the ith column of A
        Vec4& operator[]( int i );
  const Vec4& operator[]( int i ) const;

  // increments by B
  void operator+=( const Mat4& B );

  // returns -A
  Mat4 operator-( void ) const;

  // returns A-B
  Mat4 operator-( const Mat4& B ) const;

  // returns c*A
  Mat4 operator*( double c ) const;

  // returns A*B
  Mat4 operator*( const Mat4& B ) const;

  // returns A*x
  Vec4 operator*( const Vec4& x ) const;

  // divides each element by x
  void operator/=( double x );

  protected:

  // 4 by 4 matrices are represented by an array of 4 column vectors.
  Vec4 entries[4];

}; // class Mat3

// returns the outer product of u and v.
Mat4 outer( const Vec4& u, const Vec4& v );

// returns c*A
Mat4 operator*( double c, const Mat4& A );

// prints entries
std::ostream& operator<<( std::ostream& os, const Mat4& A );

} // namespace CMU462

#endif // CMU462_MAT4_H
