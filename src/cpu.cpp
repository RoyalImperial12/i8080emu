// ==============================================================
// cpu.cpp | Processor Source File
// ==============================================================

// Main Include
#include "i8080.h"

// Includes
#include <cstdio>

// Processor Definitions

// CPU Constructor
i8080::cpu::cpu() {
    psw.x = 0;

    b.x = d.x = h.x = 0;

    pc = sp = 0;

    // OpCodes 0x00 -> 0x0f
    insTable[0x00] = { []() { return 4; } }; // NOP
    INSBIND(0x01, LXI, std::ref(pc), std::ref(b.x));
    INSBIND(0x02, STAX, std::ref(b.x), std::ref(psw.xl));
    INSBIND(0x03, INX, std::ref(b.x));
    INSBIND(0x04, INRr, std::ref(b.xh));
    INSBIND(0x05, DCRr, std::ref(b.xh));
    INSBIND(0x06, MVIrd, std::ref(pc), std::ref(b.xh));
    INSBIND(0x07, RLC, std::ref(psw.xl));
    insTable[0x08] = { []() { return 4; } }; // NOP
    INSBIND(0x09, DAD, std::ref(h.x), std::ref(b.x));
    INSBIND(0x0a, LDAX, std::ref(b.x), std::ref(psw.xl));
    INSBIND(0x0b, DCX, std::ref(b.x));
    INSBIND(0x0c, INRr, std::ref(b.xl));
    INSBIND(0x0d, DCRr, std::ref(b.xl));
    INSBIND(0x0e, MVIrd, std::ref(pc), std::ref(b.xl));
    INSBIND(0x0f, RRC, std::ref(psw.xl));

    // OpCodes 0x10 -> 0x1f
    insTable[0x10] = { []() { return 4; } }; // NOP
    INSBIND(0x11, LXI, std::ref(pc), std::ref(d.x));
    INSBIND(0x12, STAX, std::ref(d.x), std::ref(psw.xl));
    INSBIND(0x13, INX, std::ref(d.x));
    INSBIND(0x14, INRr, std::ref(d.xh));
    INSBIND(0x15, DCRr, std::ref(d.xh));
    INSBIND(0x16, MVIrd, std::ref(pc), std::ref(d.xh));
    INSBIND(0x17, RAL, std::ref(psw.xl));
    insTable[0x18] = { []() { return 4; } }; // NOP
    INSBIND(0x19, DAD, std::ref(h.x), std::ref(d.x));
    INSBIND(0x1a, LDAX, std::ref(d.x), std::ref(psw.xl));
    INSBIND(0x1b, DCX, std::ref(d.x));
    INSBIND(0x1c, INRr, std::ref(d.xl));
    INSBIND(0x1d, DCRr, std::ref(d.xl));
    INSBIND(0x1e, MVIrd, std::ref(pc), d.xl);
    INSBIND(0x1f, RRC, std::ref(psw.xl));

    // OpCodes 0x20 -> 0x2f
    insTable[0x20] = { []() { return 4; } }; // NOP
    INSBIND(0x21, LXI, std::ref(pc), std::ref(h.x));
    INSBIND(0x22, STAX, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0x23, SHLD, std::ref(pc), std::ref(h.x));
    INSBIND(0x24, INRr, std::ref(h.xh));
    INSBIND(0x25, DCRr, std::ref(h.xh));
    INSBIND(0x26, MVIrd, std::ref(pc), std::ref(h.xh));
    INSBIND(0x27, DAA, std::ref(psw.xl));
    insTable[0x28] = { []() { return 4; } }; // NOP
    INSBIND(0x29, DAD, std::ref(h.x), std::ref(h.x));
    INSBIND(0x2a, LHLD, std::ref(pc), std::ref(h.x));
    INSBIND(0x2b, DCX, std::ref(h.x));
    INSBIND(0x2c, INRr, std::ref(h.xl));
    INSBIND(0x2d, DCRr, std::ref(h.xl));
    INSBIND(0x2e, MVIrd, std::ref(pc), std::ref(h.xl));
    INSBIND(0x2f, CMA, std::ref(psw.xl));

    // OpCodes 0x30 -> 0x3f
    insTable[0x30] = { []() { return 4; } }; // NOP
    INSBIND(0x31, LXI, std::ref(pc), std::ref(sp));
    INSBIND(0x32, STA, std::ref(pc), std::ref(psw.xl));
    INSBIND(0x33, INX, std::ref(sp));
    INSBIND(0x34, INRM, std::ref(h.x));
    INSBIND(0x35, DCRM, std::ref(h.x));
    INSBIND(0x36, MVIMd, std::ref(pc), std::ref(h.x));
    insTable[0x37] = { std::bind(STC) };
    insTable[0x38] = { []() { return 4; } }; // NOP
    INSBIND(0x39, DAD, std::ref(h.x), std::ref(sp));
    INSBIND(0x3a, LDA, std::ref(pc), std::ref(psw.xl));
    INSBIND(0x3b, DCX, std::ref(sp));
    INSBIND(0x3c, INRr, std::ref(psw.xl));
    INSBIND(0x3d, DCRr, std::ref(psw.xl));
    INSBIND(0x3e, MVIrd, std::ref(pc), std::ref(psw.xl));
    insTable[0x3f] = { std::bind(CMC) };

    // OpCodes 0x40 -> 0x4f
    INSBIND(0x40, MOVr1r2, std::ref(b.xh), std::ref(b.xh));
    INSBIND(0x41, MOVr1r2, std::ref(b.xh), std::ref(b.xl));
    INSBIND(0x42, MOVr1r2, std::ref(b.xh), std::ref(d.xh));
    INSBIND(0x43, MOVr1r2, std::ref(b.xh), std::ref(d.xl));
    INSBIND(0x44, MOVr1r2, std::ref(b.xh), std::ref(h.xh));
    INSBIND(0x45, MOVr1r2, std::ref(b.xh), std::ref(h.xl));
    INSBIND(0x46, MOVMr, std::ref(h.x), std::ref(b.xh));
    INSBIND(0x47, MOVr1r2, std::ref(b.xh), std::ref(psw.xl));
    INSBIND(0x48, MOVr1r2, std::ref(b.xl), std::ref(b.xh));
    INSBIND(0x49, MOVr1r2, std::ref(b.xl), std::ref(b.xl));
    INSBIND(0x4a, MOVr1r2, std::ref(b.xl), std::ref(d.xh));
    INSBIND(0x4b, MOVr1r2, std::ref(b.xl), std::ref(d.xl));
    INSBIND(0x4c, MOVr1r2, std::ref(b.xl), std::ref(h.xh));
    INSBIND(0x4d, MOVr1r2, std::ref(b.xl), std::ref(h.xl));
    INSBIND(0x4e, MOVMr, std::ref(h.x), std::ref(b.xl));
    INSBIND(0x4f, MOVr1r2, std::ref(b.xl), std::ref(psw.xl));

    // OpCodes 0x50 -> 0x5f
    INSBIND(0x50, MOVr1r2, std::ref(d.xh), std::ref(b.xh));
    INSBIND(0x51, MOVr1r2, std::ref(d.xh), std::ref(b.xl));
    INSBIND(0x52, MOVr1r2, std::ref(d.xh), std::ref(d.xh));
    INSBIND(0x53, MOVr1r2, std::ref(d.xh), std::ref(d.xl));
    INSBIND(0x54, MOVr1r2, std::ref(d.xh), std::ref(h.xh));
    INSBIND(0x55, MOVr1r2, std::ref(d.xh), std::ref(h.xl));
    INSBIND(0x56, MOVMr, std::ref(h.x), std::ref(b.xh));
    INSBIND(0x57, MOVr1r2, std::ref(d.xh), std::ref(psw.xl));
    INSBIND(0x58, MOVr1r2, std::ref(d.xl), std::ref(b.xh));
    INSBIND(0x59, MOVr1r2, std::ref(d.xl), std::ref(b.xl));
    INSBIND(0x5a, MOVr1r2, std::ref(d.xl), std::ref(d.xh));
    INSBIND(0x5b, MOVr1r2, std::ref(d.xl), std::ref(d.xl));
    INSBIND(0x5c, MOVr1r2, std::ref(d.xl), std::ref(h.xh));
    INSBIND(0x5d, MOVr1r2, std::ref(d.xl), std::ref(h.xl));
    INSBIND(0x5e, MOVMr, std::ref(h.x), std::ref(b.xl));
    INSBIND(0x5f, MOVr1r2, std::ref(d.xl), std::ref(psw.xl));
    
    // OpCodes 0x60 -> 0x6f
    INSBIND(0x60, MOVr1r2, std::ref(h.xh), std::ref(b.xh));
    INSBIND(0x61, MOVr1r2, std::ref(h.xh), std::ref(b.xl));
    INSBIND(0x62, MOVr1r2, std::ref(h.xh), std::ref(d.xh));
    INSBIND(0x63, MOVr1r2, std::ref(h.xh), std::ref(d.xl));
    INSBIND(0x64, MOVr1r2, std::ref(h.xh), std::ref(h.xh));
    INSBIND(0x65, MOVr1r2, std::ref(h.xh), std::ref(h.xl));
    INSBIND(0x66, MOVMr, std::ref(h.x), std::ref(h.xh));
    INSBIND(0x67, MOVr1r2, std::ref(h.xh), std::ref(psw.xl));
    INSBIND(0x68, MOVr1r2, std::ref(h.xl), std::ref(b.xh));
    INSBIND(0x69, MOVr1r2, std::ref(h.xl), std::ref(b.xl));
    INSBIND(0x6a, MOVr1r2, std::ref(h.xl), std::ref(d.xh));
    INSBIND(0x6b, MOVr1r2, std::ref(h.xl), std::ref(d.xl));
    INSBIND(0x6c, MOVr1r2, std::ref(h.xl), std::ref(h.xh));
    INSBIND(0x6d, MOVr1r2, std::ref(h.xl), std::ref(h.xl));
    INSBIND(0x6e, MOVMr, std::ref(h.x), std::ref(h.xl));
    INSBIND(0x6f, MOVr1r2, std::ref(h.xl), std::ref(psw.xl));

    // OpCodes 0x70 -> 0x7f
    INSBIND(0x70, MOVMr, std::ref(h.x), std::ref(b.xh));
    INSBIND(0x71, MOVMr, std::ref(h.x), std::ref(b.xl));
    INSBIND(0x72, MOVMr, std::ref(h.x), std::ref(d.xh));
    INSBIND(0x73, MOVMr, std::ref(h.x), std::ref(d.xl));
    INSBIND(0x74, MOVMr, std::ref(h.x), std::ref(h.xh));
    INSBIND(0x75, MOVMr, std::ref(h.x), std::ref(h.xl));
    insTable[0x76] = { [this]() { halted = true; return 4; } };
    INSBIND(0x77, MOVMr, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0x78, MOVr1r2, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0x79, MOVr1r2, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0x7a, MOVr1r2, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0x7b, MOVr1r2, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0x7c, MOVr1r2, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0x7d, MOVr1r2, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0x7e, MOVMr, std::ref(h.x), std::ref(b.xl));
    INSBIND(0x7f, MOVr1r2, std::ref(psw.xl), std::ref(psw.xl));

    // OpCodes 0x80 -> 0x8f
    INSBIND(0x80, ADDr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0x81, ADDr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0x82, ADDr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0x83, ADDr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0x84, ADDr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0x85, ADDr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0x86, ADDM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0x87, ADDr, std::ref(psw.xl), std::ref(psw.xl));
    INSBIND(0x88, ADCr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0x89, ADCr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0x8a, ADCr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0x8b, ADCr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0x8c, ADCr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0x8d, ADCr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0x8e, ADCM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0x8f, ADCr, std::ref(psw.xl), std::ref(psw.xl));

    // OpCodes 0x90 -> 0x9f
    INSBIND(0x90, SUBr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0x91, SUBr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0x92, SUBr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0x93, SUBr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0x94, SUBr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0x95, SUBr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0x96, SUBM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0x97, SUBr, std::ref(psw.xl), std::ref(psw.xl));
    INSBIND(0x98, SBBr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0x99, SBBr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0x9a, SBBr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0x9b, SBBr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0x9c, SBBr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0x9d, SBBr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0x9e, SBBM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0x9f, SBBr, std::ref(psw.xl), std::ref(psw.xl));

    // OpCodes 0xa0 -> 0xaf
    INSBIND(0xa0, ANAr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0xa1, ANAr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0xa2, ANAr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0Xa3, ANAr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0xa4, ANAr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0xa5, ANAr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0xa6, ANAM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0xa7, ANAr, std::ref(psw.xl), std::ref(psw.xl));
    INSBIND(0xa8, XRAr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0xa9, XRAr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0xaa, XRAr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0xab, XRAr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0xac, XRAr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0xad, XRAr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0xae, XRAM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0xaf, XRAr, std::ref(psw.xl), std::ref(psw.xl));

    // OpCodes 0xb0 -> 0xbf
    INSBIND(0xb0, ORAr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0xb1, ORAr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0xb2, ORAr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0xb3, ORAr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0xb4, ORAr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0xb5, ORAr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0xb6, ORAM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0xb7, ORAr, std::ref(psw.xl), std::ref(psw.xl));
    INSBIND(0xb8, CMPr, std::ref(psw.xl), std::ref(b.xh));
    INSBIND(0xb9, CMPr, std::ref(psw.xl), std::ref(b.xl));
    INSBIND(0xba, CMPr, std::ref(psw.xl), std::ref(d.xh));
    INSBIND(0xbb, CMPr, std::ref(psw.xl), std::ref(d.xl));
    INSBIND(0xbc, CMPr, std::ref(psw.xl), std::ref(h.xh));
    INSBIND(0xbd, CMPr, std::ref(psw.xl), std::ref(h.xl));
    INSBIND(0xbe, CMPM, std::ref(h.x), std::ref(psw.xl));
    INSBIND(0xbf, CMPr, std::ref(psw.xl), std::ref(psw.xl));

    // OpCodes 0xc0 -> 0xcf
    insTable[0xc0] = { [this]() { return (retZero()) ? 5 : RET(pc, sp); } };
    INSBIND(0xc1, POP, std::ref(sp), std::ref(b.x));
    insTable[0xc2] = { [this]() { return (retZero()) ? 5 : JMP(pc); } };
    INSBIND(0xc3, JMP, std::ref(pc));
    insTable[0xc4] = { [this]() { return (retZero()) ? 5 : CALL(pc, sp); } };
    INSBIND(0xc5, PUSH, std::ref(sp), std::ref(b.x));
    INSBIND(0xc6, ADI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xc7, RST, std::ref(pc), std::ref(sp), 0);
    insTable[0xc8] = { [this]() { return (retZero()) ? RET(pc, sp) : 5; } };
    INSBIND(0xc9, RET, std::ref(pc), std::ref(sp));
    insTable[0xca] = { [this]() { return (retZero()) ? JMP(pc) : 5; } };
    INSBIND(0xcb, JMP, std::ref(pc));
    insTable[0xcc] = { [this]() { return (retZero()) ? CALL(pc, sp) : 5; } };
    INSBIND(0xcd, CALL, std::ref(pc), std::ref(sp));
    INSBIND(0xce, ACI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xcf, RST, std::ref(pc), std::ref(sp), 1);

    // OpCodes 0xd0 -> 0xdf
    insTable[0xd0] = { [this]() { return (retCarry()) ? 5 : RET(pc, sp); } };
    INSBIND(0xd1, POP, std::ref(sp), std::ref(d.x));
    insTable[0xd2] = { [this]() { return (retCarry()) ? 5 : JMP(pc); } };
    INSBIND(0xd3, OUT, std::ref(pc), std::ref(psw.xl));
    insTable[0xd4] = { [this]() { return (retCarry()) ? 5 : CALL(pc, sp); } };
    INSBIND(0xd5, PUSH, std::ref(sp), std::ref(d.x));
    INSBIND(0xd6, SUI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xd7, RST, std::ref(pc), std::ref(sp), 2);
    insTable[0xd8] = { [this]() { return (retCarry()) ? RET(pc, sp) : 5; } };
    INSBIND(0xd9, RET, std::ref(pc), std::ref(sp));
    insTable[0xda] = { [this]() { return (retCarry()) ? JMP(pc) : 5; } };
    INSBIND(0xdb, IN, std::ref(pc), std::ref(psw.xl));
    insTable[0xdc] = { [this]() { return (retCarry()) ? CALL(pc, sp) : 5; } };
    INSBIND(0xdd, CALL, std::ref(pc), std::ref(sp));
    INSBIND(0xde, SBI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xdf, RST, std::ref(pc), std::ref(sp), 3);

    // OpCodes 0xe0 -> 0xef
    insTable[0xe0] = { [this]() { return (retParity()) ? 5 : RET(pc, sp); } };
    INSBIND(0xe1, POP, std::ref(sp), std::ref(h.x));
    insTable[0xe2] = { [this]() { return (retParity()) ? 5 : JMP(pc); } };
    INSBIND(0xe3, XTHL, std::ref(sp), std::ref(h.x));
    insTable[0xe4] = { [this]() { return (retParity()) ? 5 : CALL(pc, sp); } };
    INSBIND(0xe5, PUSH, std::ref(sp), std::ref(h.x));
    INSBIND(0xe6, ANI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xe7, RST, std::ref(pc), std::ref(sp), 4);
    insTable[0xe8] = { [this]() { return (retParity()) ? RET(pc, sp) : 5; } };
    INSBIND(0xe9, PCHL, std::ref(pc), std::ref(h.x));
    insTable[0xea] = { [this]() { return (retParity()) ? JMP(pc) : 5; } };
    INSBIND(0xeb, XCHG, std::ref(h.x), std::ref(d.x));
    insTable[0xec] = { [this]() { return (retParity()) ? CALL(pc, sp) : 5; } };
    INSBIND(0xed, CALL, std::ref(pc), std::ref(sp));
    INSBIND(0xee, XRI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xef, RST, std::ref(pc), std::ref(sp), 5);

    // OpCodes 0xf0 -> 0xff
    insTable[0xf0] = { [this]() { return (retSign()) ? 5 : RET(pc, sp); } };
    INSBIND(0xf1, POP, std::ref(sp), std::ref(psw.x));
    insTable[0xf2] = { [this]() { return (retSign()) ? 5 : JMP(pc); } };
    insTable[0xf3] = { [this]() { intEn = false; return 4; } };
    insTable[0xf4] = { [this]() { return (retSign()) ? 5 : CALL(pc, sp); } };
    INSBIND(0xf5, PUSH, std::ref(sp), std::ref(psw.x));
    INSBIND(0xf6, ORI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xf7, RST, std::ref(pc), std::ref(sp), 6);
    insTable[0xf8] = { [this]() { return (retSign()) ? RET(pc, sp) : 5; } };
    INSBIND(0xf9, SPHL, std::ref(sp), std::ref(h.x));
    insTable[0xfa] = { [this]() { return (retSign()) ? JMP(pc) : 5; } };
    insTable[0xfb] = { [this]() { intEn = true; return 4; } };
    insTable[0xfc] = { [this]() { return (retSign()) ? CALL(pc, sp) : 5; } };
    INSBIND(0xfd, CALL, std::ref(pc), std::ref(sp));
    INSBIND(0xfe, CPI, std::ref(pc), std::ref(psw.xl));
    INSBIND(0xff, RST, std::ref(pc), std::ref(sp), 7);
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

// reset - Reset CPU Emulation
// Arguments: none
void i8080::cpu::reset() {
    psw.x = 0;

    b.x = d.x = h.x = 0;

    pc = sp = 0;
}

// execute - Execute Function
// Arguments: none
void i8080::cpu::execute() {
    if ((intEn & mobo.intEn) && mobo.interrupts.size() > 0) {
        while(mobo.interrupts.size() > 0) {
            mobo.cycles += insTable[mobo.interrupts.front()]();
            mobo.interrupts.pop();
        }
    } else {
        u8 ins = mobo.rByte(pc); pc++;
        mobo.cycles += insTable[ins]();
    }
}