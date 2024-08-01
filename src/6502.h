#ifndef _6502_H_
#define _6502_H_

#include "config.h"
#include "memory.h"

namespace emu {
    static const char* MI_Names[] = {
        "MI_READ_BYTE",
        "MI_READ_BYTE_FCB",
        "MI_READ_BYTE_FC",

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

        "MI_WRITE",
        "MI_WRITEB"

        "MI_CACHE_DNI",

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
            } Inst;

            void GetState();

            Byte A;
            Byte X;
            Byte Y; 

        private:
            typedef enum {
                MI_NOP = 0,

                MI_READ_BYTE,
                MI_READ_BYTE_FCB,
                MI_READ_BYTE_FC,

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

                MI_WRITE,
                MI_WRITEB,

                MI_CACHE_DNI,

                MI_END
            } MicroInst;

            typedef enum {
                N = 0x01,
                Z = 0x02,
                C = 0x04,
                I = 0x08,
                D = 0x10,
                V = 0x20,
            } StatsMask;

            MicroInst m_Inst[10] = { MI_NOP };
            u8 m_InstPtr = 0;

            Byte m_Status;

            Word PC;
            Byte SP;

            memory* m_Mem;
            Byte m_Cache[10] = {0};

            Byte m_CachePtr;
            bool m_Next;

            void Run();

            void ReadNextI();
            Byte FetchByte();
            Byte ReadByte(Word addr);

            void WriteByte(Word addr, Byte value);

            void RunMI(MicroInst MicInst);
    };
}

#endif // _6502_H_