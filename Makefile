# Robin Kalia
# robinkalia@berkeley.edu
# UC Berkeley
#
# pThreads: Trying out multithreading using pthreads
# Makefile: Contains the instructions to make the pthreads executable


CC = gcc
CXX = g++
EXEC = mlt


all : $(EXEC)
# Compilation flags:
# -O3   turns on optimization
# -g    enables debugging support
# -Wall turns on all compiler warnings
CXXFLAGS = -O3 -g -std=c++11 -Wall 

# Linking flags: Link to the static and run-time libraries
LFLAGS = -lm

# Object files: List of object files needed to build the program.
OBJECTS = MultiThreadingLib.o main.o


# Linking rule:
$(EXEC): $(OBJECTS)
	$(CXX) -c $(CXXFLAGS) MultiThreadingLib.cpp main.cpp -pthread
	$(CXX) $^ $(LFLAGS) -o $@ 


# Clean-up rule:
clean:
	rm -f $(EXEC) *.o *~ \#*


