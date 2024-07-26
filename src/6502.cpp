#include "6502.h"
#include "log.h"

#define MI_P_NOP() EMU_DEBUG("Running MI: NOP")
#define MI_P_END() EMU_DEBUG("Running MI: END")

namespace emu {
    void _6502::Reset() {
        A = 0x0;
        X = 0x0;
        Y = 0x0;

        m_Status = 0x0;

        PC = 0xFFFE;
        SP = 0x0;

        m_Inst[0] = MI_NOP;
        m_Inst[9] = MI_END;
    }

    void _6502::Clock() {
        // if (m_Next) {
        //     m_InstPtr = 0;
        //     m_CachePtr = 0;

        //     m_Inst[0] = MI_NOP;

        //     m_Next = false;
        // }

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

        EMU_DEBUG("Running MI: {}", (u32)MicInst);
    }
}