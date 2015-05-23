#ifndef __JSON_OBJ_H_
#define __JSON_OBJ_H_
#include <string>
#include <vector>
#include <unordered_map>
#include "define.h"

namespace tis {
namespace json {

class JsonObj {
public:
    virtual ~JsonObj() {}
public:
    virtual obj_type type() = 0;
};

class JsonString : public JsonObj {
public:
    obj_type type() { return STRING; }
    void assign(const char* str);
    void assign(const char* str, size_t len);
private:
    std::string _str;
};

class JsonNumber : public JsonObj {
public:
    JsonNumber();
    obj_type type() { return NUMBER; }
    void set(double d);
    void set(uint64_t u);
    void set(int64_t i);
    uint64_t to_uint64();
    int64_t to_int64();
    double to_double();
private:
    enum number_type {
        double_type, 
        uint64_type, 
        int64_type, 
    };
    typedef union value_t {
        double double_value; 
        uint64_t uint64_value; 
        int64_t int64_value; 
    } value_t;
    number_type _cur_type;
    value_t _cur_value;
};

class JsonArray : public JsonObj {
public:
    obj_type type() { return ARRAY; }
    size_t size();
    JsonObj*& operator[](size_t idx);
    JsonObj* get(size_t idx);
    void push_back(JsonObj* obj);
private:
    std::vector<JsonObj*> _vector;
};

class JsonMap : public JsonObj {
public:
    obj_type type() { return MAP; }
    JsonObj*& operator[](const char* k);
private:
    std::unordered_map<std::string, JsonObj*> _map;
};

class JsonBool : public JsonObj {
public:
    JsonBool() : _bool(false) {}
    obj_type type() {return BOOL;}
    void set(bool b) { _bool = b; }
    bool get() { return _bool; }
private:
    bool _bool;
};

class JsonNil : public JsonObj {
public:
    obj_type type() { return NIL;}
};



}
}
#endif
