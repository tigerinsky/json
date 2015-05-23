#include "../json_obj.h"

namespace tis {
namespace json {

void JsonString::assign(const char* str) {
    _str.assign(str);
}

void JsonString::assign(const char* str, size_t len) {
    _str.assign(str, len);
}

}
}
