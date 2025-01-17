all: Lab1

CXX = g++

LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3

Lab1: main.o
	$(CXX) $(LINKFLAGS) lab1.o -o Lab1

main.o: lab1.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" lab1.cpp -c



clean:
	rm -rf *.o *.gch Lab1






