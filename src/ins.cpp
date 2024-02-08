// ==============================================================
// ins.cpp | Instructions Source File
// ==============================================================

// Main Include
#include "i8080.h"

// MOV - Move
int i8080::MOVr1r2(i8080::u8 ddd, i8080::u8 sss) {
    if (ddd == 7 && sss == 7) {
        // Do nothing, why waste cycles assigning something to itself?!
    } else if (ddd == 7) {
        processor.retPSW().xl = (sss % 2 == 1) ? processor.retReg(sss).xl : processor.retReg(sss).xh;
    } else {
        (ddd % 2 ? processor.retReg(ddd).xl : processor.retReg(ddd).xh) = (sss % 2 ? processor.retReg(sss).xl : processor.retReg(sss).xh);
    }

    return 5; // 5 Cycles
}

int i8080::MOVMr(u8 ddd) {
    (ddd % 2 ? processor.retReg(ddd).xl : processor.retReg(ddd).xh) = mobo.rByte(processor.retM());
    return 7;
}

int i8080::MOVrM(u8 sss) {
    mobo.wByte(processor.retM(), (sss % 2 ? processor.retReg(sss).xl : processor.retReg(sss).xh));
    return 7;
}

// SPHL - HL to SP
int i8080::SPHL() {
    processor.retSP() = processor.retReg(4).x;
    return 5;
}

// MVI - Move Immediate
int i8080::MVIrd(u8 ddd) {
    (ddd % 2 ? processor.retReg(ddd).xl : processor.retReg(ddd).xh) = mobo.rByte(processor.retPC());
    processor.retPC()++;
    return 7;
}

int i8080::MVIMd(u8 sss) {
    mobo.wByte(processor.retM(), mobo.rByte(processor.retPC()));
    processor.retPC()++; 
    return 10;
}

// LXI
int i8080::LXI(u8 rp) {
    processor.retReg(rp).x = mobo.rWord(processor.retPC()); 
    processor.retPC() += 2; 
    return 10;
}

// LDA
int i8080::LDA() {
    processor.retPSW().xl = mobo.rByte(processor.retPC());
    return 13;
}

// STA
int i8080::STA() {
    mobo.wByte(processor.retPC(), processor.retPSW().xl);
    return 13;
}

// LHLD
int i8080::LHLD() {
    processor.retReg(I8080_REG_H).x = mobo.rWord(processor.retPC());
    processor.retPC() += 2;
    return 16;
}