
CXX=g++

all: tree main

main: tree test.o main.o
	$(CXX) -o $@ $^

tree: tree.cpp tree/node.cpp

%.o: %.cpp
	# compile only cpp file
	$(CXX) -c -o $@ $^
