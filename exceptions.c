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

void throw(exception e) {
    if (!current) {
        fprintf(stderr, "Uncaught exception: %s\n", exc_name(e.kind));
        exit(1);
    }
    current->value = e;
    longjmp(current->buf, 1);
}

void failwith(const char *msg) {
    throw(
        (exception) {
            FAILURE, 
            msg
        }
    );
}