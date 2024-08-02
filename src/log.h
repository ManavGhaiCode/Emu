#ifndef _LOG_H_
#define _LOG_H_

#include "config.h"

#include <string>
#include <sstream>
#include <iostream>

namespace emu {
    typedef enum {
        LOG_FATAL,
        LOG_ERROR,
        LOG_WARN,
        LOG_INFO,
        LOG_DEBUG,
        LOG_TRACE,
        LOG_TEST_PASS,
        LOG_TEST_FAIL,
    } LogLevel;

    template<typename T>
    void format_helper(
        std::ostringstream& oss, 
        std::string& str, 
        const T& value
    ) {
        std::size_t openBracket = str.find('{');
        if (openBracket == std::string::npos) { return; }
        std::size_t closeBracket = str.find('}', openBracket + 1);
        if (closeBracket == std::string::npos) { return; }
        oss << str.substr(0, openBracket) << value;
        str = str.substr(closeBracket + 1);
    }

    template<typename... Targs>
    std::string format(
        std::string& str,
        Targs...args
    ) {
        std::ostringstream oss;
        (format_helper(oss, str, args), ...);
        oss << str;
        return oss.str();
    }

    template <typename... Targs>
    void Log(LogLevel level, std::string str, Targs... args) {
        const char* prefix;

        #ifdef LINUX
            const char* color;

            switch (level) {
                case LOG_TRACE: color = "\033[97m"; break;
                case LOG_DEBUG: color = "\033[92m"; break;
                case LOG_INFO:  color = "\033[94m"; break;
                case LOG_WARN:  color = "\033[93m"; break;
                case LOG_ERROR: color = "\033[91m"; break;
                case LOG_FATAL: color = "\033[31m"; break;

                case LOG_TEST_PASS: color = "\033[94m"; break;
                case LOG_TEST_FAIL: color = "\033[91m"; break;
                
                default: break;
            }
        #endif

        #ifdef WINDOWS
            i32 color = 0;

            switch (level) {
                case LOG_TRACE: color = 7; break;
                case LOG_DEBUG: color = 2; break;
                case LOG_INFO:  color = 1; break;
                case LOG_WARN:  color = 6; break;
                case LOG_ERROR: color = 4; break;
                case LOG_FATAL: color = 12; break;

                case LOG_TEST_PASS: color = 2; break;
                case LOG_TEST_FAIL: color = 4; break;
                
                default: break;
            }
        #endif

        switch (level) {
            case LOG_TRACE: prefix = "[TRACE] "; break;
            case LOG_DEBUG: prefix = "[DEBUG] "; break;
            case LOG_INFO:  prefix = "[ INFO] "; break;
            case LOG_WARN:  prefix = "[ WARN] "; break;
            case LOG_ERROR: prefix = "[ERROR] "; break;
            case LOG_FATAL: prefix = "[FATAL] "; break;

            case LOG_TEST_PASS: prefix = "[ PASS] "; break;
            case LOG_TEST_FAIL: prefix = "[ FAIL] "; break;
            
            default: break;
        }

        #ifdef LINUX
            std::cout << color << prefix << format(str, args...) << std::endl;
        #else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            std::cout << prefix << format(str, args...) << std::endl;
        #endif
    }

    void ReportAssert(const char* exp, const char* msg, int Line, const char* File);
}

#ifdef LINUX
    #define DEBUG_BREAK() __builtin_trap();
#elif defined (WINDOWS)
    #include <intrin.h>
    #define DEBUG_BREAK() __debugbreak();
#else
    #error "Unrachable"
#endif

#ifndef RELEASE
    #define EMU_TRACE(...) emu::Log(emu::LOG_TRACE, __VA_ARGS__)
    #define EMU_DEBUG(...) emu::Log(emu::LOG_DEBUG, __VA_ARGS__)
    #define EMU_INFO(...)  emu::Log(emu::LOG_INFO, __VA_ARGS__)
    #define EMU_WARN(...)  emu::Log(emu::LOG_WARN, __VA_ARGS__)

    #define EMU_PASS(...)  emu::Log(emu::LOG_TEST_PASS, __VA_ARGS__)
    #define EMU_FAIL(...)  emu::Log(emu::LOG_TEST_FAIL, __VA_ARGS__);

    #if USE_ASSERTS
        #define ASSERT_DEBUG(exp) if (exp) {} else { emu::ReportAssert(#exp, "", __LINE__, __FILE__); }
        #define STATIC_ASSERT(exp) static_assert(exp)
    #else
        #define ASSERT_DEBUG(exp) 
        #define STATIC_ASSERT(exp) 
    #endif
#else
    #define EMU_TRACE(...) 
    #define EMU_DEBUG(...) 
    #define EMU_INFO(...)
    #define EMU_WARN(...)

    #define EMU_PASS(...)
    #define EMU_FAIL(...)
#endif

#if USE_ASSERTS
    #define ASSERT(exp) if (exp) {} else { emu::ReportAssert(#exp, "", __LINE__, __FILE__); }
    #define ASSERT_MSG(exp, msg) if (exp) {} else { emu::ReportAssert(#exp, msg, __LINE__, __FILE__); }
#else
    #define ASSERT(exp)
    #define ASSERT_MSG(exp, msg)
#endif

#define EMU_ERROR(...) emu::Log(emu::LOG_ERROR, __VA_ARGS__)
#define EMU_FATAL(...) emu::Log(emu::LOG_FATAL, __VA_ARGS__)

#endif // _LOG_H_