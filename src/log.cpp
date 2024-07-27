#include "log.h"

namespace emu {
    void ReportAssert(const char* exp, const char* msg, int Line, const char* File) {
        EMU_FATAL("Failed to assert: {} msg: '{}'\n\tLine: {}\n\tFile: {}", exp, msg, Line, File);
        DEBUG_BREAK();
    }
}