#include "../json_obj.h"
#include "../json.h"

namespace tis {
namespace json {

std::string& JsonObj::_escape(const char* s, size_t len) const {
    _json->escape_string(s, len);
    return _json->_serialize_buf;
}

std::ostream& operator<<(std::ostream& os, const JsonObj& o) {
        const JsonObj* obj = &o;
        switch (o.type()) {
        case STRING:
            return os << *((JsonString*)obj); 
        case NUMBER:
            return os << *((JsonNumber*)obj); 
        case MAP:
            return os << *((JsonMap*)obj); 
        case ARRAY:
            return os << *((JsonArray*)obj); 
        case BOOL:
            return os << *((JsonBool*)obj); 
        case NIL:
            return os << *((JsonNil*)obj); 
        } 
        return os;
}

}
}
