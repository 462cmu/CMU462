#include "mat4.h"

#include <iostream>
#include <cmath>

using namespace std;

namespace CMU462 {

  double& Mat4::operator()( int i, int j ) {
    return entries[j][i];
  }

  const double& Mat4::operator()( int i, int j ) const {
    return entries[j][i];
  }

  Vec4& Mat4::operator[]( int j ) {
      return entries[j];
  }

  const Vec4& Mat4::operator[]( int j ) const {
    return entries[j];
  }

  void Mat4::zero( double val ) {
    // sets all elements to val
    entries[0] =
	  entries[1] =
	  entries[2] =
	  entries[3] = Vec4( val, val, val, val );
  }

  double Mat4::det( void ) const {
    const Mat4& A( *this );

	return
	  A(0,3)*A(1,2)*A(2,1)*A(3,0) - A(0,2)*A(1,3)*A(2,1)*A(3,0) -
	  A(0,3)*A(1,1)*A(2,2)*A(3,0) + A(0,1)*A(1,3)*A(2,2)*A(3,0) +
	  A(0,2)*A(1,1)*A(2,3)*A(3,0) - A(0,1)*A(1,2)*A(2,3)*A(3,0) -
	  A(0,3)*A(1,2)*A(2,0)*A(3,1) + A(0,2)*A(1,3)*A(2,0)*A(3,1) +
	  A(0,3)*A(1,0)*A(2,2)*A(3,1) - A(0,0)*A(1,3)*A(2,2)*A(3,1) -
	  A(0,2)*A(1,0)*A(2,3)*A(3,1) + A(0,0)*A(1,2)*A(2,3)*A(3,1) +
	  A(0,3)*A(1,1)*A(2,0)*A(3,2) - A(0,1)*A(1,3)*A(2,0)*A(3,2) -
	  A(0,3)*A(1,0)*A(2,1)*A(3,2) + A(0,0)*A(1,3)*A(2,1)*A(3,2) +
	  A(0,1)*A(1,0)*A(2,3)*A(3,2) - A(0,0)*A(1,1)*A(2,3)*A(3,2) -
	  A(0,2)*A(1,1)*A(2,0)*A(3,3) + A(0,1)*A(1,2)*A(2,0)*A(3,3) +
	  A(0,2)*A(1,0)*A(2,1)*A(3,3) - A(0,0)*A(1,2)*A(2,1)*A(3,3) -
	  A(0,1)*A(1,0)*A(2,2)*A(3,3) + A(0,0)*A(1,1)*A(2,2)*A(3,3);

  }

  double Mat4::norm( void ) const {
    return sqrt( entries[0].norm2() +
                 entries[1].norm2() +
                 entries[2].norm2() +
				         entries[3].norm2());
  }

  Mat4 Mat4::operator-( void ) const {

  // returns -A (Negation).
  const Mat4& A( *this );
  Mat4 B;

  B(0,0) = -A(0,0); B(0,1) = -A(0,1); B(0,2) = -A(0,2); B(0,3) = -A(0,3);
  B(1,0) = -A(1,0); B(1,1) = -A(1,1); B(1,2) = -A(1,2); B(1,3) = -A(1,3);
  B(2,0) = -A(2,0); B(2,1) = -A(2,1); B(2,2) = -A(2,2); B(2,3) = -A(2,3);
	B(3,0) = -A(3,0); B(3,1) = -A(3,1); B(3,2) = -A(3,2); B(3,3) = -A(3,3);

    return B;
  }

  void Mat4::operator+=( const Mat4& B ) {

    Mat4& A( *this );
    double* Aij = (double*) &A;
    const double* Bij = (const double*) &B;

	// Add the 16 contigous vector packed double values.
    *Aij++ += *Bij++;//0
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;//4
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;//8
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;//12
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;
    *Aij++ += *Bij++;//15
	//16.

  }

  Mat4 Mat4::operator-( const Mat4& B ) const {
    const Mat4& A( *this );
    Mat4 C;

    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
       C(i,j) = A(i,j) - B(i,j);
    }

