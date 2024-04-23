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
`git clone https://github.com/RoyalImperial12/i8080emu.git; cd i8080emu
make`

## Usage ##
Acquire Intel 8080 binary files and trail their path after the application in the command line.
<br>e.g. `./i8080 ROMs/invaders.h`
