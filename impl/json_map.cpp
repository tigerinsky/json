#include "../json_obj.h"

namespace tis {
namespace json {

JsonObj*& JsonMap::operator[](const char* key) {
    return _map[key]; 
}

}
}