    return C;
  }

  Mat4 Mat4::operator*( double c ) const {
    const Mat4& A( *this );
    Mat4 B;

    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
       B(i,j) = c*A(i,j);
    }

    return B;
  }

  // Returns c*A.
  Mat4 operator*( double c, const Mat4& A ) {

    Mat4 cA;
    const double* Aij = (const double*) &A;
    double* cAij = (double*) &cA;

    *cAij++ = c * (*Aij++);//0
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);//4
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);//8
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);//12
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);
    *cAij++ = c * (*Aij++);//15
	//16
    return cA;
  }

  // Tradiational Grade School Multiplication. N^3
  Mat4 Mat4::operator*( const Mat4& B ) const {
    const Mat4& A( *this );
    Mat4 C;

    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
       C(i,j) = 0.;

       for( int k = 0; k < 4; k++ )
       {
          C(i,j) += A(i,k)*B(k,j);
       }
    }

    return C;
  }


  Vec4 Mat4::operator*( const Vec4& x ) const {
    return x[0]*entries[0] + // Add up products for each matrix column.
           x[1]*entries[1] +
           x[2]*entries[2] +
           x[3]*entries[3];
  }

  // Naive Transposition.
  Mat4 Mat4::T( void ) const {
    const Mat4& A( *this );
    Mat4 B;

    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
       B(i,j) = A(j,i);
    }

    return B;
  }

  Mat4 Mat4::inv( void ) const {
    const Mat4& A( *this );
    Mat4 B;

	// Hardcoded in Fully Symbolic computation.

	B(0,0) = A(1,2)*A(2,3)*A(3,1) - A(1,3)*A(2,2)*A(3,1) + A(1,3)*A(2,1)*A(3,2) - A(1,1)*A(2,3)*A(3,2) - A(1,2)*A(2,1)*A(3,3) + A(1,1)*A(2,2)*A(3,3);
	B(0,1) = A(0,3)*A(2,2)*A(3,1) - A(0,2)*A(2,3)*A(3,1) - A(0,3)*A(2,1)*A(3,2) + A(0,1)*A(2,3)*A(3,2) + A(0,2)*A(2,1)*A(3,3) - A(0,1)*A(2,2)*A(3,3);
	B(0,2) = A(0,2)*A(1,3)*A(3,1) - A(0,3)*A(1,2)*A(3,1) + A(0,3)*A(1,1)*A(3,2) - A(0,1)*A(1,3)*A(3,2) - A(0,2)*A(1,1)*A(3,3) + A(0,1)*A(1,2)*A(3,3);
	B(0,3) = A(0,3)*A(1,2)*A(2,1) - A(0,2)*A(1,3)*A(2,1) - A(0,3)*A(1,1)*A(2,2) + A(0,1)*A(1,3)*A(2,2) + A(0,2)*A(1,1)*A(2,3) - A(0,1)*A(1,2)*A(2,3);
	B(1,0) = A(1,3)*A(2,2)*A(3,0) - A(1,2)*A(2,3)*A(3,0) - A(1,3)*A(2,0)*A(3,2) + A(1,0)*A(2,3)*A(3,2) + A(1,2)*A(2,0)*A(3,3) - A(1,0)*A(2,2)*A(3,3);
	B(1,1) = A(0,2)*A(2,3)*A(3,0) - A(0,3)*A(2,2)*A(3,0) + A(0,3)*A(2,0)*A(3,2) - A(0,0)*A(2,3)*A(3,2) - A(0,2)*A(2,0)*A(3,3) + A(0,0)*A(2,2)*A(3,3);
	B(1,2) = A(0,3)*A(1,2)*A(3,0) - A(0,2)*A(1,3)*A(3,0) - A(0,3)*A(1,0)*A(3,2) + A(0,0)*A(1,3)*A(3,2) + A(0,2)*A(1,0)*A(3,3) - A(0,0)*A(1,2)*A(3,3);
	B(1,3) = A(0,2)*A(1,3)*A(2,0) - A(0,3)*A(1,2)*A(2,0) + A(0,3)*A(1,0)*A(2,2) - A(0,0)*A(1,3)*A(2,2) - A(0,2)*A(1,0)*A(2,3) + A(0,0)*A(1,2)*A(2,3);
	B(2,0) = A(1,1)*A(2,3)*A(3,0) - A(1,3)*A(2,1)*A(3,0) + A(1,3)*A(2,0)*A(3,1) - A(1,0)*A(2,3)*A(3,1) - A(1,1)*A(2,0)*A(3,3) + A(1,0)*A(2,1)*A(3,3);
	B(2,1) = A(0,3)*A(2,1)*A(3,0) - A(0,1)*A(2,3)*A(3,0) - A(0,3)*A(2,0)*A(3,1) + A(0,0)*A(2,3)*A(3,1) + A(0,1)*A(2,0)*A(3,3) - A(0,0)*A(2,1)*A(3,3);
	B(2,2) = A(0,1)*A(1,3)*A(3,0) - A(0,3)*A(1,1)*A(3,0) + A(0,3)*A(1,0)*A(3,1) - A(0,0)*A(1,3)*A(3,1) - A(0,1)*A(1,0)*A(3,3) + A(0,0)*A(1,1)*A(3,3);
	B(2,3) = A(0,3)*A(1,1)*A(2,0) - A(0,1)*A(1,3)*A(2,0) - A(0,3)*A(1,0)*A(2,1) + A(0,0)*A(1,3)*A(2,1) + A(0,1)*A(1,0)*A(2,3) - A(0,0)*A(1,1)*A(2,3);
	B(3,0) = A(1,2)*A(2,1)*A(3,0) - A(1,1)*A(2,2)*A(3,0) - A(1,2)*A(2,0)*A(3,1) + A(1,0)*A(2,2)*A(3,1) + A(1,1)*A(2,0)*A(3,2) - A(1,0)*A(2,1)*A(3,2);
	B(3,1) = A(0,1)*A(2,2)*A(3,0) - A(0,2)*A(2,1)*A(3,0) + A(0,2)*A(2,0)*A(3,1) - A(0,0)*A(2,2)*A(3,1) - A(0,1)*A(2,0)*A(3,2) + A(0,0)*A(2,1)*A(3,2);
	B(3,2) = A(0,2)*A(1,1)*A(3,0) - A(0,1)*A(1,2)*A(3,0) - A(0,2)*A(1,0)*A(3,1) + A(0,0)*A(1,2)*A(3,1) + A(0,1)*A(1,0)*A(3,2) - A(0,0)*A(1,1)*A(3,2);
	B(3,3) = A(0,1)*A(1,2)*A(2,0) - A(0,2)*A(1,1)*A(2,0) + A(0,2)*A(1,0)*A(2,1) - A(0,0)*A(1,2)*A(2,1) - A(0,1)*A(1,0)*A(2,2) + A(0,0)*A(1,1)*A(2,2);

	// Invertable iff the determinant is not equal to zero.
    B /= det();

    return B;
  }

  void Mat4::operator/=( double x ) {
    Mat4& A( *this );
    double rx = 1./x;

    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
       A( i, j ) *= rx;
    }
  }

  Mat4 Mat4::identity( void ) {
    Mat4 B;

    B(0,0) = 1.; B(0,1) = 0.; B(0,2) = 0.; B(0,3) = 0.;
    B(1,0) = 0.; B(1,1) = 1.; B(1,2) = 0.; B(1,3) = 0.;
    B(2,0) = 0.; B(2,1) = 0.; B(2,2) = 1.; B(2,3) = 0.;
    B(3,0) = 0.; B(3,1) = 0.; B(3,2) = 0.; B(3,3) = 1.;

    return B;
  }

  Mat4 outer( const Vec4& u, const Vec4& v ) {
    Mat4 B;

    // Opposite of an inner product.
    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    {
       B( i, j ) = u[i]*v[j];
    }

    return B;
  }

  std::ostream& operator<<( std::ostream& os, const Mat4& A ) {
    for( int i = 0; i < 4; i++ )
    {
       os << "[ ";

       for( int j = 0; j < 4; j++ )
       {
          os << A(i,j) << " ";
       }

       os << "]" << std::endl;
    }

    return os;
  }

  Vec4& Mat4::column( int i ) {
    return entries[i];
  }

  const Vec4& Mat4::column( int i ) const {
    return entries[i];
  }
}
