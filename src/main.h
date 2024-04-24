#ifndef I8080_MAIN_H
#define I8080_MAIN_H

// ==============================================================
// main.h | Mainboard Header
// ==============================================================

// Main Include
#include "i8080.h"

#include <queue>
#include <chrono>

// Defines
#define I8080_CLOCK_STEP 0
#define I8080_CLOCK_FREE 1

// Namespace Extension
namespace i8080 {
    class mainboard;

    extern mainboard mobo;
}

class i8080::mainboard {
private:
    std::array<u8, 65536> mem;
    std::array<u8, 256> prt;

    bool mode = I8080_CLOCK_STEP;
public:
    // Memory
    inline u8 rByte(u16 addr) { return mem[((addr) & mAddr)]; }
    inline u8 rWord(u16 addr) { return (u16)mem[((addr + 1) & mAddr)] << 8 | mem[((addr) & mAddr)]; }

    inline void wByte(u16 addr, u8 data) { mem[((addr) & mAddr)] = data; }
    inline void wWord(u16 addr, u16 data) { mem[((addr + 1) & mAddr)] = data >> 8; mem[((addr) & mAddr)] = data; }

    // Ports
    inline u8 rPrt(u8 addr) { return prt[addr]; }

    inline void wPrt(u8 addr, u8 data) { prt[addr] = data; }

    // Cycles
    uint64_t cycles = 0;

    // Clock
    inline bool getMode() { return mode; }
    inline void freerun() { mode = I8080_CLOCK_FREE; }

    // Running?
    bool running = true;

    // Stepping?
    bool stepping = false;

    // Interrupt Queue
    std::queue<u8> interrupts;

    // SP Offset
    u16 spOffset = 0x0;

    // Mirror Address
    u16 mAddr = 0x0;

    // Interrupts Enabled?
    bool intEn = true;
};

#endif