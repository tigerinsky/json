#include "../json_obj.h"
#include "string_helper.h"
#include "../exception.h"

namespace tis {
namespace json {

void JsonString::assign(const char* str) {
    _str.assign(str);
}

void JsonString::assign(const char* str, size_t len) {
    _str.assign(str, len);
}

const char* JsonString::c_str() {
    return _str.c_str();
}

size_t JsonString::size() {
    return _str.size();
}

std::ostream& operator<<(std::ostream& os, const JsonString& s) {
    return os << s._escape(s._str.c_str(), s._str.size());
}

}
}
