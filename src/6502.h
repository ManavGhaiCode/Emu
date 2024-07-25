#include "config.h"

namespace emu {
    class _6502 {
        public:
            void Clock();
            void Init();

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

                I_LDA_IM    = 0xA9,
                I_LDA_ZP    = 0xA5,
                I_LDA_ZP_X  = 0xB5,
                I_LDA_ABS   = 0xAD,
                I_LDA_ABS_X = 0xBD,
                I_LDA_ABS_Y = 0xB9,
                I_LDA_IND_X = 0xA1,
                I_LDA_IND_Y = 0xB1
            } Inst;

        private:
            typedef enum {
                MI_NONE = 0,
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

            MicroInst m_Inst[10] = { MI_NONE };
            u8 m_InstPtr = 0;

            Byte m_Status;

            Byte A;
            Byte X;
            Byte Y; 

            Word PC;
            Byte SP;

            void Run();
    };
}