#include "json.h"

static json_context *curr_ctx;

json_context json_initcontext(FILE* f)
{
    json_context ctx = {0};
    ctx.outfile = f;
    return ctx;
}

void json_makectxcurrent(json_context *ctx)
{
    curr_ctx = ctx;
};

void json_beginobject()
{
    json_beginlvl(Obj);
}

void json_beginarray()
{
    json_beginlvl(Arr);
}

void json_endobject()
{
    json_endlvl(Obj);
}

void json_endarray()
{
    json_endlvl(Arr);
}

void json_key(const char *key)
{
    if (json_getlvl().valcnt > 0)
        fprintf(curr_ctx->outfile,",");
    fprintf(curr_ctx->outfile,"\n");
    
    fprintf(curr_ctx->outfile,"%*s\"%s\": ", curr_ctx->curr_indentation, "", key);
    curr_ctx->lvl[curr_ctx->lvlidx].valcnt++;
}

void json_string(const char *str)
{
    json_printvalue("\"%s\"", str);
}

void json_double(double f)
{
    json_printvalue("%.8g", f);
}

void json_int(int v)
{
    json_printvalue("%d", v);
}

inline json_lvl json_getlvl()
{
    return curr_ctx->lvl[curr_ctx->lvlidx];
}

void json_endlvl(json_in lvl)
{
    char end = lvl == Obj ? '}' : ']';
    curr_ctx->curr_indentation -= DEFAULT_INDENTATION;
    if(json_getlvl().valcnt>0)
    {
        fprintf(curr_ctx->outfile,"\n");
        fprintf(curr_ctx->outfile,"%*s", curr_ctx->curr_indentation, "");
    }
    fprintf(curr_ctx->outfile,"%c",end);
    curr_ctx->lvlidx--;
}

void json_beginlvl(json_in lvl)
{
    char begin = lvl == Obj ? '{' : '[';
    if (json_getlvl().lvl == Obj || json_getlvl().lvl == None)
    {
        fprintf(curr_ctx->outfile,"%c", begin);
    }
    else
    // lvl is Arr because its not obj
    {
        if (json_getlvl().valcnt > 0)
            fprintf(curr_ctx->outfile,",");
        fprintf(curr_ctx->outfile,"\n");

        fprintf(curr_ctx->outfile,"%*s%c", curr_ctx->curr_indentation, "", begin);
        curr_ctx->lvl[curr_ctx->lvlidx].valcnt++;
    }
    curr_ctx->curr_indentation += DEFAULT_INDENTATION;
    curr_ctx->lvlidx++;
    curr_ctx->lvl[curr_ctx->lvlidx].lvl = lvl;
    curr_ctx->lvl[curr_ctx->lvlidx].valcnt = 0;
}

void json_printvalue(const char *fmt, ...)
{
    va_list args;

    if (json_getlvl().lvl == Obj)
    {
        va_start(args,fmt);
        vfprintf(curr_ctx->outfile,fmt,args);
        va_end(args);
        return;
    }
    if (json_getlvl().valcnt > 0)
        fprintf(curr_ctx->outfile,",");
    fprintf(curr_ctx->outfile,"\n");

    fprintf(curr_ctx->outfile,"%*s", curr_ctx->curr_indentation, "");
    
    va_start(args,fmt);
    vfprintf(curr_ctx->outfile,fmt,args);
    va_end(args);
    curr_ctx->lvl[curr_ctx->lvlidx].valcnt++;
}