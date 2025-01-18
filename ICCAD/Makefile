all: cadb0016_alpha

CXX = g++

LINKFLAGS = -std=c++11 -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3

cadb0016_alpha: cadb0016_alpha.o
	$(CXX) $(LINKFLAGS) cadb0016_alpha.o -o cadb0016_alpha

cadb0016_alpha.o: cadb0016_alpha.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" cadb0016_alpha.cpp -c



clean:
	rm -rf *.o *.gch netlistTop.aux netlistTop.nodes netlistTop.nets netlistTop.pl netlistTop.scl netlistTop.wts netlistTop.gp.pl netlistTop.gp.plt netlistTop.lg.pl netlistTop.lg.plt netlistTop.ntup.pl netlistTop.ntup.plt netlistBot.aux netlistBot.nodes netlistBot.nets netlistBot.pl netlistBot.scl netlistBot.wts netlistBot.gp.pl netlistBot.gp.plt netlistBot.lg.pl netlistBot.lg.plt netlistBot.ntup.pl netlistBot.ntup.plt






