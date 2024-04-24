#ifndef I8080_CPU_H
#define I8080_CPU_H

// ==============================================================
// cpu.h | Processor Header
// ==============================================================

// Main Include
#include "i8080.h"

// Includes
#include <functional>

// Defines

// For debugging purposes
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

// To allow for easy function remapping in the future (if needed)
#define I8080_ER_CARRY processor.retCarry()
#define I8080_ES_CARRY processor.setCarry()
#define I8080_EC_CARRY processor.clrCarry()

#define I8080_ER_PARITY processor.retParity()
#define I8080_ES_PARITY processor.setParity()
#define I8080_EC_PARITY processor.clrParity()

#define I8080_ER_ACARRY processor.retACarry()
#define I8080_ES_ACARRY processor.setACarry()
#define I8080_EC_ACARRY processor.clrACarry()

#define I8080_ER_ZERO processor.retZero()
#define I8080_ES_ZERO processor.setZero()
#define I8080_EC_ZERO processor.clrZero()

#define I8080_ER_SIGN processor.retSign()
#define I8080_ES_SIGN processor.setSign()
#define I8080_EC_SIGN processor.clrSign()

// Flag Setting Macros
#define I8080_CARRY_ADD(a, b) (b > UINT8_MAX - a) ? I8080_ES_CARRY : I8080_EC_CARRY
#define I8080_CARRY_SUB(a, b) (b > a) ? I8080_ES_CARRY : I8080_EC_CARRY

#define I8080_PARITY(a) int x = a ^ (a >> 1); x ^= (x >> 2); x^= (x >> 4); (x & 1) ? I8080_EC_PARITY : I8080_ES_PARITY

#define I8080_ACARRY_ADD(a, b) ((a & 0xf) + (b & 0xf) > 0xf) ? I8080_ES_ACARRY : I8080_EC_ACARRY
#define I8080_ACARRY_SUB(a, b) int y = (a & 0x1f) - (b & 0xf); ((b & 0x10) ^ (a & 0x10)) ? I8080_ES_ACARRY : I8080_EC_ACARRY

#define I8080_ZERO(a) (a == 0) ? I8080_ES_ZERO : I8080_EC_ZERO

#define I8080_SIGN(a) (a & 0x80) ? I8080_ES_SIGN : I8080_EC_SIGN

// Bind Function Macro
#define INSBIND(a, b, args...) insTable[a] = { std::bind(b, args) }

// Namespace Extension
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

        reg(u16 val = 0) { x = val; }
        ~reg() { x = 0; }
    };

    reg psw;

    reg b, d, h;

    u16 sp, pc;

    std::array<std::function<u8()>, 256> insTable {};

    bool intEn = true;

    bool halted = true;
public:
    cpu();
    ~cpu();

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

    inline void halt() { halted = true; }
    inline void resume() { halted = false; }

    void reset();

    void execute();

    // Debug Functions
    inline bool getHalted() { return halted; }
    inline bool getIntEn() { return intEn; }
};

#endif