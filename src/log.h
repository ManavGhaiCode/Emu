#ifndef _LOG_H_
#define _LOG_H_

#include "config.h"

#include <string>
#include <sstream>
#include <iostream>

namespace Fuel {
    typedef enum {
        LOG_FATAL,
        LOG_ERROR,
        LOG_WARN,
        LOG_INFO,
        LOG_DEBUG,
        LOG_TRACE,
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
    #define TRACE(...) Fuel::Log(Fuel::LOG_TRACE, __VA_ARGS__)
    #define DEBUG(...) Fuel::Log(Fuel::LOG_DEBUG, __VA_ARGS__)
    #define INFO(...)  Fuel::Log(Fuel::LOG_INFO, __VA_ARGS__)
    #define WARN(...)  Fuel::Log(Fuel::LOG_WARN, __VA_ARGS__)

    #if USE_ASSERTS
        #define ASSERT_DEBUG(exp) if (exp) {} else { Fuel::ReportAssert(#exp, "", __LINE__, __FILE__); }
        #define STATIC_ASSERT(exp) static_assert(exp)
    #else
        #define ASSERT_DEBUG(exp) 
        #define STATIC_ASSERT(exp) 
    #endif
#else
    #define TRACE 
    #define DEBUG 
    #define INFO 
    #define WARN
#endif

#if USE_ASSERTS
    #define ASSERT(exp) if (exp) {} else { Fuel::ReportAssert(#exp, "", __LINE__, __FILE__); }
    #define ASSERT_MSG(exp, msg) if (exp) {} else { Fuel::ReportAssert(#exp, msg, __LINE__, __FILE__); }
#else
    #define ASSERT(exp)
    #define ASSERT_MSG(exp, msg)
#endif

#define ERROR(...) Fuel::Log(Fuel::LOG_ERROR, __VA_ARGS__)
#define FATAL(...) Fuel::Log(Fuel::LOG_FATAL, __VA_ARGS__)

#endif // _LOG_H_