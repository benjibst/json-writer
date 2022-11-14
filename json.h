#ifndef __JSON_H__
#define __JSON_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define DEFAULT_INDENTATION 2

enum json_in{None,Obj,Arr};
typedef enum json_in json_in;

struct json_lvl
{
    json_in lvl;
    int valcnt;
};
typedef struct json_lvl json_lvl;

struct json_context
{
    int curr_indentation;
    json_lvl lvl[255];
    FILE* outfile;
    size_t lvlidx;
    size_t bufsz;
};
typedef struct json_context json_context;

//functions to deal with context
json_context json_initcontext(FILE* f);
void json_makectxcurrent(json_context *ctx);

//functions to write json file
void json_beginobject();
void json_beginarray();
void json_endobject();
void json_endarray();
void json_key(const char *key);
void json_string(const char *str);
void json_double(double f);
void json_int(int v);

// used only internally, use the other functions to print
json_lvl json_getlvl();
void json_endlvl(json_in lvl);
void json_beginlvl(json_in lvl);
void json_printvalue(const char *fmt, ...);

#endif // __JSON_H__