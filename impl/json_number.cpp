#include "../json_obj.h"
#include "../exception.h"

namespace tis {
namespace json {

void JsonNumber::set(double d) {
    _cur_type = double_type;
    _cur_value.double_value = d;
}

void JsonNumber::set(uint64_t u) {
    _cur_type = uint64_type;
    _cur_value.uint64_value = u;
}

void JsonNumber::set(int64_t i) {
    _cur_type = int64_type;
    _cur_value.int64_value = i;
}

uint64_t JsonNumber::to_uint64() const {
    switch (_cur_type) {
    case double_type: 
        if (_cur_value.double_value < 0) {
            throw InvalidOpException() <<""; 
        }
        return (uint64_t)_cur_value.double_value;
    case int64_type:
        throw InvalidOpException() << "";
    case uint64_type:
        return _cur_value.uint64_value;
    }
}

int64_t JsonNumber::to_int64() const {
    switch (_cur_type) {
    case double_type: 
        return (int64_t)_cur_value.double_value;
    case int64_type:
        return _cur_value.int64_value; 
    case uint64_type:
        return (int64_t)_cur_value.uint64_value;
    }
}

double JsonNumber::to_double() const {
    switch (_cur_type) {
    case double_type: 
        return _cur_value.double_value;
    case int64_type:
        return (double)_cur_value.int64_value;
    case uint64_type:
        return (double)_cur_value.uint64_value;
    }
}

std::ostream& operator<<(std::ostream& os, const JsonNumber& number) {
    switch (number._cur_type) {
    case JsonNumber::double_type: 
        return os << number._cur_value.double_value;
    case JsonNumber::int64_type: 
        return os << number._cur_value.int64_value;
    case JsonNumber::uint64_type: 
        return os << number._cur_value.uint64_value;
    }
    return os;
}

}
}
