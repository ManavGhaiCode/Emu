#include "6502.h"
#include "log.h"

namespace emu {
    void _6502::Reset() {
        A = 0x0;
        X = 0x0;
        Y = 0x0;

        m_Status = 0x0;

        PC = 0xFFFE;
        SP = 0x0;

        m_Inst[9] = MI_END;
    }

    void _6502::Clock() {
        Run();
        m_InstPtr += 1;

        if (m_InstPtr >= 10) {
            m_InstPtr = 0;
        }
    }

    void _6502::Run() {
        MicroInst MicInst = m_Inst[m_InstPtr];
        if (MicInst == MI_END) return;

        EMU_DEBUG("{} Hi", (u32)m_InstPtr);
    }
}