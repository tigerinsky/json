#include "../json_obj.h"

namespace tis {
namespace json {

size_t JsonArray::size() {
    return _vector.size();
}

JsonObj*& JsonArray::operator[](size_t idx) {
    return _vector[idx]; 
}

JsonObj* JsonArray::get(size_t idx) {
    return _vector[idx];
}

void JsonArray::push_back(JsonObj* obj) {
    _vector.push_back(obj);
}

}
}
