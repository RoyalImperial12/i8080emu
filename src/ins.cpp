// ==============================================================
// ins.cpp | Instructions Source File
// ==============================================================

// Main Include
#include "i8080.h"

// MOV - Move to Register from Register (or Indirect)
int i8080::MOVr1r2(u8& ddd, u8& sss) {
    ddd = sss;

    return 5; // 5 Cycles
}

int i8080::MOVMr(u16& M, u8& ddd) {
    ddd = mobo.rByte(M);

    return 7;
}

int i8080::MOVrM(u16& M, u8& sss) {
    mobo.wByte(M, sss);

    return 7;
}

// SPHL - Set SP to HL
int i8080::SPHL(u16& SP, u16& HL) {
    SP = HL;

    return 5;
}

// MVI - Move to Register with Immediate
int i8080::MVIrd(u16& PC, u8& ddd) {
    ddd = mobo.rByte(PC);
    PC++;

    return 7;
}

int i8080::MVIMd(u16& M, u16& PC) {
    mobo.wByte(M, mobo.rByte(PC));
    PC++;

    return 10;
}

// LXI - Load Register Pair with Immediate
int i8080::LXI(u16& PC, u16& dd) {
    dd = mobo.rWord(PC);
    PC += 2;

    return 10;
}

// LDA - Load Direct to Accumulator
int i8080::LDA(u16& PC, u8& A) {
    A = mobo.rByte(mobo.rWord(PC));
    PC += 2;

    return 13;
}

// STA - Store from Accumulator
int i8080::STA(u16& PC, u8& A) {
    mobo.wByte(mobo.rWord(PC), A);
    PC += 2;

    return 13;
}

// LHLD - Load HL from Memory
int i8080::LHLD(u16& PC, u16& HL) {
    HL = mobo.rWord(mobo.rWord(PC));
    PC += 2;

    return 16;
}

// SHLD - Store HL to Memory
int i8080::SHLD(u16& PC, u16& HL) {
    mobo.wWord(mobo.rWord(PC), HL);
    PC += 2;

    return 16;
}