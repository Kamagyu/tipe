#include "exceptions.h"


int main() 
{
    void *p = gc_malloc(500);
    TRY {
        gc_malloc(1000);
        failwith("ça va leak...");
    } CATCH(e) {
        case FAILURE: break;
    } END_TRY;
    free(p);
    return 0;
}

