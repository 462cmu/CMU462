#include "vector3D.h"

namespace CSD462 {

  std::ostream& operator<<( std::ostream& os, const Vector3D& v ) {
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    return os;
  }

} // namespace CSD462
