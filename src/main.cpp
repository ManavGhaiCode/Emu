#include "log.h"
#include "6502.h"

#include "test.h"

#include <stdlib.h>

int main( void ) {
    static const timespec SleepTime = {1, 0};

    EMU_TRACE("Init Emulator (emu)");

    emu::_6502 CPU;
    emu::memory Mem;

    CPU.BindMemory(&Mem);

    u32 Fail = 0;

    emu::__TEST_LDA_IM   (Fail, CPU, Mem);
    emu::__TEST_LDA_ZP   (Fail, CPU, Mem);
    emu::__TEST_LDA_ZPX  (Fail, CPU, Mem);
    emu::__TEST_LDA_ABS  (Fail, CPU, Mem);
    emu::__TEST_LDA_ABSX (Fail, CPU, Mem);
    emu::__TEST_LDA_ABSY (Fail, CPU, Mem);
    emu::__TEST_LDA_INDX (Fail, CPU, Mem);

    if (!Fail) {
        EMU_INFO("All Tests Passing");
    } else {
        EMU_WARN("{} Tests failing", Fail);
    }

    return 0;
}