CXX=clang++
CXXFLAGS=-std=c++17 -O3

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.o 

hello-world.o: hello-world.cpp
	$(CXX) $(CXXFLAGS) hello-world.cpp -o hello-world.o