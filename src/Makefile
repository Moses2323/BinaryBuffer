# for windows mingw32-make

CXX=g++
CXXFLAGS=-std=c++14 -O3 -Wall -pedantic
CXXFLAGSDBG=-std=c++14 -O0 -g -Wall -pedantic
LIBS=
SRCS=$(wildcard *.cpp)
TRG=..\build\bin\BinaryBuffer.exe
DPNDS=$(wildcard *.h *.hpp *.hxx *.tcc)

all: $(TRG) 

$(TRG): $(SRCS) $(DPNDS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@  $(LIBS)
	
debug: $(SRCS) $(DPNDS)
	$(CXX) $(CXXFLAGSDBG) $(SRCS) -o $(TRG)  $(LIBS)

clean:
	-del "$(TRG)"
	echo Clean done