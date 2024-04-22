// ==============================================================
// main.cpp | Mainboard Source File
// ==============================================================

// Main Include
#include "i8080.h"

// Includes
#include <cstdio>
#include <string>
#include <thread>
#include <chrono>
#include <iomanip>
#include <iostream>

#include <boost/program_options.hpp>

// Mainboard Definitions

// Externs
i8080::cpu i8080::processor;
i8080::mainboard i8080::mobo;

// Helper Functions

std::string toHex(i8080::u8 val) {
    std::stringstream ss;
    ss << std::hex << std::setw(5) << std::setfill('0') << val;
    return ss.str();
}

// Main Definition

int main(int argc, char* argv[]) {
    i8080::ui ui;

    ui.start();

    return 0;
}