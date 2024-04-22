#ifndef I8080_UI_H
#define I8080_UI_H

// ==============================================================
// ui.h | User Interface Header
// ==============================================================

// Main Include
#include "i8080.h"

// Includes
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

// Namespace Extension
namespace i8080 {
    class ui;
}

class i8080::ui {
private:
    void render();

    ftxui::Screen scr;
    std::string rstPos;

    //void clear();
public:
    ui();
    ~ui();

    u16 memOffset = 0;

    void start();
};

#endif