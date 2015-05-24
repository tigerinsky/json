#ifndef __JSON_OBJ_H_
#define __JSON_OBJ_H_
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>
#include "define.h"

namespace tis {
namespace json {

class JsonObj {
public:
    virtual ~JsonObj() {}
public:
    friend std::ostream& operator<<(std::ostream& os, const JsonObj& o);
    virtual obj_type type() const = 0;
};
std::ostream& operator<<(std::ostream& os, const JsonObj& o);

class JsonString : public JsonObj {
public:
    obj_type type() const { return STRING; }
    void assign(const char* str);
    void assign(const char* str, size_t len);
    const char* c_str();
    size_t size();
    friend std::ostream& operator<<(std::ostream& os, const JsonString& n);
private:
    std::string _str;
};
std::ostream& operator<<(std::ostream& os, const JsonString& s);

class JsonNumber : public JsonObj {
public:
    JsonNumber();
    obj_type type() const { return NUMBER; }
    void set(double d);
    void set(uint64_t u);
    void set(int64_t i);
    uint64_t to_uint64() const;
    int64_t to_int64() const;
    double to_double() const;
    friend std::ostream& operator<<(std::ostream& os, const JsonNumber& n);
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
std::ostream& operator<<(std::ostream& out, const JsonNumber& t1);

class JsonArray : public JsonObj {
public:
    obj_type type() const { return ARRAY; }
    size_t size() const;
    JsonObj*& operator[](size_t idx);
    JsonObj* get(size_t idx) const;
    void push_back(JsonObj* obj);
    friend std::ostream& operator<<(std::ostream& out, const JsonArray& arr);
private:
    std::vector<JsonObj*> _vector;
};
std::ostream& operator<<(std::ostream& out, const JsonArray& arr);

typedef std::unordered_map<std::string, JsonObj*>::iterator iterator_t;
typedef std::unordered_map<std::string, JsonObj*>::const_iterator const_iterator_t;
class JsonMap : public JsonObj {
public:
    obj_type type() const { return MAP; }
    JsonObj*& operator[](const char* k);
    size_t size();
    iterator_t begin();
    iterator_t end();
    friend std::ostream& operator<<(std::ostream& out, const JsonMap& map);
private:
    std::unordered_map<std::string, JsonObj*> _map;
};
std::ostream& operator<<(std::ostream& out, const JsonMap& map);

class JsonBool : public JsonObj {
public:
    JsonBool() : _bool(false) {}
    obj_type type() const { return BOOL; }
    void set(bool b) { _bool = b; }
    bool get() const { return _bool; }
    friend std::ostream& operator<<(std::ostream& os, const JsonBool& n);
private:
    bool _bool;
};
std::ostream& operator<<(std::ostream& os, const JsonBool& b);

class JsonNil : public JsonObj {
public:
    obj_type type() const { return NIL;}
    friend std::ostream& operator<<(std::ostream& os, const JsonNil& n);
};
std::ostream& operator<<(std::ostream& os, const JsonNil& n);

}
}
#endif
