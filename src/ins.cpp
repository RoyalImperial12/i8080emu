// ==============================================================
// ins.cpp | Instructions Source File
// ==============================================================

// Main Include
#include "i8080.h"

// MOV - Move
i8080::u8 i8080::MOVr1r2(u8& ddd, u8& sss) {
    ddd = sss;

    return 5; // 5 Cycles
}

i8080::u8 i8080::MOVMr(u16& M, u8& ddd) {
    ddd = mobo.rByte(M);

    return 7;
}

i8080::u8 i8080::MOVrM(u16& M, u8& sss) {
    mobo.wByte(M, sss);

    return 7;
}

// SPHL - Set SP to HL
i8080::u8 i8080::SPHL(u16& SP, u16& HL) {
    SP = HL;

    return 5;
}

// MVI - Move to Register with Immediate
i8080::u8 i8080::MVIrd(u16& PC, u8& ddd) {
    ddd = mobo.rByte(PC);
    PC++;

    return 7;
}

i8080::u8 i8080::MVIMd(u16& M, u16& PC) {
    mobo.wByte(M, mobo.rByte(PC));
    PC++;

    return 10;
}

// LXI - Load Register Pair with Immediate
i8080::u8 i8080::LXI(u16& PC, u16& dd) {
    dd = mobo.rWord(PC);
    PC += 2;

    return 10;
}

// LDA - Load Direct to Accumulator
i8080::u8 i8080::LDA(u16& PC, u8& A) {
    A = mobo.rByte(mobo.rWord(PC));
    PC += 2;

    return 13;
}

// STA - Store from Accumulator
i8080::u8 i8080::STA(u16& PC, u8& A) {
    mobo.wByte(mobo.rWord(PC), A);
    PC += 2;

    return 13;
}

// LHLD - Load HL from Memory
i8080::u8 i8080::LHLD(u16& PC, u16& HL) {
    HL = mobo.rWord(mobo.rWord(PC));
    PC += 2;

    return 16;
}

// SHLD - Store HL to Memory
i8080::u8 i8080::SHLD(u16& PC, u16& HL) {
    mobo.wWord(mobo.rWord(PC), HL);
    PC += 2;

    return 16;
}

// LDAX - Load Accumulator Indirect via BC or DE
i8080::u8 i8080::LDAX(u16& rp, u8& A) {
    A = mobo.rByte(rp);

    return 7;
}

// STAX - Store Accumulator Indirect via BC or DE
i8080::u8 i8080::STAX(u16& rp, u8& A) {
    mobo.wByte(rp, A);

    return 7;
}

// XCHG - Exchange HL and DE
i8080::u8 i8080::XCHG(u16& HL, u16& DE) {
    u16 tmp = DE;
    DE = HL;
    HL = tmp;

    return 4;
}

// ADD - Add to Accumulator
i8080::u8 i8080::ADDr(u8& A, u8& sss) {
    u8 value_a = A;

    A += sss;

    I8080_CARRY_ADD(value_a, sss);

    I8080_PARITY(A);

    I8080_ACARRY_ADD(value_a, sss);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 6;
}

