// ==============================================================
// cpu.cpp | Processor Source File
// ==============================================================

// Main Include
#include "i8080.h"

// Includes

// Processor Definitions

// retReg - Return Register Pair
// Arguments: u8 reg - Register ID
i8080::cpu::reg& i8080::cpu::retReg(u8 reg) {
    switch (reg) {
        case 0:
        case 1:
            return b;
            break;
        case 2:
        case 3:
            return d;
            break;
        case 4:
        case 5:
            return h;
            break;
        case 6:
            return h;
            break;
        case 7:
            return psw;
            break;
    }
}

// execute - Execute Function
// Arguments: none
void i8080::cpu::execute() {

}