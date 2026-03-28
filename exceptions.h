#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DIV0,
    FAILURE
} exc_kind;

typedef struct {
    exc_kind kind;
    const char *msg;
} exception;

typedef struct mem_node {
    void *ptr;
    struct mem_node *next;
} mem_node;

typedef struct exc_ctx {
    jmp_buf buf;
    struct exc_ctx *prev; // previous try 
    exception value;
    mem_node *allocs;
} exc_ctx;

extern exc_ctx *current;

#define CASE(x) case x: return #x;

#define TRY do { \
    exc_ctx ctx; \
    ctx.prev = current; \
    current = &ctx; \
    int _exc_flag = setjmp(ctx.buf); \
    if (_exc_flag == 0)

#define CATCH(e) \
    else { \
        exception e = ctx.value; \
        switch (e.kind) {\

#define END_TRY \
    default: { \
        current = ctx.prev; \
        raise(e); \
    } \
    } \
    } \
    current = ctx.prev; \
    } while (0)

#define RERAISE() \
    do { \
        exception _e = ctx.value; \
        current = ctx.prev; \
        raise(_e); \
    } while(0)

const char *exc_name(exc_kind k);
void exc_print(exception e);
void raise(exception e);
void failwith(const char* msg);

#endif