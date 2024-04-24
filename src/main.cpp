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
#include <fstream>

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
    boost::program_options::positional_options_description p;
    p.add("load", -1);

    boost::program_options::options_description desc("Options");

    desc.add_options()
        ("help,h", "Prints this help message.")
        ("load,l", boost::program_options::value<std::vector<std::string>>(), "File input")
        ("mirror,m", boost::program_options::value<i8080::u16>(), "Mirrors Memory (emulates a restricted memory space)")
        ("stack,s", boost::program_options::value<i8080::u16>(), "Define stack top")
        ("freerun,f", "Sets emulation right into freerunning mode");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;

        return 0;
    }

    if (vm.count("stack")) {
        i8080::mobo.spOffset = vm["stack"].as<i8080::u16>();
    }

        if (vm.count("mirror")) {
        i8080::mobo.mAddr = vm["mirror"].as<i8080::u16>();
    }

    i8080::mobo.mAddr--;

    if (vm.count("load")) {
        i8080::u16 memOffset = 0x0;

        for (std::string string : vm["load"].as<std::vector<std::string>>()) {
            std::cout << string << std::endl;
            std::ifstream f(string, std::ios::binary);

            if (!f) {
                continue;
            }

            f.unsetf(std::ios::skipws);

            std::vector<char> data;
            f.seekg(0, f.end);
            std::streampos length = f.tellg();
            f.seekg(0, f.beg);

            data.reserve(length);

            data.insert(data.begin(), std::istream_iterator<i8080::u8>(f), std::istream_iterator<i8080::u8>());

            f.close();

            for (i8080::u8 byte : data) {
                i8080::mobo.wByte(memOffset, byte);
                memOffset++;
            }
        }
    }

    if (vm.count("freerun")) {
        i8080::mobo.freerun();
    }

    i8080::ui ui;

    ui.start();

    return 0;
}