CXX = g++

# Adicionamos -Xpreprocessor e o caminho (-I) para ele achar o 'omp.h'
CXXFLAGS = -g -Wall -O3 -march=native -funroll-loops -Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include

# Adicionamos o caminho (-L) para ele achar a biblioteca compilada (libomp)
LDFLAGS = -L/usr/local/opt/libomp/lib -lomp

all: sum

sum: main.cc sum.cc
	$(CXX) $(CXXFLAGS) -o sum main.cc sum.cc $(LDFLAGS)