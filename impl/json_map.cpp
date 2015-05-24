#include "../json_obj.h"

namespace tis {
namespace json {

JsonObj*& JsonMap::operator[](const char* key) {
    return _map[key]; 
}

iterator_t JsonMap::begin() {
    return _map.begin();
}

iterator_t JsonMap::end() {
    return _map.end();
}

}
}
