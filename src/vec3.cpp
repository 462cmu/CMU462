#include "vec3.h"

namespace CMU462 {

  std::ostream& operator<<( std::ostream& os, const Vec3& v ) {
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    return os;
  }

} // namespace CMU462
