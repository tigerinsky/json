#include <stdio.h>
#include "../json.h"
#include "../exception.h"

using namespace tis::json;

void test_deserialize() {
    try {
        const char* str = "{'\\u6C49\\u6c49b\\t\\u6c49cd\\uD83D\\uDE03hi' : [1e10, 0.2, -31]}";
        printf("%s\n", str);
        Json* json = new(std::nothrow) Json;  
        JsonObj* obj = json->deserialize(str);
        printf("type:%d\n", obj->type());
        JsonMap& map = *((JsonMap*)obj);
        for (auto ite : map) {
            printf("%s\n", ite.first.c_str());
            JsonArray* array = (JsonArray*)ite.second;
            for (int i = 0; i < array->size(); ++i) {
                printf("%lf\n", ((JsonNumber*)(array->get(i)))->to_double()); 
            }
        }
    } catch (JsonException& ex) {
        printf("exception[%s]\n", ex.what()); 
    }
}

int main (int argc, char** argv) {
    test_deserialize();
}
