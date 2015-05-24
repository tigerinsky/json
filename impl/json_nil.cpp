#include "../json_obj.h"

namespace tis {
namespace json {

std::ostream& operator<<(std::ostream& os, const JsonNil& n) {
    return os << "null";
}

}
}
