#include "../json_obj.h"

namespace tis {
namespace json {

size_t JsonArray::size() const {
    return _vector.size();
}

JsonObj*& JsonArray::operator[](size_t idx){
    return _vector[idx]; 
}

JsonObj* JsonArray::get(size_t idx) const {
    return _vector[idx];
}

void JsonArray::push_back(JsonObj* obj) {
    _vector.push_back(obj);
}

std::ostream& operator<<(std::ostream& os, const JsonArray& arr) {
    os << '[';
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        os << *(arr.get(i));
        os << ", ";
    }
    if (arr.size() > 0) {
        os << arr.get(arr.size() - 1);
    }
    return os << ']';
}

}
}
