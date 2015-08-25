#include "vector2D.h"

namespace CSD462 {

  std::ostream& operator<<( std::ostream& os, const Vector2D& v ) {
    os << "( " << v.x << ", " << v.y << " )";
    return os;
  }

} // namespace CSD462
