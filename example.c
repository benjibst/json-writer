#include "json.h"

int main()
{
    FILE* example = fopen("example.json","w");
    json_context ctx = json_initcontext(example);
    json_makectxcurrent(&ctx);
    json_beginobject();
    json_key("string");
    json_string("Hello!");
    json_key("real");
    json_double(3.14);
    json_key("int");
    json_int(123);
    json_key("object");
    json_beginobject();
    json_key("array");
    json_beginarray();
    json_int(345);
    json_int(678);
    json_int(910);
    json_beginarray();
    json_double(2.71);
    json_double(1.41);
    json_double(1.73);
    json_endarray();
    json_endarray();
    json_endobject();
    json_key("bye");
    json_string("later");
    json_endobject();
    fclose(example);
}