i8080::u8 i8080::ADDM(u16& M, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(M);

    A += value_o;

    I8080_CARRY_ADD(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_ADD(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// ADI - Add to Accumulator with Immediate
i8080::u8 i8080::ADI(u16& PC, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(PC);
    PC++;

    A += value_o;

    I8080_CARRY_ADD(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_ADD(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// ADC - Add to Accumulator with Carry
i8080::u8 i8080::ADCr(u8& A, u8& sss) {
    u8 value_a = A;
    u8 value_o = sss + I8080_ER_CARRY;

    A += value_o;

    I8080_CARRY_ADD(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_ADD(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 6;
}

i8080::u8 i8080::ADCM(u16& M, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(M) + I8080_ER_CARRY;

    A += value_o;

    I8080_CARRY_ADD(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_ADD(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// ACI - Add to Accumulator with Immediate and Carry
i8080::u8 i8080::ACI(u16& PC, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(PC) + I8080_ER_CARRY;
    PC++;

    A += value_o;

    I8080_CARRY_ADD(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_ADD(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// SUB - Subtract from Accumulator
i8080::u8 i8080::SUBr(u8& A, u8& sss) {
    u8 value_a = A;

    A -= sss;

    I8080_CARRY_SUB(value_a, sss);

    I8080_PARITY(A);

    I8080_ACARRY_SUB(value_a, sss);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 6;
}

i8080::u8 i8080::SUBM(u16& M, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(M);

    A -= value_o;

    I8080_CARRY_SUB(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_SUB(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// SUI - Subtract from Accumulator with Immediate

i8080::u8 i8080::SUI(u16& PC, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(PC);
    PC++;

    A -= value_o;

    I8080_CARRY_SUB(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_SUB(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// SBB - Subtract from Accumulator with Borrow

i8080::u8 i8080::SBBr(u8& A, u8& sss) {
    u8 value_a = A;
    u8 value_o = sss;

    A -= value_o - I8080_ER_CARRY;

    I8080_CARRY_SUB(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_SUB(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 6;
}

i8080::u8 i8080::SBBM(u16& M, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(M);

    A -= value_o - I8080_ER_CARRY;

    I8080_CARRY_SUB(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_SUB(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// SBI - Subtract from Accumulator with Borrow and Immediate

i8080::u8 i8080::SBI(u16& PC, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(PC);
    PC++;

    A -= value_o - I8080_ER_CARRY;

    I8080_CARRY_SUB(value_a, value_o);

    I8080_PARITY(A);

    I8080_ACARRY_SUB(value_a, value_o);

    I8080_ZERO(A);

    I8080_SIGN(A);

    return 9;
}

// INR - Increment

i8080::u8 i8080::INRr(u8& ddd) {
    u8 value_o = ddd;

    ddd++;

    I8080_PARITY(ddd);

    I8080_ACARRY_ADD(value_o, 1);

    I8080_ZERO(ddd);

    I8080_SIGN(ddd);

    return 5;
}

i8080::u8 i8080::INRM(u16& M) {
    u8 value_o = mobo.rByte(M);

    mobo.wByte(M, value_o + 1);

    I8080_PARITY(value_o + 1);

    I8080_ACARRY_ADD(value_o, 1);

    I8080_ZERO(value_o + 1);

    I8080_SIGN(value_o + 1);

    return 10;
}

// DCR - Decrement

i8080::u8 i8080::DCRr(u8& ddd) {
    u8 value_o = ddd;

    ddd--;

    I8080_PARITY(ddd);

    I8080_ACARRY_SUB(value_o, 1);

    I8080_ZERO(ddd);

    I8080_SIGN(ddd);

    return 5;
}

i8080::u8 i8080::DCRM(u16& M) {
    u8 value_o = mobo.rByte(M);

    mobo.wByte(M, value_o - 1);

    I8080_PARITY(value_o - 1);

    I8080_ACARRY_SUB(value_o, 1);

    I8080_ZERO(value_o - 1);

    I8080_SIGN(value_o - 1);

    return 10;
}

// INX - Increment Register Pair

i8080::u8 i8080::INX(u16& rp) {
    rp++;

    return 5;
}

// DCX - Decrement Register Pair

i8080::u8 i8080::DCX(u16& rp) {
    rp--;

    return 5;
}

// DAD - Add Register Pair to HL

i8080::u8 i8080::DAD(u16& HL, u16& rp) {
    uint32_t value_o = HL + rp;

    HL = value_o;

    (value_o > UINT16_MAX) ? I8080_ES_CARRY : I8080_EC_CARRY;

    return 10;
}

// DAA - Decimal Adjust Accumulator

i8080::u8 i8080::DAA(u8& A) {
    u8 value_a = A;

    u8 la = A & 0xf;
    u8 ua = (A & 0xf) >> 4; 

    (la > 9 || I8080_ER_ACARRY) ? la += 6 : 0;
    (ua > 9 || I8080_ER_CARRY) ? ua += 6 : 0;

    (la > 0xf) ? I8080_ES_ACARRY : I8080_EC_ACARRY;
    (ua > 0xf) ? I8080_ES_CARRY : I8080_EC_CARRY;

    A = ((ua << 4) | (la & 0xf));

    I8080_PARITY(A);
    
    I8080_SIGN(A);

    I8080_ZERO(A);

    return 4;
}

// ANA - AND Accumulator

i8080::u8 i8080::ANAr(u8& A, u8& sss) {
    u8 value_a = A;
    u8 value_o = sss;

    A &= sss;

    I8080_EC_CARRY;
    
    ((value_a & 0x8) | (value_o & 0x8)) ? I8080_ES_ACARRY : I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 6;
}

i8080::u8 i8080::ANAM(u16& M, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(M);

    A &= value_o;

    I8080_EC_CARRY;
    
    ((value_a & 0x8) | (value_o & 0x8)) ? I8080_ES_ACARRY : I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 9;
}

// ANI - AND Accumulator with Immediate

i8080::u8 i8080::ANI(u16& PC, u8& A) {
    u8 value_a = A;
    u8 value_o = mobo.rByte(PC);
    PC++;

    A &= value_o;

    I8080_EC_CARRY;
    
    ((value_a & 0x8) | (value_o & 0x8)) ? I8080_ES_ACARRY : I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 9;
}

// XRA - XOR Accumulator

i8080::u8 i8080::XRAr(u8& A, u8& sss) {
    A ^= sss;

    I8080_EC_CARRY;

    I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 6;
}

i8080::u8 i8080::XRAM(u16& M, u8& A) {
    A ^= mobo.rByte(M);

    I8080_EC_CARRY;

    I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 9;
}

// XRI - XOR Accumulator with Immediate

i8080::u8 i8080::XRI(u16& PC, u8& A) {
    A ^= mobo.rByte(PC);
    PC++;

    I8080_EC_CARRY;

    I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 9;
}

// ORA - OR Accumulator

i8080::u8 i8080::ORAr(u8& A, u8& sss) {
    A &= sss;

    I8080_EC_CARRY;
    
    I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 6;
}

i8080::u8 i8080::ORAM(u16& M, u8& A) {
    A &= mobo.rByte(M);

    I8080_EC_CARRY;
    
    I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 9;
}

// ORI - OR Accumulator with Immediate

i8080::u8 i8080::ORI(u16& PC, u8& A) {
    A &= mobo.rByte(PC);
    PC++;

    I8080_EC_CARRY;
    
    I8080_EC_ACARRY;

    I8080_PARITY(A);

    I8080_SIGN(A);

    I8080_ZERO(A);

    return 9;
}

// CMP - Compare

i8080::u8 i8080::CMPr(u8& A, u8& sss) {
    u8 value = A - sss;

    (A < sss) ? I8080_ES_CARRY : I8080_EC_CARRY;
    (A == sss) ? I8080_ES_ZERO : I8080_EC_ZERO;

    I8080_ACARRY_SUB(A, sss);

    I8080_PARITY(value);

    return 6;
}

i8080::u8 i8080::CMPM(u16& M, u8& A) {
    u8 value_o = mobo.rByte(M);
    u8 value = A - value_o;

    (A < value_o) ? I8080_ES_CARRY : I8080_EC_CARRY;
    (A == value_o) ? I8080_ES_ZERO : I8080_EC_ZERO;

    I8080_ACARRY_SUB(A, value_o);

    I8080_PARITY(value);

    return 9;
}

// CPI - Compare with Immediate

i8080::u8 i8080::CPI(u16& PC, u8& A) {
    u8 value_o = mobo.rByte(PC);
    u8 value = A - value_o;
    PC++;

    (A < value_o) ? I8080_ES_CARRY : I8080_EC_CARRY;
    (A == value_o) ? I8080_ES_ZERO : I8080_EC_ZERO;

    I8080_ACARRY_SUB(A, value_o);

    I8080_PARITY(value);

    return 9;
}

// RLC - Rotate A Left

i8080::u8 i8080::RLC(u8& A) {
    u16 value = A << 1;

    A = value;

    (value > 255) ? I8080_ES_CARRY : I8080_EC_CARRY;

    return 6;
}

// RRC - Rotate A Right

i8080::u8 i8080::RRC(u8& A) {
    u8 value = A >> 1;

    A = value;

    ((((uint32_t)A << 2) >> 1) & 0x1) ? I8080_ES_CARRY : I8080_EC_CARRY;

    return 6;
}

// RAL - Rotate A Left with Carry

i8080::u8 i8080::RAL(u8& A) {
    u16 value = (A << 1) + I8080_ER_CARRY;

    A = value;

    (value > 255) ? I8080_ES_CARRY : I8080_EC_CARRY;

    return 6;
}

// RAR - Rotate A Right with Carry

i8080::u8 i8080::RAR(u8& A) {
    u8 value = (A >> 1) + (I8080_ER_CARRY << 7);

    A = value;

    ((((uint32_t)A << 2) >> 1) & 0x1) ? I8080_ES_CARRY : I8080_EC_CARRY;

    return 6;
}

// CMA - Complement A

i8080::u8 i8080::CMA(u8& A) {
    A = ~A;

    return 4;
}

// CMC - Complement Carry

i8080::u8 i8080::CMC() {
    (I8080_ER_CARRY) ? I8080_EC_CARRY : I8080_ES_CARRY;

    return 4;
}

// STC - Set Carry

i8080::u8 i8080::STC() {
    I8080_ES_CARRY;

    return 4;
}

// JMP - Jump to Address

i8080::u8 i8080::JMP(u16& PC) {
    PC = mobo.rWord(PC);

    return 10;
}

// CALL - Call Subroutine

i8080::u8 i8080::CALL(u16& PC, u16& SP) {
    u16 addr = mobo.rWord(PC);
    PC += 2;

    mobo.wByte(mobo.spOffset - (SP - 1), PC >> 8);
    mobo.wByte(mobo.spOffset - (SP - 2), PC & 0xff);
    SP -= 2;

    PC = addr;

    return 19;
}

// RET - Return from Subroutine

i8080::u8 i8080::RET(u16& PC, u16& SP) {
    PC = (mobo.rByte(mobo.spOffset - (SP + 1)) << 8) | mobo.rByte(mobo.spOffset - (SP));
    SP += 2;

    return 10;
}

// RST - Restart

i8080::u8 i8080::RST(u16& PC, u16& SP, u8 nnn) {
    mobo.wByte(mobo.spOffset - (SP - 1), PC >> 8);
    mobo.wByte(mobo.spOffset - (SP - 2), PC & 0xff);
    SP -= 2;

    PC = 8 * nnn;

    return 11;
}

// PCHL - Jump Indirect

i8080::u8 i8080::PCHL(u16& PC, u16& HL) {
    PC = mobo.rWord(HL) + 1;

    return 5;
}

// PUSH - Push to Stack

i8080::u8 i8080::PUSH(u16& SP, u16& rp) {
    mobo.wByte(mobo.spOffset - (SP - 1), rp  >> 8);
    mobo.wByte(mobo.spOffset - (SP - 2), rp & 0xff);
    SP -= 2;

    return 11;
}

// POP - Pop from Stack

i8080::u8 i8080::POP(u16& SP, u16& rp) {
    rp = (mobo.rByte(mobo.spOffset - (SP + 1)) << 8) | mobo.rByte(SP);
    SP += 2;

    return 10;
}

// XTHL - Exchange HL with Stack Top

i8080::u8 i8080::XTHL(u16& SP, u16& HL) {
    u16 data = (mobo.rByte(mobo.spOffset - (SP + 1)) << 8) | mobo.rByte(SP);
    
    mobo.wByte(SP, HL & 0xff);
    mobo.wByte(SP + 1, HL >> 8);

    HL = data;

    return 18;
}

// IN - In from IO Port

i8080::u8 i8080::IN(u16& PC, u8& A) {
    A = mobo.rPrt(mobo.rByte(PC));
    PC++;

    return 10;
}

// OUT - Out to IO Port

i8080::u8 i8080::OUT(u16& PC, u8& A) {
    mobo.wPrt(mobo.rByte(PC), A);
    PC++;

    return 10;
}