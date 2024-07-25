#include "6502.h"

namespace emu {
    void _6502::Init() {
        A = 0x0;
        X = 0x0;
        Y = 0x0;

        m_Status = 0x0;

        PC = 0xFFFE;
        SP = 0x0;
    }

    void _6502::Clock() {
        Run();
        m_InstPtr += 1;
    }

    void _6502::Run() {}
}