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
            EMU_PASS("__TEST_LDX_ABSY");
        } else {
            EMU_FAIL("__TEST_LDX_ABSY");
            fail += 1;
        }
    }

    void __TEST_LDY_IM   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDY_IM;
        mem[0x0001] = 0xF0;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0xF0);

        if (pass) {
            EMU_PASS("__TEST_LDY_IM");
        } else {
            EMU_FAIL("__TEST_LDY_IM");
            fail += 1;
        }
    }

    void __TEST_LDY_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDY_ZP;
        mem[0x0001] = 0xF0;
        mem[0x00F0] = 0x50;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0x50);

        if (pass) {
            EMU_PASS("__TEST_LDY_ZP");
        } else {
            EMU_FAIL("__TEST_LDY_ZP");
            fail += 1;
        }
    }

    void __TEST_LDY_ZPX  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDY_ZPX;
        mem[0x0001] = 0x90;
        mem[0x00A0] = 0xFF;

        CPU.X = 0x10;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0xFF);

        if (pass) {
            EMU_PASS("__TEST_LDY_ZPY");
        } else {
            EMU_FAIL("__TEST_LDY_ZPY");
            fail += 1;
        }
    }

    void __TEST_LDY_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDY_ABS;
        mem[0x0001] = 0x90;
        mem[0x0002] = 0xFF;
        mem[0xFF90] = 0x21;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0x21);

        if (pass) {
            EMU_PASS("__TEST_LDY_ABS");
        } else {
            EMU_FAIL("__TEST_LDY_ABS");
            fail += 1;
        }
    }

    void __TEST_LDY_ABSX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_LDY_ABSX;
        mem[0x0001] = 0x90;
        mem[0x0002] = 0x55;
        mem[0x55E5] = 0x21;

        CPU.X = 0x55;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0x21);

        if (pass) {
            EMU_PASS("__TEST_LDY_ABSY");
        } else {
            EMU_FAIL("__TEST_LDY_ABSY");
            fail += 1;
        }
    }

    void __TEST_STA_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_ZP;
        mem[0x0001] = 0x20;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x0020] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_ZP");
        } else {
            EMU_FAIL("__TEST_STA_ZP");
            fail += 1;
        }
    }

    void __TEST_STA_ZPX  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0x10;
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_ZPX;
        mem[0x0001] = 0x20;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x0030] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_ZPX");
        } else {
            EMU_FAIL("__TEST_STA_ZPX");
            fail += 1;
        }
    }

    void __TEST_STA_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_ABS;
        mem[0x0001] = 0x20;
        mem[0x0002] = 0x30;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x3020] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_ABS");
        } else {
            EMU_FAIL("__TEST_STA_ABS");
            fail += 1;
        }
    }

    void __TEST_STA_ABSX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        
        CPU.X = 0x55;
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_ABSX;
        mem[0x0001] = 0x20;
        mem[0x0002] = 0x30;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x3075] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_ABSX");
        } else {
            EMU_FAIL("__TEST_STA_ABSX");
            fail += 1;
        }
    }

    void __TEST_STA_ABSY (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        
        CPU.Y = 0x55;
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_ABSY;
        mem[0x0001] = 0x20;
        mem[0x0002] = 0x30;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x3075] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_ABSY");
        } else {
            EMU_FAIL("__TEST_STA_ABSY");
            fail += 1;
        }
    }

    void __TEST_STA_INDX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        
        CPU.X = 0x55;
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_INDX;
        mem[0x0001] = 0x20;
        mem[0x0020] = 0x60;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0xB6B5] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_INDX");
        } else {
            EMU_FAIL("__TEST_STA_INDX");
            fail += 1;
        }
    }

    void __TEST_STA_INDY (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        
        CPU.X = 0x55;
        CPU.A = 0x22;

        mem[0x0000] = _6502::I_STA_INDX;
        mem[0x0001] = 0x20;
        mem[0x0020] = 0x60;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0xB6B5] == 0x22);

        if (pass) {
            EMU_PASS("__TEST_STA_INDY");
        } else {
            EMU_FAIL("__TEST_STA_INDY");
            fail += 1;
        }
    }

    void __TEST_STX_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.X = 0x50;

        mem[0x0000] = _6502::I_STX_ZP;
        mem[0x0001] = 0xF0;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x00F0] == 0x50);

        if (pass) {
            EMU_PASS("__TEST_STX_ZP");
        } else {
            EMU_FAIL("__TEST_STX_ZP");
            fail += 1;
        }
    }

    void __TEST_STX_ZPY  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0x53;
        CPU.Y = 0x0F;

        mem[0x0000] = _6502::I_STX_ZPY;
        mem[0x0001] = 0xF0;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x00FF] == 0x53);

        if (pass) {
            EMU_PASS("__TEST_STX_ZPY");
        } else {
            EMU_FAIL("__TEST_STX_ZPY");
            fail += 1;
        }
    }

    void __TEST_STX_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.X = 0x10;

        mem[0x0000] = _6502::I_STX_ABS;
        mem[0x0001] = 0xF0;
        mem[0x0002] = 0xA2;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0xA2F0] == 0x10);

        if (pass) {
            EMU_PASS("__TEST_STX_ABS");
        } else {
            EMU_FAIL("__TEST_STX_ABS");
            fail += 1;
        }
    }

    void __TEST_STY_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.Y = 0x50;

        mem[0x0000] = _6502::I_STY_ZP;
        mem[0x0001] = 0xF0;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x00F0] == 0x50);

        if (pass) {
            EMU_PASS("__TEST_STY_ZP");
        } else {
            EMU_FAIL("__TEST_STY_ZP");
            fail += 1;
        }
    }

    void __TEST_STY_ZPX  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.Y = 0x53;
        CPU.X = 0x0F;

        mem[0x0000] = _6502::I_STY_ZPX;
        mem[0x0001] = 0xF0;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x00FF] == 0x53);

        if (pass) {
            EMU_PASS("__TEST_STY_ZPY");
        } else {
            EMU_FAIL("__TEST_STY_ZPY");
            fail += 1;
        }
    }

    void __TEST_STY_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.Y = 0x53;

        mem[0x0000] = _6502::I_STY_ABS;
        mem[0x0001] = 0x40;
        mem[0x0002] = 0xA2;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0xA240] == 0x53);

        if (pass) {
            EMU_PASS("__TEST_STY_ABS");
        } else {
            EMU_FAIL("__TEST_STY_ABS");
            fail += 1;
        }
    }

    void __TEST_TAX      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.A = 0x10;
        mem[0x0000] = _6502::I_TAX;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == CPU.A);

        if (pass) {
            EMU_PASS("__TEST_TAX");
        } else {
            EMU_FAIL("__TEST_TAX");
            fail += 1;
        }
    }

    void __TEST_TAY      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.A = 0x10;
        mem[0x0000] = _6502::I_TAY;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == CPU.A);

        if (pass) {
            EMU_PASS("__TEST_TAY");
        } else {
            EMU_FAIL("__TEST_TAY");
            fail += 1;
        }
    }

    void __TEST_TSX      (u32& fail, _6502& CPU, memory& mem); // Currently unsupported

    void __TEST_TXA      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0x10;
        mem[0x0000] = _6502::I_TXA;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == CPU.X);

        if (pass) {
            EMU_PASS("__TEST_TXA");
        } else {
            EMU_FAIL("__TEST_TXA");
            fail += 1;
        }
    }

    void __TEST_TXS      (u32& fail, _6502& CPU, memory& mem); // Currently unsupported

    void __TEST_TYA      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.Y = 0x10;
        mem[0x0000] = _6502::I_TYA;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == CPU.Y);

        if (pass) {
            EMU_PASS("__TEST_TYA");
        } else {
            EMU_FAIL("__TEST_TYA");
            fail += 1;
        }
    }

    void __TEST_JMP_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_JMP_ABS;
        mem[0x0001] = 0xFC;
        mem[0x0002] = 0xFF;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.PC == 0xFFFC);

        if (pass) {
            EMU_PASS("__TEST_JMP_ABS");
        } else {
            EMU_FAIL("__TEST_JMP_ABS");
            fail += 1;
        }
    }

    void __TEST_JMP_IND  (u32& fail, _6502& CPU, memory& mem); // Currently unsupported

    void __TEST_DEC_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_DEC_ZP;
        mem[0x0001] = 0x30;
        mem[0x0030] = 0x41;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x0030] == 0x40);

        if (pass) {
            EMU_PASS("__TEST_DEC_ZP");
        } else {
            EMU_FAIL("__TEST_DEC_ZP");
            fail += 1;
        }
    }

    void __TEST_DEC_ZPX  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0x10;

        mem[0x0000] = _6502::I_DEC_ZPX;
        mem[0x0001] = 0x20;
        mem[0x0030] = 0x41;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        
        bool pass = (mem[0x0030] == 0x40);

        if (pass) {
            EMU_PASS("__TEST_DEC_ZPX");
        } else {
            EMU_FAIL("__TEST_DEC_ZPX");
            fail += 1;
        }
    }

    void __TEST_DEC_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        
        mem[0x0000] = _6502::I_DEC_ABS;
        mem[0x0001] = 0x30;
        mem[0x0002] = 0x41;
        mem[0x4130] = 0xA2;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x4130] == 0xA1);

        if (pass) {
           EMU_PASS("__TEST_DEC_ABS");
        } else {
            EMU_FAIL("__TEST_DEC_ABS");
            fail += 1;
        }
    }

    void __TEST_DEC_ABSX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0x1A;
        
        mem[0x0000] = _6502::I_DEC_ABSX;
        mem[0x0001] = 0x30;
        mem[0x0002] = 0x41;
        mem[0x414A] = 0xA2;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x414A] == 0xA1);

        if (pass) {
           EMU_PASS("__TEST_DEC_ABSX");
        } else {
            EMU_FAIL("__TEST_DEC_ABSX");
            fail += 1;
        }
    }

    void __TEST_DEX      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.X = 0x21;

        mem[0x0000] = _6502::I_DEX;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0x20);

        if (pass) {
            EMU_PASS("__TEST_DEX");
        } else {
            EMU_FAIL("__TEST_DEX");
            fail += 1;
        }
    }

    void __TEST_DEY      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.Y = 0x21;

        mem[0x0000] = _6502::I_DEY;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0x20);

        if (pass) {
            EMU_PASS("__TEST_DEY");
        } else {
            EMU_FAIL("__TEST_DEY");
            fail += 1;
        }
    }

    void __TEST_INC_ZP   (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        mem[0x0000] = _6502::I_INC_ZP;
        mem[0x0001] = 0x30;
        mem[0x0030] = 0x41;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x0030] == 0x42);

        if (pass) {
            EMU_PASS("__TEST_INC_ZP");
        } else {
            EMU_FAIL("__TEST_INC_ZP");
            fail += 1;
        }
    }

    void __TEST_INC_ZPX  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0xA0;
        
        mem[0x0000] = _6502::I_INC_ZPX;
        mem[0x0001] = 0x30;
        mem[0x00D0] = 0x41;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x00D0] == 0x42);

        if (pass) {
            EMU_PASS("__TEST_INC_ZPX");
        } else {
            EMU_FAIL("__TEST_INC_ZPX");
            fail += 1;
        }
    }

    void __TEST_INC_ABS  (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        
        mem[0x0000] = _6502::I_INC_ABS;
        mem[0x0001] = 0x30;
        mem[0x0002] = 0x41;
        mem[0x4130] = 0xA2;

        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x4130] == 0xA3);

        if (pass) {
           EMU_PASS("__TEST_INC_ABS");
        } else {
            EMU_FAIL("__TEST_INC_ABS");
            fail += 1;
        }
    }

    void __TEST_INC_ABSX (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();

        CPU.X = 0x1A;
        
        mem[0x0000] = _6502::I_INC_ABSX;
        mem[0x0001] = 0x30;
        mem[0x0002] = 0x41;
        mem[0x414A] = 0xA1;
        
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x414A] == 0xA2);

        if (pass) {
           EMU_PASS("__TEST_INC_ABSX");
        } else {
            EMU_FAIL("__TEST_INC_ABSX");
            fail += 1;
        }
    }

    void __TEST_INX      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.X = 0x21;

        mem[0x0000] = _6502::I_INX;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.X == 0x22);

        if (pass) {
            EMU_PASS("__TEST_INX");
        } else {
            EMU_FAIL("__TEST_INX");
            fail += 1;
        }
    }

    void __TEST_INY      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.Y = 0x21;

        mem[0x0000] = _6502::I_INY;

        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.Y == 0x22);

        if (pass) {
            EMU_PASS("__TEST_INY");
        } else {
            EMU_FAIL("__TEST_INY");
            fail += 1;
        }
    }

    void __TEST_PHA      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.A = 0x10;

        mem[0x0000] = _6502::I_PHA;

        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x0200] == 0x10);

        if (pass) {
            EMU_PASS("TEST_PHA");
        } else {
            EMU_FAIL("TEST_PHA");
            fail += 1;
        }
    }

    void __TEST_PHP      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.SetStatus(0xF5);
        
        mem[0x0000] = _6502::I_PHP;

        CPU.Clock();
        CPU.Clock();

        bool pass = (mem[0x0200] == 0xF5);

        if (pass) {
            EMU_PASS("TEST_PHP");
        } else {
            EMU_FAIL("TEST_PHP");
            fail += 1;
        }
    }

    void __TEST_PLA      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.SP -= 1;
        
        mem[0x0000] = _6502::I_PLA;
        mem[0x0200] = 0xA0;
        
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.A == 0xA0);

        if (pass) {
            EMU_PASS("TEST_PLA");
        } else {
            EMU_FAIL("TEST_PLA");
            fail += 1;
        }
    }

    void __TEST_PLP      (u32& fail, _6502& CPU, memory& mem) {
        CPU.Reset();
        CPU.SP -= 1;
        
        mem[0x0000] = _6502::I_PLP;
        mem[0x0200] = 0xA0;
        
        CPU.Clock();
        CPU.Clock();

        bool pass = (CPU.GetStatus() == 0xA0);

        if (pass) {
            EMU_PASS("TEST_PLP");
        } else {
            EMU_FAIL("TEST_PLP");
            fail += 1;
        }
    }
}
