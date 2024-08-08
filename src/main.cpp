#include "log.h"
#include "6502.h"

#include "test.h"

#include <stdlib.h>

int main( void ) {
    // static const timespec SleepTime = {1, 0};

    EMU_TRACE("Init Emulator (emu)");

    emu::_6502 CPU;
    emu::memory Mem;

    CPU.BindMemory(&Mem);

    u32 Fail = 0;

    EMU_DEBUG("Testing LDA:\n");

    emu::__TEST_LDA_IM   (Fail, CPU, Mem);
    emu::__TEST_LDA_ZP   (Fail, CPU, Mem);
    emu::__TEST_LDA_ZPX  (Fail, CPU, Mem);
    emu::__TEST_LDA_ABS  (Fail, CPU, Mem);
    emu::__TEST_LDA_ABSX (Fail, CPU, Mem);
    emu::__TEST_LDA_ABSY (Fail, CPU, Mem);
    emu::__TEST_LDA_INDX (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing LDX:\n");

    emu::__TEST_LDX_IM   (Fail, CPU, Mem);
    emu::__TEST_LDX_ZP   (Fail, CPU, Mem);
    emu::__TEST_LDX_ZPY  (Fail, CPU, Mem);
    emu::__TEST_LDX_ABS  (Fail, CPU, Mem);
    emu::__TEST_LDX_ABSY (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing LDY:\n");

    emu::__TEST_LDY_IM   (Fail, CPU, Mem);
    emu::__TEST_LDY_ZP   (Fail, CPU, Mem);
    emu::__TEST_LDY_ZPX  (Fail, CPU, Mem);
    emu::__TEST_LDY_ABS  (Fail, CPU, Mem);
    emu::__TEST_LDY_ABSX (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing STA:\n");

    emu::__TEST_STA_ZP   (Fail, CPU, Mem);
    emu::__TEST_STA_ZPX  (Fail, CPU, Mem);
    emu::__TEST_STA_ABS  (Fail, CPU, Mem);
    emu::__TEST_STA_ABSX (Fail, CPU, Mem);
    emu::__TEST_STA_ABSY (Fail, CPU, Mem);
    emu::__TEST_STA_INDX (Fail, CPU, Mem);
    emu::__TEST_STA_INDY (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing STX:");

    emu::__TEST_STX_ZP   (Fail, CPU, Mem);
    emu::__TEST_STX_ZPY  (Fail, CPU, Mem);
    emu::__TEST_STX_ABS  (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing STY:");

    emu::__TEST_STY_ZP   (Fail, CPU, Mem);
    emu::__TEST_STY_ZPX  (Fail, CPU, Mem);
    emu::__TEST_STY_ABS  (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing T**:");

    emu::__TEST_TAX      (Fail, CPU, Mem);
    emu::__TEST_TAY      (Fail, CPU, Mem);
    emu::__TEST_TXA      (Fail, CPU, Mem);
    emu::__TEST_TYA      (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing JMP:");

    emu::__TEST_JMP_ABS  (Fail, CPU, Mem);
    // emu::__TEST_JMP_IND  (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing DEC");

    emu::__TEST_DEC_ZP   (Fail, CPU, Mem);
    emu::__TEST_DEC_ZPX  (Fail, CPU, Mem);
    emu::__TEST_DEC_ABS  (Fail, CPU, Mem);
    emu::__TEST_DEC_ABSX (Fail, CPU, Mem);
    
    std::cout << std::endl;
    EMU_DEBUG("Testing DEX/DEY");

    emu::__TEST_DEX      (Fail, CPU, Mem);
    emu::__TEST_DEY      (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testing INC");

    emu::__TEST_INC_ZP   (Fail, CPU, Mem);
    emu::__TEST_INC_ZPX  (Fail, CPU, Mem);
    emu::__TEST_INC_ABS  (Fail, CPU, Mem);
    emu::__TEST_INC_ABSX (Fail, CPU, Mem);
    
    std::cout << std::endl;
    EMU_DEBUG("Testing INX/INY");

    emu::__TEST_INX      (Fail, CPU, Mem);
    emu::__TEST_INY      (Fail, CPU, Mem);

    std::cout << std::endl;
    EMU_DEBUG("Testong PH* and PL*");

    emu::__TEST_PHA      (Fail, CPU, Mem);
    emu::__TEST_PHP      (Fail, CPU, Mem);
    emu::__TEST_PLA      (Fail, CPU, Mem);
    emu::__TEST_PLP      (Fail, CPU, Mem);

    std::cout << std::endl;
    
    if (!Fail) {
        EMU_INFO("All Tests Passing");
    } else {
        EMU_WARN("{} Tests failing", Fail);
    }

    return 0;
}
