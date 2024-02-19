#ifndef I8080_CPU_H
#define I8080_CPU_H

// ==============================================================
// cpu.h | Processor Header
// ==============================================================

// Main Include
#include "i8080.h"

// Defines - FUTURE TO BE DECIDED
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

#define I8080_FLAG_C 0x1
#define I8080_FLAG_P 0x2
#define I8080_FLAG_A 0x4
#define I8080_FLAG_Z 0x8
#define I8080_FLAG_S 0x10
#define I8080_FLAG_ALL 0x1f

#define I8080_OP_ADD 0
#define I8080_OP_SUB 1
#define I8080_OP_AND 2
#define I8080_OP_OR  3
#define I8080_OP_XOR 4

// Namespace Extension
namespace i8080 {
    struct ARGS;
    
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

    inline void setCarry() { psw.xh |= 0x1; }
    inline void clrCarry() { psw.xh &= 0xfe; }
    inline bool retCarry() { return psw.xh & 0x1; }

    inline void setParity() { psw.xh |= 0x4; }
    inline void clrParity() { psw.xh &= 0xfb; }
    inline bool retParity() { return psw.xh & 0x4; }

    inline void setACarry() { psw.xh |= 0x10; }
    inline void clrACarry() { psw.xh &= 0xef; }
    inline bool retACarry() { return psw.xh & 0x10; }

    inline void setZero() { psw.xh |= 0x40; }
    inline void clrZero() { psw.xh &= 0xbf; }
    inline bool retZero() { return psw.xh & 0x40; }

    inline void setSign() { psw.xh |= 0x80; }
    inline void clrSign() { psw.xh &= 0x7f; }
    inline bool retSign() { return psw.xh & 0x80; }
};

#endif