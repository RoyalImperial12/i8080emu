// ==============================================================
// cpu.cpp | Processor Source File
// ==============================================================

// Main Include
#include "i8080.h"

// Includes

// Processor Definitions

// CPU Constructor
i8080::cpu::cpu() {
    psw.x = 0;

    b.x = d.x = h.x = 0;

    pc = sp = 0;

    // OpCodes 0x00 -> 0x0f
    insTable[0x00] = { []() { return 4; } }; // NOP
    INSBIND(0x01, LXI, pc, b.x);
    INSBIND(0x02, STAX, b.x, psw.xl);
    INSBIND(0x03, INX, b.x);
    INSBIND(0x04, INRr, b.xh);
    INSBIND(0x05, DCRr, b.xh);
    INSBIND(0x06, MVIrd, pc, b.xh);
    INSBIND(0x07, RLC, psw.xl);
    insTable[0x08] = { []() { return 4; } }; // NOP
    INSBIND(0x09, DAD, h.x, b.x);
    INSBIND(0x0a, LDAX, b.x, psw.xl);
    INSBIND(0x0b, DCX, b.x);
    INSBIND(0x0c, INRr, b.xl);
    INSBIND(0x0d, DCRr, b.xl);
    INSBIND(0x0e, MVIrd, pc, b.xl);
    INSBIND(0x0f, RRC, psw.xl);

    // OpCodes 0x10 -> 0x1f
    insTable[0x10] = { []() { return 4; } }; // NOP
    INSBIND(0x11, LXI, pc, d.x);
    INSBIND(0x12, STAX, d.x, psw.xl);
    INSBIND(0x13, INX, d.x);
    INSBIND(0x14, INRr, d.xh);
    INSBIND(0x15, DCRr, d.xh);
    INSBIND(0x16, MVIrd, pc, d.xh);
    INSBIND(0x17, RAL, psw.xl);
    insTable[0x18] = { []() { return 4; } }; // NOP
    INSBIND(0x19, DAD, h.x, d.x);
    INSBIND(0x1a, LDAX, d.x, psw.xl);
    INSBIND(0x1b, DCX, d.x);
    INSBIND(0x1c, INRr, d.xl);
    INSBIND(0x1d, DCRr, d.xl);
    INSBIND(0x1e, MVIrd, pc, d.xl);
    INSBIND(0x1f, RRC, psw.xl);

    // OpCodes 0x20 -> 0x2f
    insTable[0x20] = { []() { return 4; } }; // NOP
    INSBIND(0x21, LXI, pc, h.x);
    INSBIND(0x22, STAX, h.x, psw.xl);
    INSBIND(0x23, SHLD, pc, h.x);
    INSBIND(0x24, INRr, h.xh);
    INSBIND(0x25, DCRr, h.xh);
    INSBIND(0x26, MVIrd, pc, h.xh);
    INSBIND(0x27, DAA, psw.xl);
    insTable[0x28] = { []() { return 4; } }; // NOP
    INSBIND(0x29, DAD, h.x, h.x);
    INSBIND(0x2a, LHLD, pc, h.x);
    INSBIND(0x2b, DCX, h.x);
    INSBIND(0x2c, INRr, h.xl);
    INSBIND(0x2d, DCRr, h.xl);
    INSBIND(0x2e, MVIrd, pc, h.xl);
    INSBIND(0x2f, CMA, psw.xl);

    // OpCodes 0x30 -> 0x3f
    insTable[0x30] = { []() { return 4; } }; // NOP
    INSBIND(0x31, LXI, pc, sp);
    INSBIND(0x32, STA, pc, psw.xl);
    INSBIND(0x33, INX, sp);
    INSBIND(0x34, INRM, h.x);
    INSBIND(0x35, DCRM, h.x);
    INSBIND(0x36, MVIMd, pc, h.x);
    insTable[0x37] = { std::bind(STC) };
    insTable[0x38] = { []() { return 4; } }; // NOP
    INSBIND(0x39, DAD, h.x, sp);
    INSBIND(0x3a, LDA, pc, psw.xl);
    INSBIND(0x3b, DCX, sp);
    INSBIND(0x3c, INRr, psw.xl);
    INSBIND(0x3d, DCRr, psw.xl);
    INSBIND(0x3e, MVIrd, pc, psw.xl);
    insTable[0x3f] = { std::bind(CMC) };
}

// CPU Destructor
i8080::cpu::~cpu() {
    psw.x = 0;

    b.x = d.x = h.x = 0;

    pc = sp = 0;

    insTable.fill(0);
}

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

    return psw;
}

// execute - Execute Function
// Arguments: none
void i8080::cpu::execute() {

}