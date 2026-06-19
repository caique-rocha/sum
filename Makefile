CXX = g++

# No Linux, basta usar a flag -fopenmp nativa do g++
CXXFLAGS = -g -Wall -O3 -march=native -funroll-loops -fopenmp

# Não precisamos de caminhos extras de biblioteca (-L), apenas do -fopenmp no link
LDFLAGS = -fopenmp

all: sum

sum: main.cc sum.cc
	$(CXX) $(CXXFLAGS) -o sum main.cc sum.cc $(LDFLAGS)

clean:
	rm -f sum *.o
