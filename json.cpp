#include "json.h"
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include "exception.h"
#include "string_helper.h"
namespace tis {
namespace json {
void Json::skip_white() {
    while (_s_token_map[(uint8_t)(*_cur)] == WHITE_SPACE) {
        ++_cur;
    }
}

JsonObj* Json::create(int t) {
    JsonObj* obj = NULL;
    switch (t) {
    case STRING:  
        obj = new(std::nothrow) JsonString(this);
        break;
    case NUMBER:
        obj = new(std::nothrow) JsonNumber(this);
        break;
    case MAP:
        obj = new(std::nothrow) JsonMap(this);
        break;
    case ARRAY:
        obj = new(std::nothrow) JsonArray(this);
        break;
    case BOOL:
        obj = new(std::nothrow) JsonBool(this);
        break;
    case NIL:
        obj = new(std::nothrow) JsonNil(this);
        break;
    default:
        return NULL;
    }
    if (obj) _alloc_objs.push_back(obj);
    return obj;
}

Json::Json() {
    _str_buf_size = 0;
    _str_buf_capacity = DEFAULT_STRING_BUF_SIZE;
    _str_buf = (char*)malloc(DEFAULT_STRING_BUF_SIZE);
    if (!_str_buf) {
        throw NoEnoughMemException() << "init str buff error"; 
    }
    _conv = iconv_open("utf8", "utf16"); 
    if ((iconv_t)-1 == _conv) {
        throw EncodingException() << "init iconv error";
    }
    _out_conv = iconv_open("utf16", "utf8");
    if ((iconv_t)-1 == _out_conv) {
        throw EncodingException() << "init out iconv error";
    }
    char* s = "1";
    char* buf = new char[5];
    char* pout = buf;
    size_t in = 1;
    size_t out = 4;
    buf[4] = '\0';
    iconv(_out_conv, &s, &in, &pout, &out);
    delete[] buf;
}

Json::~Json() {
    if (_str_buf) free(_str_buf);
    clear();
}

void Json::clear() {
    for (auto ite : _alloc_objs) delete ite; 
    _alloc_objs.clear();
}

JsonObj* Json::deserialize(const char* str) {
    _cur = str;
    return deserialize_value();
}

std::string Json::serialize(const JsonObj* obj) {
    std::stringbuf buf;
    std::ostream os(&buf);  
    os << *obj;
    return buf.str();
}

JsonObj* Json::deserialize_value() {
    skip_white();
    switch( _s_token_map[(uint8_t)(*_cur)] ){
    case MAP_BEGIN:
        return deserialize_map();
    case ARRAY_BEGIN:
        return deserialize_array();
    case STRING_LITERAL:
    {
        deserialize_string();
        JsonString* str = (JsonString*)create(STRING);
        str->assign(_str_buf, _str_buf_size);
        return str;
    }
    case NUMBER_LITERAL:
        return deserialize_number();
    case TRUE_LITERAL:
        if (0 == strncmp("true", _cur, 4)) {
            JsonBool* b = static_cast<JsonBool*>(create(BOOL)); 
            b->set(true);
            _cur += 4;
            return b;
        } else {
            throw ParseException()<<"deserialize bool true error"; 
        }
    case FALSE_LITERAL:
        if (0 == strncmp("false", _cur, 5)) {
            JsonBool* b = static_cast<JsonBool*>(create(BOOL)); 
            b->set(false);
            _cur += 5;
            return b;
        } else {
            throw ParseException()<<"deserialize bool false error"; 
        }
    case NULL_LITERAL:
        if (0 == strncmp("null", _cur, 4)) {
            JsonBool* b = static_cast<JsonBool*>(create(BOOL)); 
            _cur += 4;
            return b;
        } else {
            throw ParseException()<<"deserialize bool false error"; 
        }
    default:
        return NULL; 
    }
}

JsonObj* Json::deserialize_map() {
    JsonMap& map = *(static_cast<JsonMap*>(create(MAP))); 
    ++_cur; //skip '{'
    skip_white();
    if (_s_token_map[(uint8_t)(*_cur)] == STRING_LITERAL) {
        while(true) {
            deserialize_string();
            JsonObj*& value = map[_str_buf];
            skip_white();
            if (_s_token_map[(uint8_t)(*_cur)] != COLON) {
                throw ParseException()<< "deserialize map error, missing':'";
            }
            ++ _cur; //skip :
            JsonObj* v =  deserialize_value();
            if (!v) {
                throw ParseException()<< "deserialize map error, no value found"; 
            }
            value = v;
            skip_white();
            if (_s_token_map[(uint8_t)(*_cur)] == MAP_END) {
                break;
            }else if (_s_token_map[(uint8_t)(*_cur)] != COMMA) {
                throw ParseException()<< "deserialize map error, missing','";
            }
            ++ _cur; //skip ,
            skip_white();
            if (_s_token_map[(uint8_t)(*_cur)] == MAP_END) {
                break; 
            } else if (_s_token_map[(uint8_t)(*_cur)] != STRING_LITERAL) {
                throw ParseException()<< "deserialize map error, missing'\"'";
            }
        }
    }
    if (_s_token_map[(uint8_t)(*_cur)] != MAP_END) {
        throw ParseException()<<"deserialize map error, mising'}'";
    }
    ++ _cur; // skip '}'
    return &map;
}

JsonObj* Json::deserialize_array() {
    JsonArray* array = static_cast<JsonArray*>(create(ARRAY));
    ++ _cur; //skip '['
    skip_white();
    if (_s_token_map[(uint8_t)(*_cur)] != ARRAY_END) {
        while(true) {
            JsonObj* obj = deserialize_value();
            if (obj) {
                array->push_back(obj);
            }
            skip_white();
            if (_s_token_map[(uint8_t)(*_cur)] == ARRAY_END) {
                break;
            } else if (_s_token_map[(uint8_t)(*_cur)] != COMMA) {
                throw ParseException()<<"deserialize array error, missing','";
            }
            ++ _cur; //skip ,
        }
    }
    if (_s_token_map[(uint8_t)(*_cur)] != ARRAY_END) {
        throw ParseException()<<"deserialize array error, missing']'";
    }
    ++ _cur; // skip '}'
    return array;
}

void Json::flush_unicode_to_strbuf() {
    if (_unicode_buf.size()) {
        enlarge_strbuf(_unicode_buf.size() * 1.5);
        char* p_in = (char*)_unicode_buf.c_str();
        size_t size_in = _unicode_buf.size();
        char* p_out = _str_buf + _str_buf_size;
        size_t size_out = _str_buf_capacity - _str_buf_size;
        if ((size_t)-1 == iconv(_conv, &p_in, &size_in, &p_out, &size_out)) {
            throw ParseException() << "iconv error"; 
        }
        assert(0 == size_in);
        _str_buf_size = _str_buf_capacity - size_out;
        _unicode_buf.clear();
    }
}

void Json::enlarge_strbuf(size_t extra) {
    if (_str_buf_capacity - _str_buf_size >= extra) {
        return; 
    }
    _str_buf_capacity = 1.5 * _str_buf_capacity + 1;    
    char* new_str_buf = (char*)malloc(_str_buf_capacity);
    if (!new_str_buf) {
        throw NoEnoughMemException() << "no enough mem for str buf, capacity"; 
    }
    memcpy(new_str_buf, _str_buf, _str_buf_size);
    free(_str_buf);
    _str_buf = new_str_buf;
}

void Json::append_to_strbuf(const char* data, size_t len) {
    if (len) {
        enlarge_strbuf(len);
        memcpy(_str_buf + _str_buf_size, data, len);
        _str_buf_size += len;
    }
}

void Json::push_to_unicode_buf() {
    if ( !(*(_cur+2) && *(_cur+3) && *(_cur+4) && *(_cur+5))){
        throw ParseException()<<"read unicode error";
    }
    uint16_t unicode = _s_hex_map[(uint8_t)(*(_cur+2))] << 12
        | _s_hex_map[(uint8_t)(*(_cur+3))] << 8
        | _s_hex_map[(uint8_t)(*(_cur+4))] << 4
        | _s_hex_map[(uint8_t)(*(_cur+5))];
    _unicode_buf.append((char*)(&unicode), sizeof(unicode));
}

void Json::deserialize_string() {
    char delimiter = *_cur;
    const char *last_pos = _cur + 1;
    ++ _cur; // skip '\"'
    _str_buf_size = 0;
    _unicode_buf.clear();
    while (*_cur && *_cur != delimiter) {
        if ( *_cur == '\\' ) {   //escape
            if ( *(_cur + 1) == 'u' ) {    //unicode
                if (last_pos != _cur) {
                    flush_unicode_to_strbuf();
                    append_to_strbuf(last_pos, _cur - last_pos);
                }
                push_to_unicode_buf();
                _cur += 6;
            } else {
                flush_unicode_to_strbuf();
                append_to_strbuf(last_pos, _cur - last_pos);
                ++ _cur;
                char tmp = _s_unescape_map[(uint8_t)(*_cur)];
                if (tmp) { 
                    append_to_strbuf(&tmp, 1);
                }
                ++ _cur;
            }
            last_pos = _cur;
        } else {
            ++ _cur;
        }
    }
    if ( *_cur == delimiter ) {
        flush_unicode_to_strbuf();
        append_to_strbuf(last_pos, _cur - last_pos);
        ++ _cur; // skip '\"'
    } else {
        throw ParseException()<<"parse string error: no end";
    }
    _str_buf[_str_buf_size] = '\0';
}

JsonObj* Json::deserialize_number() {
    JsonNumber* number = static_cast<JsonNumber*>(create(NUMBER));
    char* p = (char*)_cur;
    bool parse_as_double = false;
    bool positive = true;
    if ('-' == *p) {
        positive = false;
        ++p;
    } else if ('+' == *p) {
        ++p; 
    }
    while(true) {
        if ('0' <= *p && '9' >= *p) {
            ++p;
        } else if ('.' == *p || 'e' == *p || 'E' == *p) {
            parse_as_double = true;
            break;
        } else {
            break; 
        }
    }
    if (parse_as_double) {
        double double_value = strtod(_cur, &p); 
        if ((HUGE_VAL == double_value || 0 == double_value) && ERANGE == errno) {
            throw ParseException() << "parse double error, value out of range"; 
        } 
        number->set(double_value);
    } else if (positive) {
        uint64_t uint64_value = strtoull(_cur, &p, 10);
        if (ULONG_MAX == uint64_value && ERANGE == errno) {
            throw ParseException() << "parse uint64_t error, value overflow"; 
        } 
        number->set(uint64_value);
    } else {
        int64_t int64_value = strtoll(_cur, &p, 10); 
        if (LLONG_MIN == int64_value && ERANGE == errno) {
            throw ParseException() << "parse int64_t error, value overflow"; 
        }
        number->set(int64_value);
    } 
    _cur = p;
    return number;
}

void Json::convert_unicode(const char* unicode, size_t len) {
    char* p_in = (char*)unicode;
    size_t size_in = len;
    char* p_out = _str_buf;
    size_t size_out = _str_buf_capacity;
    if ((size_t)-1 == iconv(_out_conv, 
                            &p_in, 
                            &size_in, 
                            &p_out, 
                            &size_out)) {
        throw ParseException() << "serialize iconv error"; 
    }
    assert(0 == size_in); 
    size_out = _str_buf_capacity - size_out;
    assert(0 == size_out % sizeof(uint16_t));
    uint16_t* up = (uint16_t*)_str_buf;
    for (uint32_t i = 0; i < size_out / sizeof(uint16_t); ++i) {
        _serialize_buf.append("\\u");
        uint16_t unicode = *(up + i);
        _serialize_buf.push_back(_s_invert_hex_map[unicode >> 12 & 0xf]);
        _serialize_buf.push_back(_s_invert_hex_map[unicode >> 8 & 0xf]);
        _serialize_buf.push_back(_s_invert_hex_map[unicode >> 4 & 0xf]);
        _serialize_buf.push_back(_s_invert_hex_map[unicode & 0xf]);
    }
}

void Json::escape_string(const char* data, size_t len) {
    const char* p = data;
    const char* last_utf8 = NULL;
    _str_buf_size = 0;
    enlarge_strbuf(len * 3 + 1);
    _serialize_buf.clear();
    while (true) {
        int size = tis::StringHelper::next_term_utf8(p);  
        if (0 == size) {
            break; 
        } else if (1 == size) {
            if (last_utf8) {
                convert_unicode(last_utf8, p - last_utf8);
                last_utf8 = NULL;
            }
            if (_s_escape_map[uint8_t(*p)]) {
                _serialize_buf.push_back('\\'); 
                _serialize_buf.push_back(_s_escape_map[uint8_t(*p)]); 
            } else {
                _serialize_buf.push_back(*p);
            }
            ++p;
        } else {
            if (!last_utf8) {
                last_utf8 = p; 
            }
            p += size;
        }
    }
    if (last_utf8) {
        convert_unicode(last_utf8, p - last_utf8); 
    }
}

bool Json::_s_init_token_map() {
    _s_token_map['\0'] = END;
    _s_token_map[' ']  = WHITE_SPACE;
    _s_token_map['\t'] = WHITE_SPACE;
    _s_token_map['\r'] = WHITE_SPACE;
    _s_token_map['\n'] = WHITE_SPACE;
    _s_token_map['{']  = MAP_BEGIN;
    _s_token_map['}']  = MAP_END;
    _s_token_map['[']  = ARRAY_BEGIN;
    _s_token_map[']']  = ARRAY_END;
    _s_token_map['(']  = LPAREN;
    _s_token_map[')']  = RPAREN;
    _s_token_map['\"'] = STRING_LITERAL;
    _s_token_map['\''] = STRING_LITERAL; //extended
    _s_token_map['t']  = TRUE_LITERAL;
    _s_token_map['f']  = FALSE_LITERAL;
    _s_token_map['n']  = NULL_LITERAL;
    _s_token_map[',']  = COMMA;
    _s_token_map[':']  = COLON;
    _s_token_map['+']  = NUMBER_LITERAL;  //extended
    _s_token_map['-']  = NUMBER_LITERAL;
    for( char c = '0'; c <= '9'; ++ c ) {
        _s_token_map[uint8_t(c)] = NUMBER_LITERAL;
    }
    return true;
}

bool Json::_s_init_unescape_map() {
    memset(_s_unescape_map, 0, sizeof(_s_unescape_map));
    _s_unescape_map[uint8_t('\"')] = '\"';
    _s_unescape_map[uint8_t('\'')] = '\'';
    _s_unescape_map[uint8_t('\\')] = '\\';
    _s_unescape_map[uint8_t('/' )] = '/';
    _s_unescape_map[uint8_t('b')] = '\b';
    _s_unescape_map[uint8_t('f')] = '\f';
    _s_unescape_map[uint8_t('n')] = '\n';
    _s_unescape_map[uint8_t('r')] = '\r';
    _s_unescape_map[uint8_t('t')] = '\t';
    return true;
}

bool Json::_s_init_escape_map() {
    memset(_s_escape_map, 0, sizeof(_s_escape_map));
    _s_escape_map[uint8_t('\"')] = '\"';
    _s_escape_map[uint8_t('\'')] = '\'';
    _s_escape_map[uint8_t('\\')] = '\\';
    _s_escape_map[uint8_t('/' )] = '/';
    _s_escape_map[uint8_t('\b')] = 'b';
    _s_escape_map[uint8_t('\f')] = 'f';
    _s_escape_map[uint8_t('\n')] = 'n';
    _s_escape_map[uint8_t('\r')] = 'r';
    _s_escape_map[uint8_t('\t')] = 't';
    return true;
}

bool Json::_s_init_hex_map(){
    memset(_s_hex_map, 0, sizeof(_s_hex_map));
    for( char c = '0'; c <= '9'; ++ c ){
        _s_hex_map[uint8_t(c)] = c - '0';
    }
    for( char c = 'A'; c <= 'F'; ++ c ){
        _s_hex_map[uint8_t(c)] = 10 + c - 'A';
    }
    for( char c = 'a'; c <= 'f'; ++ c ){
        _s_hex_map[uint8_t(c)] = 10 + c - 'a';
    }
    return true;
}

bool Json::_s_init_invert_hex_map() {
    memset(_s_invert_hex_map, 0, sizeof(_s_invert_hex_map));
    for( char c = '0'; c <= '9'; ++ c ){
        _s_invert_hex_map[c - '0'] = c;
    }
    for( char c = 'A'; c <= 'F'; ++ c ){
        _s_invert_hex_map[10 + c - 'A'] = c;
    }
    for( char c = 'a'; c <= 'f'; ++ c ){
        _s_invert_hex_map[10 + c - 'a'] = c;
    }
    return true;
}

Json::token_type Json::_s_token_map[];
char Json::_s_unescape_map[];
char Json::_s_escape_map[];
uint16_t Json::_s_hex_map[];
char Json::_s_invert_hex_map[];

bool Json::_s_initer = (Json::_s_init_token_map(), 
                        Json::_s_init_unescape_map(), 
                        Json::_s_init_hex_map(),
                        Json::_s_init_escape_map(),
                        Json::_s_init_invert_hex_map());

}
}
