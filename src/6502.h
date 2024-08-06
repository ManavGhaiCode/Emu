#ifndef _6502_H_
#define _6502_H_

#include "config.h"
#include "memory.h"

namespace emu {
    static const char* MI_Names[] = {
        "MI_NOP",

        "MI_FETCH_BYTE",
        "MI_READ_BYTEB",
        "MI_READ_BYTE",

        "MI_ADD_CX",
        "MI_ADD_CY",
        "MI_ADD_CXW",
        "MI_ADD_CYW",

        "MI_WRITE_A",
        "MI_WRITE_Y",
        "MI_WRITE_X",
        "MI_READ_A",
        "MI_READ_X",
        "MI_READ_Y",
        "MI_DEC_X",
        "MI_DEC_Y",
        "MI_INC_X",
        "MI_INC_Y",

        "MI_WRITE_PC",
        "MI_READ_PC",

        "MI_WRITE",
        "MI_WRITEB",

        "MI_CACHE_DNI",
        "MI_CACHE_DEC",
        "MI_CACHE_INC",
        "MI_CAHSE_DNIW_G2",

        "MI_END"
    };

    class _6502 {
        public:
            _6502()
                : m_Mem (nullptr)
                , m_Next (true)
            {};

            void Clock();
            void Reset();

            void BindMemory(memory* mem) {
                m_Mem = mem;
            }

            typedef enum {
                /*
                    addressing    assembler     opc   bytes   cycles
                    immediate     LDA #oper     A9      2       2 
                    zeropage      LDA oper      A5      2       3 
                    zeropage,X    LDA oper,X    B5      2       4 
                    absolute      LDA oper      AD      3       4 
                    absolute,X    LDA oper,X    BD      3       4*
                    absolute,Y    LDA oper,Y    B9      3       4*
                    (indirect,X)  LDA (oper,X)  A1      2       6 
                    (indirect),Y  LDA (oper),Y  B1      2       5*
                */

                I_NOP = 0xEA,

                I_LDA_IM   = 0xA9,
                I_LDA_ZP   = 0xA5,
                I_LDA_ZPX  = 0xB5,
                I_LDA_ABS  = 0xAD,
                I_LDA_ABSX = 0xBD,
                I_LDA_ABSY = 0xB9,
                I_LDA_INDX = 0xA1,
                I_LDA_INDY = 0xB1,

                /*
                    addressing    assembler     opc   bytes   cycles
                    immediate     LDX #oper     A2      2       2  
                    zeropage      LDX oper      A6      2       3  
                    zeropage,Y    LDX oper,Y    B6      2       4  
                    absolute      LDX oper      AE      3       4  
                    absolute,Y    LDX oper,Y    BE      3       4* 
                */

                I_LDX_IM   = 0xA2,
                I_LDX_ZP   = 0xA6,
                I_LDX_ZPY  = 0xB6,
                I_LDX_ABS  = 0xAE,
                I_LDX_ABSY = 0xBE,

                /*
                    addressing    assembler     opc   bytes   cycles
                    immediate     LDY #oper     A0      2       2  
                    zeropage      LDY oper      A4      2       3  
                    zeropage,X    LDY oper,X    B4      2       4  
                    absolute      LDY oper      AC      3       4  
                    absolute,X    LDY oper,X    BC      3       4* 
                */

                I_LDY_IM   = 0xA0,
                I_LDY_ZP   = 0xA4,
                I_LDY_ZPX  = 0xB4,
                I_LDY_ABS  = 0xAC,
                I_LDY_ABSX = 0xBC,

                /*
                    addressing    assembler     opc    bytes   cycles
                    zeropage      STA oper      85       2       3
                    zeropage,X    STA oper,X    95       2       4
                    absolute      STA oper      8D       3       4
                    absolute,X    STA oper,X    9D       3       5
                    absolute,Y    STA oper,Y    99       3       5
                    (indirect,X)  STA (oper,X)  81       2       6
                    (indirect),Y  STA (oper),Y  91       2       6
                */

                I_STA_ZP   = 0x85,
                I_STA_ZPX  = 0x95,
                I_STA_ABS  = 0x8D,
                I_STA_ABSX = 0x9D,
                I_STA_ABSY = 0x99,
                I_STA_INDX = 0x81,
                I_STA_INDY = 0x91,

                /*
                    addressing    assembler     opc    bytes    cycles
                    zeropage      STX oper      86       2        3  
                    zeropage,Y    STX oper,Y    96       2        4  
                    absolute      STX oper      8E       3        4  
                */

                I_STX_ZP  = 0x86,
                I_STX_ZPY = 0x96,
                I_STX_ABS = 0x8E,

                /*
                    addressing    assembler     opc    bytes    cycles
                    zeropage      STY oper      84       2        3  
                    zeropage,X    STY oper,X    94       2        4  
                    absolute      STY oper      8C       3        4 
                */

                I_STY_ZP  = 0x84,
                I_STY_ZPX = 0x94,
                I_STY_ABS = 0x8C,

                /* 
                    addressing    assembler     opc    bytes    cycles
                    implied       TAX           AA       1        2  
                    implied       TAY           A8       1        2  
                    implied       TSX           BA       1        2  
                    implied       TXA           8A       1        2  
                    implied       TXS           9A       1        2  
                    implied       TYA           98       1        2  
                */

                I_TAX = 0xAA,
                I_TAY = 0xA8,
                I_TSX = 0xBA,
                I_TXA = 0x8A,
                I_TXS = 0x9A,
                I_TYA = 0x98,

                /*
                    addressing    assembler     opc    bytes    cycles
                    absolute      JMP oper      4C       3        3 
                    indirect      JMP (oper)    6C       3        5 
                */

                I_JMP_ABS = 0x4C,
                I_JMP_IND = 0x6C,

                /*
                    addressing    assembler     opc    bytes   cycles
                    zeropage      DEC oper      C6       2       5  
                    zeropage,X    DEC oper,X    D6       2       6  
                    absolute      DEC oper      CE       3       6  
                    absolute,X    DEC oper,X    DE       3       7  
                */

                I_DEC_ZP   = 0xC6,
                I_DEC_ZPX  = 0xD6,
                I_DEC_ABS  = 0xCE,
                I_DEC_ABSX = 0xDE,

                /*
                    addressing    assembler     opc    bytes    cycles
                    implied       DEX           CA       1        2  
                    implied       DEY           88       1        2  
                */

                I_DEX = 0xCA,
                I_DEY = 0x88,

                /*
                    addressing    assembler     opc    bytes    cycles
                    zeropage      INC oper      E6       2        5  
                    zeropage,X    INC oper,X    F6       2        6  
                    absolute      INC oper      EE       3        6  
                    absolute,X    INC oper,X    FE       3        7  
                */

                I_INC_ZP   = 0xE6,
                I_INC_ZPX  = 0xF6,
                I_INC_ABS  = 0xEE,
                I_INC_ABSX = 0xFE,

                /*
                    addressing    assembler     opc    bytes    cycles
                    implied       INX           E8       1        2  
                    implied       INY           C8       1        2 
                */

                I_INX = 0xE8,
                I_INY = 0xC8

                /*
                    addressing    assembler     opc    bytes    cycles
                    implied       PHA           48       1        3  
                    implied       PHP           08       1        3  
                    implied       PLA           68       1        4
                    implied       PLP           28       1        4
                */

                I_PHA = 0x,
                I_PHP = 0x,
                I_PLA = 0x,
                I_PLP = 0x,
            } Inst;

