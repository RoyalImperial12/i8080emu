#ifndef I8080_MAIN_H
#define I8080_MAIN_H

// ==============================================================
// main.h | Mainboard Header
// ==============================================================

// Main Include
#include "i8080.h"

namespace i8080 {
    class mainboard;

    extern mainboard mobo;
}

class i8080::mainboard {
private:
    u8 mem[65536];
    u8 prt[256];
public:
    // Memory
    inline u8 rByte(u16 addr) { return mem[addr]; }
    inline u8 rWord(u16 addr) { return (u16)mem[addr + 1] << 8 | mem[addr]; }

    inline void wByte(u16 addr, u8 data) { mem[addr] = data; }
    inline void wWord(u16 addr, u16 data) { mem[addr + 1] = data >> 8; mem[addr] = data; }

    // Ports
    inline u8 rPrt(u8 addr) { return prt[addr]; }

    inline void wPrt(u8 addr, u8 data) { prt[addr] = data; }
};

#endif