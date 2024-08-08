#define NOM_IMPLEMENTATION
#include "nom.h"

void cc(Nom_Cmd* cmd) {
    Nom_CmdAppend(cmd, "cc");
}

void cflags(Nom_Cmd* cmd) {
    Nom_CmdAppend(cmd, "-o", "./Build/emu");
    Nom_CmdAppend(cmd, "Wall", "-Wextra", "--padantic");
}

void files(Nom_Cmd* cmd) {
    Nom_CmdAppend(cmd, "src/6502.cpp", "src/test.cpp", "src/main.cpp");
}

int main() {
    Nom_Cmd cmd = {0};

    cc(&cmd);
    cflags(&cmd);
    files(&cmd);

    Nom_CmdRun_Sync(cmd);
    
    return 0;
}
