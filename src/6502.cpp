#include "6502.h"
#include "log.h"

#define MI_P_NOP() EMU_DEBUG("Running MI: NOP")
#define MI_P_END() EMU_DEBUG("Running MI: END")

#define WRITE_MI(MI) m_Inst[m_InstPtr] = MI; m_InstPtr += 1

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
        X = 0x0;
        Y = 0x0;

        m_Status = 0x0;

        PC = 0x0;
        SP = 0x0;

        m_Next = true;
    }

    Byte _6502::FetchByte() {
        Byte ret = (*m_Mem)[PC];
        PC += 1;

        return ret;
    }

    Byte _6502::ReadByte(Word addr) {
        Byte ret = (*m_Mem)[addr];
        return ret;
    }

    void _6502::WriteByte(Word addr, Byte value) {
        (*m_Mem)[addr] = value;
        m_WritenMemory = value;
    }

    void _6502::ReadNextI() {
        Inst I = (Inst)FetchByte();

        switch (I) {
            case I_NOP: return;
            case I_LDA_IM: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_LDA_ZP: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_LDA_ZPX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CX);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_LDA_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_LDA_ABSX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CXW);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_A);

                Byte lo = ReadByte(PC + 1);
                if (lo + X > 0xFF) {
                    WRITE_MI(MI_NOP);
                }
            } break;

            case I_LDA_ABSY: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CYW);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_A);

                Byte lo = ReadByte(PC + 1);
                if (lo + Y > 0xFF) {
                    WRITE_MI(MI_NOP);
                }
            } break;

            case I_LDA_INDX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_ADD_CX);
                WRITE_MI(MI_CACHE_DNI);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_LDA_INDY: {
                // TODO: Implement
                ASSERT_MSG(false, "Implement");

                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_CACHE_DNI);
                WRITE_MI(MI_ADD_CYW);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_A);

                Byte lo = ReadByte(PC + 1);
                if (lo + Y > 0xFF) {
                    WRITE_MI(MI_NOP);
                }
            } break;

            case I_LDX_IM: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_LDX_ZP: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_LDX_ZPY: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CY);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_LDX_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_LDX_ABSY: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CYW);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_LDY_IM: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_WRITE_Y);
            } break;

            case I_LDY_ZP: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_WRITE_Y);
            } break;

            case I_LDY_ZPX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CX);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_WRITE_Y);
            } break;

            case I_LDY_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_Y);
            } break;

            case I_LDY_ABSX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CXW);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_Y);
            } break;

            case I_STA_ZP: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITEB);
            } break;

            case I_STA_ZPX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CX);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITEB);
            } break;

            case I_STA_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE);
            } break;

            case I_STA_ABSX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CXW);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE);
            } break;

            case I_STA_ABSY: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CYW);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE);
            } break;

            case I_STA_INDX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTEB);
                WRITE_MI(MI_ADD_CX);
                WRITE_MI(MI_CACHE_DNI);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE);
            } break;

            case I_STA_INDY: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_CACHE_DNI);
                WRITE_MI(MI_ADD_CYW);
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE);
            } break;

            case I_STX_ZP: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_X);
                WRITE_MI(MI_WRITEB);
            } break;

            case I_STX_ZPY: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CY);
                WRITE_MI(MI_READ_X);
                WRITE_MI(MI_WRITEB);
            } break;

            case I_STX_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_X);
                WRITE_MI(MI_WRITE);
            } break;

            case I_STY_ZP: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_Y);
                WRITE_MI(MI_WRITEB);
            } break;

            case I_STY_ZPX: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_ADD_CX);
                WRITE_MI(MI_READ_Y);
                WRITE_MI(MI_WRITEB);
            } break;

            case I_STY_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_Y);
                WRITE_MI(MI_WRITE);
            } break;

            case I_TAX: {
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_TAY: {
                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE_Y);
            } break;

            case I_TSX: {
                // TODO: Implement
                ASSERT_MSG(false, "Implement");

                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_TXA: {
                WRITE_MI(MI_READ_X);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_TXS: {
                // TODO: Implement
                ASSERT_MSG(false, "Implement");

                WRITE_MI(MI_READ_A);
                WRITE_MI(MI_WRITE_X);
            } break;

            case I_TYA: {
                WRITE_MI(MI_READ_Y);
                WRITE_MI(MI_WRITE_A);
            } break;

            case I_JMP_ABS: {
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_WRITE_PC);
            } break;

            case I_JMP_IND: {
                // TODO: Implement
                ASSERT_MSG(false, "Implement");

                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_FETCH_BYTE);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_CAHSE_DNIW_G2);
                WRITE_MI(MI_READ_BYTE);
                WRITE_MI(MI_WRITE_PC);
            } break;

            default: ASSERT(false && "Unreachable");
        }
    }

    void _6502::Clock() {
        if (m_Next) {
            m_CachePtr = 0;
            m_InstPtr = 0;

            m_Inst[0] = MI_NOP;
            ReadNextI();

            WRITE_MI(MI_END);
            m_Next = false;

            m_InstPtr = 0;
        }

        Run();
        m_InstPtr += 1;

        if (m_InstPtr >= 10) {
            m_InstPtr = 0;
            m_CachePtr = 0;

            WRITE_MI(MI_NOP);
        }
    }

    void _6502::Run() {
        MicroInst MicInst = m_Inst[m_InstPtr];
        if (MicInst == MI_END) { MI_P_END(); m_Next = true; Clock(); return; }
        if (MicInst == MI_NOP) { MI_P_NOP(); return; }

        RunMI(MicInst);

        // EMU_DEBUG("Running MI: {}", emu::MI_Names[MicInst]);
    }

    void _6502::RunMI(MicroInst MicInst) {
        switch (MicInst) {
            case MI_FETCH_BYTE: {
                m_Cache[m_CachePtr] = FetchByte();
                m_CachePtr += 1;
            } break;

            case MI_READ_BYTEB: {
                m_Cache[m_CachePtr] = ReadByte(m_Cache[m_CachePtr - 1]);
                m_CachePtr += 1;
            } break;

            case MI_READ_BYTE: {
                m_Cache[m_CachePtr - 2] = 
                    ReadByte((m_Cache[m_CachePtr - 1] << 8) | (m_Cache[m_CachePtr - 2]));

                m_CachePtr -= 1;
            } break;

            case MI_ADD_CX: {
                m_Cache[m_CachePtr - 1] += X;
            } break;

            case MI_ADD_CY: {
                m_Cache[m_CachePtr - 1] += Y;
            } break;

            case MI_ADD_CXW: {
                Word add = (Word)m_Cache[m_CachePtr - 2] + X;

                if (add > 0xFF) {
                    m_Cache[m_CachePtr - 1] += (add - 0xFF) >> 8;
                }
                
                m_Cache[m_CachePtr - 2] += X;
            } break;

            case MI_ADD_CYW: {
                Word add = (Word)m_Cache[m_CachePtr - 2] + Y;

                if (add > 0xFF) {
                    m_Cache[m_CachePtr - 1] += (add - 0xFF) >> 8;
                }
                
                m_Cache[m_CachePtr - 2] += Y;
            } break;

            case MI_WRITE_A: {
                A = m_Cache[m_CachePtr - 1];
                m_CachePtr -= 1;
            } break;

            case MI_WRITE_X: {
                X = m_Cache[m_CachePtr - 1];
                m_CachePtr -= 1;
            } break;

            case MI_WRITE_Y: {
                Y = m_Cache[m_CachePtr - 1];
                m_CachePtr -= 1;
            } break;

            case MI_READ_A: {
                m_Cache[m_CachePtr] = A;
                m_CachePtr += 1;
            } break;

            case MI_READ_X: {
                m_Cache[m_CachePtr] = X;
                m_CachePtr += 1;
            } break;

            case MI_READ_Y: {
                m_Cache[m_CachePtr] = Y;
                m_CachePtr += 1;
            } break;

            case MI_WRITE_PC: {
                PC = (m_Cache[m_CachePtr - 1] << 8) | (m_Cache[m_CachePtr - 2]);
            } break;

            case MI_WRITEB: {
                Byte addr = m_Cache[m_CachePtr - 2];
                WriteByte(addr, m_Cache[m_CachePtr - 1]);

                m_CachePtr -= 2;
            } break;

            case MI_WRITE: {
                Word addr = (m_Cache[m_CachePtr - 2] << 8) | (m_Cache[m_CachePtr - 3]);
                WriteByte(addr, m_Cache[m_CachePtr - 1]);

                m_CachePtr -= 3;
            }

            case MI_CACHE_DNI: {
                m_Cache[m_CachePtr] = m_Cache[m_CachePtr - 1] + 1;
                m_CachePtr += 1;
            } break;

            case MI_CAHSE_DNIW_G2: {
                m_Cache[m_CachePtr] = (m_Cache[m_CachePtr - 3] + 1);
                m_CachePtr += 1;

                m_Cache[m_CachePtr] = (m_Cache[m_CachePtr - 3] + 1);

                if (m_Cache[m_CachePtr - 1] == 0) {
                    m_Cache[m_CachePtr] += 1;
                }
            } break;

            default: ASSERT(false && "Unreachable");
        }
    }

    void _6502::WriteStatus(StatusMask mask, bool set) {
        if (set) {
            m_Status |= mask;
        } else {
            m_Status &= ~(mask);
        }
    }

    bool _6502::ReadStatus(StatusMask mask) {
        return m_Status & mask;
    }

    void _6502::WriteStatus() {
        switch (m_StatusWriter) {
            case SI_A: {
                WriteStatus(Z, A == 0);
                WriteStatus(N, A > 0x7F);
            }  break;

            case SI_X: {
                WriteStatus(Z, X == 0);
                WriteStatus(N, X > 0x7F);
            }  break;

            case SI_Y: {
                WriteStatus(Z, Y == 0);
                WriteStatus(N, Y > 0x7F);
            }  break;

            case SI_MEM: {
                WriteStatus(Z, m_WritenMemory == 0);
                WriteStatus(N, m_WritenMemory > 0x7F);
            }  break;
        }
    }
}