#ifndef I8080_INS_H
#define I8080_INS_H

// ==============================================================
// ins.h | Instruction Header
// ==============================================================

// Main Include
#include "i8080.h"

namespace i8080 {
    // MOV
    int MOVr1r2(u8, u8);
    int MOVrM(u8);
    int MOVMr(u8);

    //SPHL
    int SPHL();

    // MVI
    int MVIrd(u8);
    int MVIMd(u8);

    // LXI
    int LXI(u8);

    // LDA
    int LDA();

    // STA
    int STA();

    // LHLD
    int LHLD();
}

#endif