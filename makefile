CC = gcc
CXX = g++
CXXFLAGS = -lstdc++ -std=gnu++23
BIN=i8080

SOURCEDIR = src
BUILDDIR = build

SRC=$(wildcard $(SOURCEDIR)/*.cpp)
OBJ=$(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

all: dir build clean

dir:
	mkdir -p $(BUILDDIR)

build: $(OBJ)
	$(CXX) $(OBJ) -o $(BIN)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILDDIR)