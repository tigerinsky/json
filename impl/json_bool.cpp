#include "../json_obj.h"

namespace tis {
namespace json {

std::ostream& operator<<(std::ostream& os, const JsonBool& b) {
    if (b._bool) {
        return os << "true";
    } else {
        return os << "false";
    }
}

}
}
