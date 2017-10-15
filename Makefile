CPP_FLAGS := -I/. -m64


all:
	g++ $(CPP_FLAGS) fibonacci.cpp  -o fib
