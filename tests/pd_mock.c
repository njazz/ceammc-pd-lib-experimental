#include "m_pd.h"

#include "m_imp.h"

#include <stdlib.h>

t_symbol* gensym(const char* s)
{
    t_symbol* ret = (t_symbol*)malloc(sizeof(t_symbol));

    ret->s_name = (char*)s;
    ret->s_next = 0;
    ret->s_thing = 0;

    return ret;
}

void outlet_anything(struct _outlet* x, t_symbol* s, int argc, t_atom* argv)
{
    printf("outlet mock: anything\n");
}

void outlet_bang(struct _outlet* x)
{
    printf("outlet mock: bang\n");
}

void outlet_list(struct _outlet* x, t_symbol* s, int argc, t_atom* argv)
{
    printf("outlet mock: list\n");
}

void outlet_symbol(struct _outlet* x, t_symbol* s)
{
    printf("outlet mock: symbol\n");
}

void outlet_float(struct _outlet* x, t_float f)
{
    printf("outlet mock: bang\n");
}

// =======

void post(const char* fmt, ...)
{
    printf("post mock \n");
}

void error(const char* fmt, ...)
{
    printf("error mock \n");
}

void pd_error(void* object, const char* fmt, ...)
{
    printf("error mock \n");
}

// =======

t_symbol s_bang = {.s_name = "bang", .s_thing = 0, .s_next = 0 };
t_symbol s_float = {.s_name = "float", .s_thing = 0, .s_next = 0 };
t_symbol s_list = {.s_name = "list", .s_thing = 0, .s_next = 0 };
t_symbol s_symbol = {.s_name = "symbol", .s_thing = 0, .s_next = 0 };
