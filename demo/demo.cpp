#include <stdio.h>
#include "../json.h"
#include "../exception.h"

using namespace tis::json;

void test_deserialize() {
    try {
        Json* json = new(std::nothrow) Json;  
        JsonObj* obj = json->parse("{'a':[1, 2, 3]}");
        printf("type:%d\n", obj->type());
        /**
        JsonArray* arr = (JsonArray*)obj;
        for (int i = 0; i < arr->size(); ++i) {
            JsonNumber* num = (JsonNumber*)arr->get(i); 
            printf("%lu\n", num->to_uint64());
        }
        **/
    } catch (JsonException& ex) {
        printf("exception[%s]\n", ex.what()); 
    }
}

int main (int argc, char** argv) {
    test_deserialize();
}
