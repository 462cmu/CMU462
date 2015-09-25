#include "vec4.h"

namespace CMU462 {

  std::ostream& operator<<( std::ostream& os, const Vec4& v ) {
    os << "{ " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " }";
    return os;
  }

  Vec3 Vec4::to3D() {
    return Vec3(x, y, z);
  }

} // namespace CMU462
