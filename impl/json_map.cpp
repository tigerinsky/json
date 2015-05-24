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

size_t JsonMap::size() {
    return _map.size();
}

std::ostream& operator<<(std::ostream& os, const JsonMap& map) {
    JsonMap& map2 = (JsonMap&)map;
    os << '{';
    for (auto ite : map2) {
        os << '"' << ite.first << "\":"; 
        JsonObj* obj = ite.second;
        os << *obj << ',';
    }
    return os << '}';
}

}
}
