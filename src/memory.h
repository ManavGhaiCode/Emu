#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "config.h"
#define MEMORY_SIZE 65536

namespace emu {
    class memory {
        public:
            Byte operator[](Word addr) const {
                return buffer[addr];
            }

            Byte& operator[](Word addr) {
                return buffer[addr];
            }

        private:
            Byte buffer[MEMORY_SIZE];
    };
}

#endif // _MEMORY_H_