            void GetState();

            Byte A;
            Byte X;
            Byte Y; 

            Word PC;

        private:
            typedef enum {
                MI_NOP = 0,

                MI_FETCH_BYTE,
                MI_READ_BYTEB,
                MI_READ_BYTE,

                MI_ADD_CX,
                MI_ADD_CY,
                MI_ADD_CXW,
                MI_ADD_CYW,

                MI_WRITE_A,
                MI_WRITE_Y,
                MI_WRITE_X,
                MI_READ_A,
                MI_READ_X,
                MI_READ_Y,
                MI_DEC_X,
                MI_DEC_Y,
                MI_INC_X,
                MI_INC_Y,

                MI_WRITE_PC,
                MI_READ_PC,

                MI_WRITE,
                MI_WRITEB,

                MI_CACHE_DNI,
                MI_CACHE_DEC,
                MI_CACHE_INC,
                MI_CAHSE_DNIW_G2,

                MI_END
            } MicroInst;

            typedef enum {
                N = 0x01,
                Z = 0x02,
                C = 0x04,
                I = 0x08,
                D = 0x10,
                V = 0x20,
            } StatusMask;

            typedef enum {
                SI_A,
                SI_X,
                SI_Y,
                SI_MEM,
            } StatusInst;

            StatusInst m_StatusWriter;

            MicroInst m_Inst[10] = { MI_NOP };
            u8 m_InstPtr = 0;

            Byte m_Status;

            Word SP;

            Byte m_WritenMemory;

            memory* m_Mem;
            Byte m_Cache[10] = {0};

            Byte m_CachePtr;
            bool m_Next;

            void Run();

            void ReadNextI();
            Byte FetchByte();
            Byte ReadByte(Word addr);
            void WriteByte(Word addr, Byte value);

            void WriteStatus(StatusMask mask, bool set);
            bool ReadStatus(StatusMask mask);

            void RunMI(MicroInst MicInst);

            void WriteStatus();
    };
}

#endif // _6502_H_
