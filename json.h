#ifndef __JSON_H_
#define __JSON_H_
#include <iconv.h>
#include <list>
#include <iostream> 
#include "json_obj.h"

namespace tis {
namespace json {

class Json {
public:
    static const int DEFAULT_STRING_BUF_SIZE = 1024;

private:
    enum token_type {
        END,            // '\0' 
        WHITE_SPACE,    // ' ' '\n' '\r' '\t' '\v' 
        MAP_BEGIN,   // '{'
        MAP_END,     // '}'
        ARRAY_BEGIN,    // '['
        ARRAY_END,      // ']'
        LPAREN,         // '('
        RPAREN,         // ')'
        NUMBER_LITERAL, // '+' '-'
        STRING_LITERAL, // '\"' '\''
        TRUE_LITERAL,   //'t' 
        FALSE_LITERAL,  //'f'
        NULL_LITERAL,   // 'n'
        COMMA,          // ','
        COLON,          // ':'
    };
    static token_type _s_token_map[0x100];
    static char _s_unescape_map[0x100];
    static uint16_t _s_hex_map[0x100];
    static bool _s_init_token_map();
    static bool _s_init_unescape_map();
    static bool _s_init_hex_map();
    static bool _s_initer;
    static bool _s_init_handler_map();

public:
    Json();
    virtual ~Json();

public:
    JsonObj* create(int type); 
    JsonObj* deserialize(const char* str);
    std::string serialize(const JsonObj* obj);
    void clear();

private:
    JsonObj* deserialize_value();
    JsonObj* deserialize_map();
    JsonObj* deserialize_array();
    void deserialize_string();
    JsonObj* deserialize_number();
    void flush_unicode_to_strbuf();
    void append_to_strbuf(const char* data, size_t len);
    void enlarge_strbuf(size_t extra);
    void push_to_unicode_buf();
    void skip_white();

private:
    std::list<JsonObj*> _alloc_objs;
    char* _str_buf;
    int _str_buf_size;
    int _str_buf_capacity; 
    std::string _unicode_buf;
    const char* _cur;
    iconv_t _conv;
};

}
}

#endif
