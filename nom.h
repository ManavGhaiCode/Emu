#ifndef _NOM_H_
#define _NOM_H_

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include <assert.h>

#ifndef NOM_ALLOC
    #define NOM_ALLOC(size) malloc(size)
#endif

#ifndef NOM_REALLOC
    #define NOM_REALLOC(ptr, size) realloc(ptr, size)
#endif

#ifndef NOM_FREE
    #define NOM_FREE(ptr) free(ptr)
#endif

#ifndef DA_INIT_CAP
    #define DA_INIT_CAP 256
#endif

#define DA_APPEND(da, el) do {                                  \
    if((da)->cap < (da)->size + 1) {                            \
        (da)->cap = (da)->cap ? (da)->cap * 2 : DA_INIT_CAP;    \
        (da)->items = NOM_REALLOC((da)->items, (da)->cap);      \
    }                                                           \
    (da)->items[(da)->size] = el;                               \
    (da)->size += 1;                                            \
} while (0)

typedef long  i64;
typedef int   i32;
typedef short i16;
typedef char  i8;

typedef unsigned long  u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef struct {
    const char** items;
    u32 size;
    u32 cap;
} Nom_Cmd;

typedef struct {
    char* items;
    u32 size;
    u32 cap;
} Nom_StringBuilder;

#ifdef WIN32
    typedef Handle Pid;
#else
    typedef u64 Pid;
#endif

#define Nom_CmdAppend(cmd, ...) __Nom_CmdAppend(cmd, __VA_ARGS__, NULL);

void __Nom_CmdAppend(Nom_Cmd* cmd, ...);
Pid  Nom_CmdRun_Async(Nom_Cmd cmd);
bool Nom_CmdRun_Sync(Nom_Cmd cmd);

void Nom_FreeCmd(Nom_Cmd* cmd);
void Nom_FreeStringBuilder(Nom_StringBuilder* sb);

// ----------------------------------------
// ----------------- FILE -----------------
// ----------------------------------------

// ----------------------------------------
// ------------ IMPLEMENTATION ------------
// ----------------------------------------

#ifdef NOM_IMPLEMENTATION

void __Nom_CmdAppend(Nom_Cmd* cmd, ...) {
    va_list list;
    va_start(list, cmd);
        const char* el = va_arg(list, const char*);
        while (el) {
            DA_APPEND(cmd, el);
            el = va_arg(list, const char*);
        }
    va_end(list);
}

Pid Nom_CmdRun_Async(Nom_Cmd cmd) {
    assert(false && "TODO: Implement Nom_CmdRun_Async()");
}

bool Nom_CmdRun_Sync(Nom_Cmd cmd) {
    assert(false && "TODO: Implement Nom_CmdRun_Sync()");
}

void Nom_FreeCmd(Nom_Cmd* cmd) {
    NOM_FREE(cmd->items);
    cmd->size = 0;
    cmd->cap = 0;
}

void Nom_FreeStringBuilder(Nom_StringBuilder* sb) {
    NOM_FREE(sb->items);
    sb->size = 0;
    sb->cap = 0;
}

#endif
#endif // _NOM_H_
