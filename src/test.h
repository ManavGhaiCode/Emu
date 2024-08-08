#ifndef _TEST_H_
#define _TEST_H_

#include "config.h"
#include "6502.h"

namespace emu {
    void __TEST_LDA_IM   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_ZPX  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_ABSX (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_ABSY (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_INDX (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDA_INDY (u32& fail, _6502& CPU, memory& mem); // Currently unsupported

    void __TEST_LDX_IM   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDX_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDX_ZPY  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDX_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDX_ABSY (u32& fail, _6502& CPU, memory& mem);

    void __TEST_LDY_IM   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDY_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDY_ZPX  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDY_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_LDY_ABSX (u32& fail, _6502& CPU, memory& mem);

    void __TEST_STA_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STA_ZPX  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STA_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STA_ABSX (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STA_ABSY (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STA_INDX (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STA_INDY (u32& fail, _6502& CPU, memory& mem);

    void __TEST_STX_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STX_ZPY  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STX_ABS  (u32& fail, _6502& CPU, memory& mem);

    void __TEST_STY_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STY_ZPX  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_STY_ABS  (u32& fail, _6502& CPU, memory& mem);

    void __TEST_TAX      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_TAY      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_TSX      (u32& fail, _6502& CPU, memory& mem); // Currently unsupported
    void __TEST_TXA      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_TXS      (u32& fail, _6502& CPU, memory& mem); // Currently unsupported
    void __TEST_TYA      (u32& fail, _6502& CPU, memory& mem);

    void __TEST_JMP_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_JMP_IND  (u32& fail, _6502& CPU, memory& mem); // Currently unsupported
  
    void __TEST_DEC_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_DEC_ZPX  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_DEC_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_DEC_ABSX (u32& fail, _6502& CPU, memory& mem);
    void __TEST_DEX      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_DEY      (u32& fail, _6502& CPU, memory& mem);
 
    void __TEST_INC_ZP   (u32& fail, _6502& CPU, memory& mem);
    void __TEST_INC_ZPX  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_INC_ABS  (u32& fail, _6502& CPU, memory& mem);
    void __TEST_INC_ABSX (u32& fail, _6502& CPU, memory& mem);
    void __TEST_INX      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_INY      (u32& fail, _6502& CPU, memory& mem);

    void __TEST_PHA      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_PHP      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_PLA      (u32& fail, _6502& CPU, memory& mem);
    void __TEST_PLP      (u32& fail, _6502& CPU, memory& mem);
}

#endif // _TEST_H_
