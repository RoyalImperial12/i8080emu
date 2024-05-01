# Intel 8080 Emulator #
An emulator for the Intel 8080, written in C++. Rewritten from my original project, now found at i8080_o.

Currently only supports Linux.

## Build ##
Requires:
- GCC `>=` 11
- FTXUI
- C++ 23
- Boost Program Options

Clone the repository and build using the given makefile.<br>
`git clone https://github.com/RoyalImperial12/i8080emu.git; cd i8080emu; make`

## Usage ##
Acquire Intel 8080 binary files and trail their path after the application in the command line.
<br>e.g. `./i8080 ROMs/invaders.h` or `./i8080 ROMs/invaders.h ROMs/invaders.g ROMs/invaders.f ROMs/invaders.e`
<br>Additional Commands can be attained from running `./i8080 -h` or `./i8080 --help`

<br>Commands:
<br>The following commands can be entered into std::cin when looking at the UI. Multiple versions of the same command are separated by spaces.
<br>`e exit q quit` - Quits the emulator when stepping, freerunning currently doesn't exit gracefully, you'll have to kill it.
<br>`f freerun` - Changes mode to freerun.
<br>`r reset` - Reset the CPU Emulation.
<br>`s step` - Step forward one instruction.
