#ifndef I8080_CPU_H
#define I8080_CPU_H

// ==============================================================
// cpu.h | Processor Header
// ==============================================================

// Main Include
#include "i8080.h"

// Includes
#include <bitset>

// Defines
#define I8080_REG_A 7
#define I8080_REG_B 0
#define I8080_REG_C 1
#define I8080_REG_D 2
#define I8080_REG_E 3
#define I8080_REG_H 4
#define I8080_REG_L 5
#define I8080_REG_M 6

#define I8080_REG_BC 0
#define I8080_REG_DE 2
#define I8080_REG_HL 4

namespace i8080 {
    class cpu;

    extern cpu processor;
}

class i8080::cpu {
private:
    struct reg {
        union {
            u16 x;
            #if (__BYTE_ORDER == __LITTLE_ENDIAN)
            struct {
                u8 xl;
                u8 xh;
            };
            #elif (__BYTE_ORDER == __BIG_ENDIAN)
            struct {
                u8 xh;
                u8 xl;
            };
            #endif
        };
    };

    reg psw;

    reg b, d, h;

    u16 sp, pc;

    void execute();
public:
    inline reg& retPSW() { return psw; }
    inline u16 retM() { return h.x; }

    inline u16& retPC() { return pc; }
    inline u16& retSP() { return sp; }

    reg& retReg(u8);
};

#endif