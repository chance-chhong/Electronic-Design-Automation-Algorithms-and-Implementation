all: Lab2

CXX = g++

LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3

Lab2: Lab2.o
	$(CXX) $(LINKFLAGS) Lab2.o -o Lab2

Lab2.o: Lab2.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" Lab2.cpp -c



clean:
	rm -rf *.o *.gch Lab2






