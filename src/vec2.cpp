#include "vec2.h"

namespace CMU462 {

  std::ostream& operator<<( std::ostream& os, const Vec2& v ) {
    os << "( " << v.x << ", " << v.y << " )";
    return os;
  }

} // namespace CMU462
