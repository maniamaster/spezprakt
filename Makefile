.PHONY: clean doc ./test/runner.cpp

CC=gcc
CPPC=g++
CXXFLAGS=-std=gnu++14 

OUTPUT=bin/test

SRCDIR=./src/
HDRDIR=./hdr/
OBJDIR=./bin/obj/

CPPSRC= basis.cpp hamiltonian.cpp
CPPHDR= $(CPPSRC:.cpp=.hpp)
CPPOBJ= $(addprefix $(OBJDIR), $(CPPSRC:.cpp=.cpp.o))

CSRC= utilities.c# sparse_matrix.c
COBJ= $(addprefix $(OBJDIR), $(CSRC:.c=.c.o))

IFLAGS+= -I/usr/include/lapacke/ -I/usr/include/ -I/usr/scratch1/mschmitt/boost-numeric-bindings/
IFLAGS+= -I/usr/include/ -I./hdr/ -I/usr/scratch1/mschmitt/armadillo-6.400.3/include/ 
OPTFLAGS= -O3 #-march=native -ffast-math -funroll-loops

default: $(CPPOBJ) $(COBJ)
	$(CPPC) $(CXXFLAGS) -o $(OUTPUT) src/main.cpp $(CPPOBJ) $(COBJ) $(LFLAGS) $(IFLAGS) $(OPTFLAGS)

./bin/obj/%.c.o: ./src/%.c ./hdr/%.h
	$(CC) -o $@ -c $< $(OPTFLAGS) $(IFLAGS)

./bin/obj/%.cpp.o: ./src/%.cpp ./hdr/%.hpp
	$(CPPC) -o $@ -c $< $(OPTFLAGS) $(IFLAGS)

./bin/obj/my_lapack_wrappers.cpp.o: ./src/my_lapack_wrappers.cpp ./hdr/my_lapack_wrappers.h
	$(CPPC) $(CXXFLAGS) -o $@ -c $< $(IFLAGS) -I/usr/include/lapacke $(OPTFLAGS) $(DEFS)

./src/%.cpp:

./hdr/%.h:

clean:
	rm $(CPPOBJ) $(COBJ)