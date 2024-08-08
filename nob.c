#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, const char ** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    nob_log(NOB_INFO, "Thing");
      
    return 0;
}
