#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef long i64;
typedef unsigned long u64;
typedef int i32;
typedef unsigned int u32;
typedef short i16;
typedef unsigned short u16;
typedef char i8;
typedef unsigned char u8;

#ifdef __linux__
    #ifdef __x86_64
        #define LINUX
    #else
        #error "64-bit distro installation requied!"
    #endif
#elif defined (_WIN32)
    #ifdef _WIN64
        #define WINDOWS
        #define WIN32_LEAN_AND_MEAN

        #include <windows.h>
    #else
        #error "64-bit Windows required!"
    #endif
#else
    #error "Unsupported Platform!"
#endif

#ifndef RELEASE
    #define DEBUG
#endif

#ifndef USE_ASSERTS
    #define USE_ASSERTS 1
#endif

#endif // _CONFIG_H_