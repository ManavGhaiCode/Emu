#ifndef _6502_H_
#define _6502_H_

#include "config.h"
#include "memory.h"

namespace emu {
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
                    addressing	  assembler	    opc	  bytes	  cycles
                    immediate     LDA #oper     A9    2       2 
                    zeropage      LDA oper      A5    2       3 
                    zeropage,X    LDA oper,X    B5    2       4 
                    absolute      LDA oper      AD    3       4 
                    absolute,X    LDA oper,X    BD    3       4*
                    absolute,Y    LDA oper,Y    B9    3       4*
                    (indirect,X)  LDA (oper,X)  A1    2       6 
                    (indirect),Y  LDA (oper),Y  B1    2       5*
                */

                I_NOP = 0xEA,

                I_LDA_IM    = 0xA9,
                I_LDA_ZP    = 0xA5,
                I_LDA_ZP_X  = 0xB5,
                I_LDA_ABS   = 0xAD,
                I_LDA_ABS_X = 0xBD,
                I_LDA_ABS_Y = 0xB9,
                I_LDA_IND_X = 0xA1,
                I_LDA_IND_Y = 0xB1
            } Inst;

            void GetState();

            Byte A;
            Byte X;
            Byte Y; 

        private:
            typedef enum {
                MI_NOP = 0,

                MI_READ_BYTE,
                MI_READ_BYTE_FC,
                MI_WRITE_A,
                
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
            Byte ReadByte();
            Byte ReadByte(Byte addr);

            void RunMI(MicroInst MicInst);
    };
}

#endif // _6502_H_