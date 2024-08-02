#include "test.h"
#include "log.h"

namespace emu {
    void __TEST_LDA_IM   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDA_IM;
        mem[0x0001] = 0x0F;


        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x0F);

        if (pass) {
            EMU_PASS("__TEST_LDA_IM");
        } else {
            EMU_FAIL("__TEST_LDA_IM");
            fail += 1;
        }
    }

    void __TEST_LDA_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[CPU.PC] = _6502::I_LDA_ZP;
        mem[0x0001] = 0x0F;
        mem[0x000F] = 0x20;


        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x20);

        if (pass) {
            EMU_PASS("__TEST_LDA_ZP");
        } else {
            EMU_FAIL("__TEST_LDA_ZP");
            fail += 1;
        }
    }

    void __TEST_LDA_ZPX  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDA_ZPX;
        mem[0x0001] = 0x0F;
        mem[0x001F] = 0x20;

        CPU.X = 0x10;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x20);

        if (pass) {
            EMU_PASS("__TEST_LDA_ZPX");
        } else {
            EMU_FAIL("__TEST_LDA_ZPX");
            fail += 1;
        }
    }

    void __TEST_LDA_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDA_ABS;
        mem[0x0001] = 0xF0;
        mem[0x0002] = 0x12;
        mem[0x12F0] = 0x26;


        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x26);

        if (pass) {
            EMU_PASS("__TEST_LDA_ABS");
        } else {
            EMU_FAIL("__TEST_LDA_ABS");
            fail += 1;
        }
    }

    void __TEST_LDA_ABSX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();


        mem[0x0000] = _6502::I_LDA_ABSX;
        mem[0x0001] = 0xF0;
        mem[0x0002] = 0x12;
        mem[0x12FF] = 0x26;

        CPU.X = 0x0F;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x26);

        if (pass) {
            EMU_PASS("__TEST_LDA_ABSX");
        } else {
            EMU_FAIL("__TEST_LDA_ABSX");
            fail += 1;
        }
    }

    void __TEST_LDA_ABSY (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();


        mem[0x0000] = _6502::I_LDA_ABSY;
        mem[0x0001] = 0xF0;
        mem[0x0002] = 0x12;
        mem[0x12FF] = 0x26;

        CPU.Y = 0x0F;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x26);

        if (pass) {
            EMU_PASS("__TEST_LDA_ABSY");
        } else {
            EMU_FAIL("__TEST_LDA_ABSY");
            fail += 1;
        }
    }

    void __TEST_LDA_INDX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDA_INDX;
        mem[0x0001] = 0xF0;
        mem[0x00F0] = 0x13;
        mem[0x2423] = 0x26;

        CPU.X = 0x10;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0x26);

        if (pass) {
            EMU_PASS("__TEST_LDA_INDX");
        } else {
            EMU_FAIL("__TEST_LDA_INDX");
            fail += 1;
        }
    }

    void __TEST_LDA_INDY (u32& fail, _6502& CPU, memory& mem); // Currently Unsupported

    void __TEST_LDX_IM   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDX_IM;
        mem[0x0001] = 0xF0;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0xF0);

        if (pass) {
            EMU_PASS("__TEST_LDX_IM");
        } else {
            EMU_FAIL("__TEST_LDX_IM");
            fail += 1;
        }
    }

    void __TEST_LDX_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDX_ZP;
        mem[0x0001] = 0xF0;
        mem[0x00F0] = 0x50;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0x50);

        if (pass) {
            EMU_PASS("__TEST_LDX_ZP");
        } else {
            EMU_FAIL("__TEST_LDX_ZP");
            fail += 1;
        }
    }

    void __TEST_LDX_ZPY  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDX_ZPY;
        mem[0x0001] = 0x90;
        mem[0x00A0] = 0xFF;

        CPU.Y = 0x10;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0xFF);

        if (pass) {
            EMU_PASS("__TEST_LDX_ZPY");
        } else {
            EMU_FAIL("__TEST_LDX_ZPY");
            fail += 1;
        }
    }

    void __TEST_LDX_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDX_ABS;
        mem[0x0001] = 0x90;
        mem[0x0002] = 0xFF;
        mem[0xFF90] = 0x21;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0x21);

        if (pass) {
            EMU_PASS("__TEST_LDX_ABS");
        } else {
            EMU_FAIL("__TEST_LDX_ABS");
            fail += 1;
        }
    }

    void __TEST_LDX_ABSY (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDX_ABSY;
        mem[0x0001] = 0x90;
        mem[0x0002] = 0x55;
        mem[0x55E5] = 0x21;

        CPU.Y = 0x55;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0x21);

        if (pass) {
            EMU_PASS("__TEST_LDX_ABS");
        } else {
            EMU_FAIL("__TEST_LDX_ABS");
            fail += 1;
        }
    }

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
    void __TEST_JMP_IND  (u32& fail, _6502& CPU, memory& mem);
}