# Makefile for CSEP
# 2014-10-31 14:00:17

CXX = g++
CXXFLAGS = -pipe -O3 -Wextra -W -ansi -pedantic -pedantic-errors -Wmissing-braces -Wparentheses -std=c++14
CXXFLAGS += -Wall -Wold-style-cast -Wzero-as-null-pointer-constant
LDFLAGS = -static -static-libgcc -static-libstdc++

all: csep

csep: csep.o
	$(CXX) $(LDFLAGS) -o $@ $<

csep.o: csep.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f csep.o
	rm -f csep.exe
