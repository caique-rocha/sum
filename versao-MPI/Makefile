CXX = mpicxx
CXXFLAGS = -g -Wall -O3 -march=native -funroll-loops
LDFLAGS = 

all: sum

sum: main.cc sum.cc
	$(CXX) $(CXXFLAGS) -o sum main.cc sum.cc $(LDFLAGS)

clean:
	rm -f sum *.o
