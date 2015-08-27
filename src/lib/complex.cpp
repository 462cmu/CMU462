#include "complex.h"

namespace CSD462 {
  
  std::ostream& operator<<( std::ostream& os, const Complex& z ) {
    if( z.y > 0 ) {
       os << z.x << " + " << z.y << "i";
    } else if( z.y < 0 ) {
       os << z.x << " - " << -z.y << "i";
    } else {
       os << z.x;
    }
    return os;
  }

} // namespace CSD462