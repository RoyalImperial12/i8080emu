// ==============================================================
// ui.cpp | User Interface Source File
// ==============================================================

// Main Include
#include "i8080.h"

// Include
#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>

// UI Constructor
i8080::ui::ui() : scr(ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Full())) {
    
}

// UI Destructor
i8080::ui::~ui() {

}

// Helper Functions
ftxui::Element getState() {
    ftxui::Element doc;
    std::vector<ftxui::Element> elements;

    (i8080::processor.getHalted()) ? elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Green, ftxui::text("Halted")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15))) : elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Red, ftxui::text("Halted")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15)));

    (i8080::mobo.interrupts.size() > 0) ? elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Green, ftxui::text("Interrupt")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15))) : elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Red, ftxui::text("Interrupt")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15)));

    doc = ftxui::vbox(ftxui::text("Emulation State"), ftxui::separator(), ftxui::hbox(std::move(elements))) | ftxui::border;

    elements.clear();

    return doc;
}

ftxui::Element getMem(i8080::u16 memOffset) {
    ftxui::Element doc;
    std::vector<ftxui::Element> elements;

    std::stringstream ss;

    elements.push_back(ftxui::hbox(ftxui::text("xxxx 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f")));

    for (unsigned int i = 0; i < 1024; i += 16) {
        ss.str("");
        for (unsigned int x = 0; x < 0x10; x++) {
            ss << std::format("{:02x}", i8080::mobo.rByte(memOffset + i + x)) << " ";
        }
        if (i8080::processor.retPC() - (memOffset + i) <= 0xf) {
            elements.push_back(ftxui::hbox(ftxui::text(std::format("{:04x} ", memOffset + i)), ftxui::color(ftxui::Color::GrayLight, ftxui::text(ss.str()))));
        } else {
            elements.push_back(ftxui::hbox(ftxui::text(std::format("{:04x} ", memOffset + i)), ftxui::color(ftxui::Color::GrayDark, ftxui::text(ss.str()))));
        }
    }

    ss.str("");

    doc = ftxui::vbox(ftxui::text("Memory"), ftxui::separator(), std::move(elements)) | ftxui::border;

    elements.clear();

    return doc;
}

ftxui::Element getRegisters() {
    ftxui::Element doc;
    std::vector<ftxui::Element> elements;

    elements.push_back(ftxui::hbox(ftxui::text("PSW") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5), ftxui::color(ftxui::Color::GrayDark, ftxui::text(std::format("{:04x}", i8080::processor.retPSW().x)))));
    elements.push_back(ftxui::hbox(ftxui::text("BC") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5), ftxui::color(ftxui::Color::GrayDark, ftxui::text(std::format("{:04x}", i8080::processor.retReg(I8080_REG_BC).x)))));
    elements.push_back(ftxui::hbox(ftxui::text("DE") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5), ftxui::color(ftxui::Color::GrayDark, ftxui::text(std::format("{:04x}", i8080::processor.retReg(I8080_REG_DE).x)))));
    elements.push_back(ftxui::hbox(ftxui::text("HL") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5), ftxui::color(ftxui::Color::GrayDark, ftxui::text(std::format("{:04x}", i8080::processor.retReg(I8080_REG_HL).x)))));
    elements.push_back(ftxui::hbox(ftxui::text("PC") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5), ftxui::color(ftxui::Color::GrayDark, ftxui::text(std::format("{:04x}", i8080::processor.retPC())))));
    elements.push_back(ftxui::hbox(ftxui::text("SP") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 5), ftxui::color(ftxui::Color::GrayDark, ftxui::text(std::format("{:04x}", i8080::processor.retSP())))));

    doc = ftxui::vbox(ftxui::text("Registers"), ftxui::separator(), std::move(elements)) | ftxui::border;

    elements.clear();

    return doc;
}

ftxui::Element getPorts() {
    ftxui::Element doc;
    std::vector<ftxui::Element> elements;

    std::stringstream ss;

    elements.push_back(ftxui::hbox(ftxui::text("xx x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb xc xd xe xf")));

    for (int x = 0; x <= 0xff; x += 16) {
        ss.str("");
        for (int y = 0; y < 0x10; y++) {
            ss << std::format("{:02x}", i8080::mobo.rPrt(x + y)) << " ";
        }

        elements.push_back(ftxui::hbox(ftxui::text(std::format("{:01x}x ", (x & 0xf0) >> 8)), ftxui::color(ftxui::Color::GrayDark, ftxui::text(ss.str()))));
    }

    ss.str("");

    doc = ftxui::vbox(ftxui::text("Ports"), ftxui::separator(), std::move(elements)) | ftxui::border;

    return doc;
}

// render - Renders UI
// arguments: none

void i8080::ui::render() {
    uint16_t block = processor.retPC() / 0x200;

    ftxui::Element doc = ftxui::vbox(std::move(getState()), ftxui::hbox(std::move(getMem(block * 0x200)), std::move(getRegisters()), std::move(getPorts())) | ftxui::flex);

    ftxui::Render(scr, doc);

    scr.Print();
}

// start - Starts Emulation
// arguments: none

void i8080::ui::start() {
    auto nextTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);

    while (true) {
        render();
        if (mobo.getMode() == I8080_CLOCK_STEP) {
            std::string c;
            std::cin >> c;
            if (c == "e" || c == "exit" || c == "q" || c == "quit") {
                return;
            } else if (c == "f" || c == "freerun") {
                mobo.freerun();
                nextTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
            } else if (c == "r" || c == "reset") {
                i8080::processor.reset();
            } else if (c == "s" || c == "step") {
                processor.execute();
            } else { }
        } else {
            while (true) {
                if (mobo.cycles < I8080_CYCLES) {
                    processor.execute();
                } else {
                    if (std::chrono::high_resolution_clock::now() >= nextTime) {
                        nextTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
                        mobo.cycles = 0;
                        break;
                    }
                }
            }
        }
        system("clear");
    }
}