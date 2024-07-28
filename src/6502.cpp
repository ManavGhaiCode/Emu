#include "6502.h"
#include "log.h"

#include <unordered_map>

#define MI_P_NOP() EMU_DEBUG("Running MI: NOP")
#define MI_P_END() EMU_DEBUG("Running MI: END")

namespace emu {
    void _6502::GetState() {
        EMU_TRACE("GetState():\n\tA:  {}\n\tX:  {}\n\tY:  {}\n\tPC: {}\n\tSP: {}",
            (u32)A,
            (u32)X,
            (u32)Y,
            (u32)PC,
            (u32)SP
        );
    }

    void _6502::Reset() {
        A = 0x0;
        X = 0x10;
        Y = 0x0;

        m_Status = 0x0;

        PC = 0x0;
        SP = 0x0;

        (*m_Mem)[PC]     = I_LDA_ZPX;
        (*m_Mem)[PC + 1] = 0x10;
        (*m_Mem)[0x20]   = 0x1F;
        m_Inst[9] = MI_END;
    }

    Byte _6502::ReadByte() {
        Byte ret = (*m_Mem)[PC];
        PC += 1;

        return ret;
    }

    Byte _6502::ReadByte(Byte addr) {
        Byte ret = (*m_Mem)[addr];
        PC += 1;

        return ret;
    }

    void _6502::ReadNextI() {
        Inst I = (Inst)ReadByte();

        switch (I) {
            case I_NOP: return;
            case I_LDA_IM: {
                m_Inst[0] = MI_READ_BYTE;
                m_Inst[1] = MI_WRITE_A;

                m_InstPtr = 2;
            } break;

            case I_LDA_ZP: {
                m_Inst[0] = MI_READ_BYTE;
                m_Inst[1] = MI_READ_BYTE_FC;
                m_Inst[2] = MI_WRITE_A;

                m_InstPtr = 3;
            } break;

            case I_LDA_ZPX: {
                m_Inst[0] = MI_READ_BYTE;
                m_Inst[1] = MI_ADD_CX;
                m_Inst[2] = MI_READ_BYTE_FC;
                m_Inst[3] = MI_WRITE_A;

                m_InstPtr = 4;
            } break;

            default: ASSERT(false && "Unreachable");
        }
    }

    void _6502::Clock() {
        if (m_Next) {
            m_InstPtr = 1;
            m_CachePtr = 0;

            m_Inst[0] = MI_NOP;
            ReadNextI();

            m_Inst[m_InstPtr] = MI_END;
            m_Next = false;

            m_InstPtr = 0;
        }

        Run();
        m_InstPtr += 1;

        if (m_InstPtr >= 10) {
            m_InstPtr = 0;
            m_CachePtr = 0;

            m_Inst[0] = MI_NOP;
        }
    }

    void _6502::Run() {
        MicroInst MicInst = m_Inst[m_InstPtr];
        if (MicInst == MI_END) { MI_P_END(); m_Next = true; return; }
        if (MicInst == MI_NOP) { MI_P_NOP(); return; }

        RunMI(MicInst);

        EMU_DEBUG("Running MI: {}", (u32)MicInst);
    }

    void _6502::RunMI(MicroInst MicInst) {
        switch (MicInst) {
            case MI_READ_BYTE: {
                m_Cache[m_CachePtr] = ReadByte();
                m_CachePtr += 1;
            } break;

            case MI_READ_BYTE_FC: {
                m_Cache[m_CachePtr] = ReadByte(m_Cache[m_CachePtr - 1]);
                m_CachePtr += 1;
            } break;

            case MI_ADD_CX: {
                m_Cache[m_CachePtr - 1] += X;
            } break;

            case MI_WRITE_A: {
                A = m_Cache[m_CachePtr - 1];
                m_CachePtr -= 1;
            } break;

            default: ASSERT(false && "Unreachable");
        }
    }
}