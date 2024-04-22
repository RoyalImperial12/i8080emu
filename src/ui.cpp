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
i8080::ui::ui() : scr(ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Full())), rstPos(scr.ResetPosition()) {
    
}

// UI Destructor
i8080::ui::~ui() {

}

// Helper Functions
ftxui::Element getState() {
    ftxui::Element doc;
    std::vector<ftxui::Element> elements;

    (i8080::processor.getHalted()) ? elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Green, ftxui::text("Halted")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15))) : elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Red, ftxui::text("Halted")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15)));

    (i8080::mobo.interrupt) ? elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Green, ftxui::text("Interrupt")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15))) : elements.push_back(ftxui::hbox(ftxui::color(ftxui::Color::Red, ftxui::text("Interrupt")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15)));

    doc = ftxui::vbox(ftxui::text("Emulation State"), ftxui::separator(), ftxui::hbox(std::move(elements))) | ftxui::border;

    elements.clear();

    return doc;
}

ftxui::Element getMem(i8080::u16 memOffset) {
    ftxui::Element doc;
    std::vector<ftxui::Element> elements;

    std::stringstream ss;

    for (unsigned int i = 0; i < 1000; i += 16) {
        ss.clear();
        for (unsigned int x = 0; x < 0x10; x++) {
            ss << std::format("{:02x}", i8080::mobo.rByte(memOffset + i + x)) << " ";
        }
        if (i8080::processor.retPC() - (memOffset + i) <= 0xf) {
            elements.push_back(ftxui::hbox(ftxui::text(std::format("{:04x} ", memOffset + i)), ftxui::color(ftxui::Color::GrayLight, ftxui::text(ss.str()))));
        } else {
            elements.push_back(ftxui::hbox(ftxui::text(std::format("{:04x} ", memOffset + i)), ftxui::color(ftxui::Color::GrayDark, ftxui::text(ss.str()))));
        }

        ss.str("");
    }

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

// render - Renders UI
// arguments: none

void i8080::ui::render() {
    uint16_t block = processor.retPC() / 0x200;

    ftxui::Element doc = ftxui::vbox(std::move(getState()), ftxui::hbox(std::move(getMem(block * 0x200)), std::move(getRegisters())) | ftxui::flex);

    std::cout << rstPos;
    scr.Clear();
    scr.Print();
    std::cout << rstPos;

    ftxui::Render(scr, doc);

    scr.Print();
    rstPos = scr.ResetPosition();
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
            if (c == "e" || c == "exit") {
                return;
            } else if (c == "f" || c == "freerun") {
                mobo.freerun();
                nextTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
            } else {
                processor.execute();
            }
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