#ifndef __JSON_OBJ_H_
#define __JSON_OBJ_H_
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>
#include "define.h"

namespace tis {
namespace json {

class Json;

class JsonObj {
public:
    virtual ~JsonObj() {}

public:
    friend std::ostream& operator<<(std::ostream& os, const JsonObj& o);
    virtual obj_type type() const { return _type;}

protected:
    std::string& _escape(const char* s, size_t len) const;

protected:
    JsonObj(obj_type t=UNKNOWN, Json* json=NULL):_type(t), _json(json) {}

protected:
    Json* _json;
    obj_type _type;
};
std::ostream& operator<<(std::ostream& os, const JsonObj& o);

class JsonString : public JsonObj {
friend std::ostream& operator<<(std::ostream& os, const JsonString& n);
friend class Json;
public:
    void assign(const char* str);
    void assign(const char* str, size_t len);
    const char* c_str();
    size_t size();
     
private:
    explicit JsonString(Json* json) : JsonObj(STRING, json) {}
    std::string _str;
};
std::ostream& operator<<(std::ostream& os, const JsonString& s);

class JsonNumber : public JsonObj {
friend std::ostream& operator<<(std::ostream& os, const JsonNumber& n);
friend class Json;
public:
    void set(double d);
    void set(uint64_t u);
    void set(int64_t i);
    uint64_t to_uint64() const;
    int64_t to_int64() const;
    double to_double() const;

private:
    explicit JsonNumber(Json* json) : 
        JsonObj(NUMBER, json), 
        _cur_type(uint64_type) {
        _cur_value.uint64_value = 0;     
    }

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
friend std::ostream& operator<<(std::ostream& out, const JsonArray& arr);
friend class Json;
public:
    size_t size() const;
    JsonObj*& operator[](size_t idx);
    JsonObj* get(size_t idx) const;
    void push_back(JsonObj* obj);
private:
    explicit JsonArray(Json* json) : JsonObj(ARRAY, json) {}
    std::vector<JsonObj*> _vector;
};
std::ostream& operator<<(std::ostream& out, const JsonArray& arr);

typedef std::unordered_map<std::string, JsonObj*>::iterator iterator_t;
typedef std::unordered_map<std::string, JsonObj*>::const_iterator const_iterator_t;
class JsonMap : public JsonObj {
friend std::ostream& operator<<(std::ostream& out, const JsonMap& map);
friend class Json;
public:
    JsonObj*& operator[](const char* k);
    size_t size();
    iterator_t begin();
    iterator_t end();
private:
    explicit JsonMap(Json* json) : JsonObj(MAP, json) {}
    std::unordered_map<std::string, JsonObj*> _map;
};
std::ostream& operator<<(std::ostream& out, const JsonMap& map);

class JsonBool : public JsonObj {
friend std::ostream& operator<<(std::ostream& os, const JsonBool& n);
friend class Json;
public:
    void set(bool b) { _bool = b; }
    bool get() const { return _bool; }
private:
    explicit JsonBool(Json* json) : JsonObj(BOOL, json), _bool(false) {}
    bool _bool;
};
std::ostream& operator<<(std::ostream& os, const JsonBool& b);

class JsonNil : public JsonObj {
friend std::ostream& operator<<(std::ostream& os, const JsonNil& n);
friend class Json;
private:
    explicit JsonNil(Json* json) : JsonObj(NIL, json) {}
};
std::ostream& operator<<(std::ostream& os, const JsonNil& n);

}
}
#endif
