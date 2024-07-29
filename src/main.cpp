#include "log.h"
#include "6502.h"

#include <stdlib.h>

int main( void ) {
    static const timespec SleepTime = {1, 0};

    EMU_TRACE("Init Emulator (emu)");

    emu::_6502 CPU;
    emu::memory Mem;

    CPU.BindMemory(&Mem);
    CPU.Reset();

    // while (true) {
        // nanosleep(&SleepTime, 0);
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
    // }

    // CPU.GetState();
    EMU_DEBUG("A: {}", (u32)CPU.A);

    return 0;
}