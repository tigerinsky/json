#ifndef __JSON_EXCEPTION_H_
#define __JSON_EXCEPTION_H_
#include <exception>
#include <string>

namespace tis {
namespace json {

class Exception : public std::exception {
public:
    virtual const char* what() const throw() { return _msg.c_str(); }
protected:
    std::string _msg;
};

template<typename ExceptionT, typename BaseExceptionT>
class BasicException : public BaseExceptionT {
public:
    ExceptionT& operator << (const char* msg) {
        this->_msg.append(msg); 
        return static_cast<ExceptionT&>(*this);
    }
};

class JsonException : public BasicException<JsonException, Exception> {};
class ParseException : public JsonException {};
class EncodingException : public JsonException {};
class NoEnoughMemException : public JsonException {};
class InvalidOpException: public JsonException {};

}
}
#endif 
