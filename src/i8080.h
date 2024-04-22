#ifndef I8080_H
#define I8080_H

// ==============================================================
// i8080.h | Intel 8080 Emulator Header
// ==============================================================

// Includes
#include <cinttypes>

#define I8080_CYCLES 2000000

// Base Namespace
namespace i8080 {
    using u8 = uint8_t;
    using u16 = uint16_t;

    using s8 = int8_t;
    using s16 = int16_t;
}

// CPU Header
#include "cpu.h"

// Instructions Header
#include "ins.h"

// Mainboard Header
#include "main.h"

// UI Header
#include "ui.h"

#endif