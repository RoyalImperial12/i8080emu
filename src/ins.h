#ifndef I8080_INS_H
#define I8080_INS_H

// ==============================================================
// ins.h | Instruction Header
// ==============================================================

// Main Include
#include "i8080.h"

// Namespace Extension
namespace i8080 {
    int MOVr1r2(u8&, u8&);
    int MOVrM(u16&, u8&);
    int MOVMr(u16&, u8&);

    int SPHL(u16&, u16&);

    int MVIrd(u16&, u8&);
    int MVIMd(u16&, u16&);

    int LXI(u16&, u16&);

    int LDA(u16&, u8&);

    int STA(u16&, u8&);

    int LHLD(u16&, u16&);

    int SHLD(u16&, u16&);

    int LDAX(u8);

    int STAX(u8);

    int XCHG();

    int ADDr(u8);
    int ADDM();

    int ADI();

    int ADCr();
    int ADCM();

    int ACI();

    int SUBr(u8);
    int SUBM();

    int SUI();

    int SBBr(u8);
    int SBBM();

    int SBI();

    int INRr(u8);
    int INRM();

    int DCRr(u8);
    int DCRM(u8);

    int INX(u8);

    int DCX(u8);

    int DAD(u8);

    int DAA();

    int ANAr(u8);
    int ANAM();

    int ANI();

    int XRAr(u8);
    int XRAM();

    int XRI();

    int ORAr(u8);
    int ORAM();
}

#endif