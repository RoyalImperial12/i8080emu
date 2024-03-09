#ifndef I8080_INS_H
#define I8080_INS_H

// ==============================================================
// ins.h | Instruction Header
// ==============================================================

// Main Include
#include "i8080.h"

// Namespace Extension
namespace i8080 {
    u8 MOVr1r2(u8&, u8&); /// ddd, sss
    u8 MOVrM(u16&, u8&); /// M, ddd
    u8 MOVMr(u16&, u8&); /// M, sss

    u8 SPHL(u16&, u16&); // SP, HL

    u8 MVIrd(u16&, u8&); // PC, ddd
    u8 MVIMd(u16&, u16&); // M, PC

    u8 LXI(u16&, u16&); // PC, dd

    u8 LDA(u16&, u8&); // PC, A

    u8 STA(u16&, u8&);// PC, A

    u8 LHLD(u16&, u16&); // PC, HL

    u8 SHLD(u16&, u16&); // PC, HL

    u8 LDAX(u16&, u8&); // rp, A

    u8 STAX(u16&, u8&); // rp, A

    u8 XCHG(u16&, u16&); // HL, DE

    u8 ADDr(u8&, u8&); // A, sss
    u8 ADDM(u16&, u8&); // M, A

    u8 ADI(u16&, u8&); // PC, A

    u8 ADCr(u8&, u8&); // A, sss
    u8 ADCM(u16&, u8&); // M, A

    u8 ACI(u16&, u8&); // PC, A

    u8 SUBr(u8&, u8&); // A, sss
    u8 SUBM(u16&, u8&); // M, A

    u8 SUI(u16&, u8&); // PC, A

    u8 SBBr(u8&, u8&); // A, sss
    u8 SBBM(u16&, u8&); // M, A

    u8 SBI(u16&, u8&); // PC, A

    u8 INRr(u8&); // ddd
    u8 INRM(u16&); // M

    u8 DCRr(u8&); // ddd
    u8 DCRM(u16&); // M

    u8 INX(u16&); // rp

    u8 DCX(u16&); // rp

    u8 DAD(u16&, u16&); // HL, rp

    u8 DAA(u8&); // A

    u8 ANAr(u8&, u8&); // A, sss
    u8 ANAM(u16&, u8&); // M, A

    u8 ANI(u16&, u8&); // PC, A

    u8 XRAr(u8&, u8&); // A, sss
    u8 XRAM(u16&, u8&); // M, A

    u8 XRI(u16&, u8&); // PC, A

    u8 ORAr(u8&, u8&); // A, sss
    u8 ORAM(u16&, u8&); // M, A

    u8 ORI(u16&, u8&); // PC, A

    u8 CMPr(u8&, u8&); // A, sss
    u8 CMPM(u16&, u8&); // M, A

    u8 CPI(u16&, u8&); // PC, A

    u8 RLC(u8&); // A

    u8 RRC(u8&); // A

    u8 RAL(u8&); // A

    u8 RAR(u8&); // A

    u8 CMA(u8&); // A

    u8 CMC();

    u8 STC();

    u8 JMP(u16&); // PC

    u8 CALL(u16&, u16&); // PC, SP

    u8 RET(u16&, u16&); // PC, SP

    u8 RST(u16&, u16&, u8); // PC, SP, nnn

    u8 PCHL(u16&, u16&); // PC, HL

    u8 PUSH(u16&, u16&); // SP, rp

    u8 POP(u16&, u16&); // SP, rp

    u8 XTHL(u16&, u16&); // SP, HL

    u8 IN(u16&, u8&); // PC, A

    u8 OUT(u16&, u8&); // PC, A
}

#endif