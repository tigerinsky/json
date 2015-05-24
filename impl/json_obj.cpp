#include "../json_obj.h"

namespace tis {
namespace json {

std::ostream& operator<<(std::ostream& os, const JsonObj& o) {
        const JsonObj* obj = &o;
        switch (o.type()) {
        case STRING:
            os << *((JsonString*)obj); 
        case NUMBER:
            os << *((JsonNumber*)obj); 
        case MAP:
            os << *((JsonMap*)obj); 
        case ARRAY:
            os << *((JsonArray*)obj); 
        case BOOL:
            os << *((JsonBool*)obj); 
        case NIL:
            os << *((JsonNil*)obj); 
        } 
        return os;
}

}
}
