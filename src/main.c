#include "exceptions.h"

void f1() {
    printf("f1() start\n");
    failwith("bleh");
    printf("f1() end\n");
}

void f2() {
    printf("f2() start\n");
    f1();
    printf("f2() end\n");
}

void f3() {
    printf("f3() start\n");
    TRY {
        f2();
    } CATCH(e) {
        case FAILURE: printf("caught exception: %s\n", e.msg); break;
    } END_TRY;
    printf("f3() end\n");
}

int main() 
{
    f3();
    return 0;
}

