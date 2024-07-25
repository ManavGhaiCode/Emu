#include "log.h"
#include "6502.h"

int main ( void ) {
    EMU_TRACE("Init Emulator (emu)");

    emu::_6502 CPU;
    CPU.Init();

    return 0;
}