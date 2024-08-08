#define NOB_IMPLEMENTATION
#include "nob.h"

void cflags(Nob_Cmd* cmd) {
    nob_cmd_append(cmd, "-o", "./Build/emu");
    nob_cmd_append(cmd, "-Wall", "-Wextra", "--pedantic");
    nob_cmd_append(cmd, "-I./src");
}

void cc(Nob_Cmd* cmd) {
    nob_cmd_append(cmd, "c++");
    cflags(cmd);
}

void files(Nob_Cmd* cmd) {
    nob_cmd_append(cmd, "src/6502.cpp");
    nob_cmd_append(cmd, "src/test.cpp");
    nob_cmd_append(cmd, "src/main.cpp", "src/log.cpp");
}

int main(int argc, const char ** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};

    if (!nob_mkdir_if_not_exists("./Build")) nob_log(NOB_ERROR, "Unable to create Build dir");
    
    cc(&cmd);
    files(&cmd);

    if (!nob_cmd_run_sync(cmd)) nob_log(NOB_ERROR, "Could not compile executable!"); return 1;
    
    return 0;
}
