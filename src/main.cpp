// ==============================================================
// main.cpp | Mainboard Source File
// ==============================================================

// Main Include
#include "i8080.h"

// Includes

// Mainboard Definitions

// Externs
i8080::cpu i8080::processor;
i8080::mainboard i8080::mobo;

// Main Definition

int main() {
    // TEST CODE
    i8080::processor.retReg(0).x = 0xffff;
    i8080::processor.retReg(7).x = 0x0000;

    i8080::MOVr1r2(i8080::processor.retReg(7).xl, i8080::processor.retReg(0).xh);
    printf("Register x: %#-.4x\n", i8080::processor.retReg(7).x);

    return 0;
}