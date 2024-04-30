CC = gcc
CXX = g++
CXXFLAGS = -lstdc++ -std=gnu++23 -O2
LDLIBS = -lftxui-dom -lftxui-screen -lboost_program_options
BIN=i8080

SOURCEDIR = src
BUILDDIR = build

SRC=$(wildcard $(SOURCEDIR)/*.cpp)
OBJ=$(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

all: dir build clean

dir:
	mkdir -p $(BUILDDIR)

build: $(OBJ)
	$(CXX) $(OBJ) $(LDLIBS) -o $(BIN)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILDDIR)