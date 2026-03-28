#include "exceptions.h"

exc_ctx *current = NULL;

const char *exc_name(exc_kind k) {
    switch (k) {
        CASE(DIV0)
        CASE(FAILURE)
        default: return "UNKNOWN";
    }
}

void exc_print(exception e) {
    printf("Caught exception %s", exc_name(e.kind));
    if (e.msg) printf(" with message: %s.\n", e.msg);
    else printf(".\n");
}

void cleanup(exc_ctx *ctx) {
    mem_node *cur = ctx->allocs;
    while (cur) {
        free(cur->ptr);
        mem_node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void raise(exception e) {
    if (!current) {
        fprintf(stderr, "Uncaught exception: %s\n", exc_name(e.kind));
        exit(1);
    }
    cleanup(current);
    current->value = e;
    longjmp(current->buf, 1);
}

void failwith(const char *msg) {
    raise(
        (exception) {
            FAILURE, 
            msg
        }
    );
}

void *gc_malloc(size_t size) {
    void *p = malloc(size);
    if (!current) {
        fprintf(stderr, "Use of gc_malloc outside TRY/CATCH is banned, use regular malloc instead.\n");
        abort();
    }

    mem_node *node = malloc(sizeof(mem_node));
    node->ptr = p;
    node->next = current->allocs;
    current->allocs = node;

    return p;
}