#include "log.h"
#include "6502.h"

#include <stdlib.h>

int main ( void ) {
    static const timespec SleepTime = {1, 0};

    EMU_TRACE("Init Emulator (emu)");

    emu::_6502 CPU;
    CPU.Init();

    while (true) {
        nanosleep(&SleepTime, 0);
        CPU.Clock();
    }

    return 0;
}