all: reduction

# modify the command to add flags for pthreads/C++11, etc.
reduction: reduction.cpp
	g++ -g $< -o $@  -std=c++11 -lpthread
.phony: clean
clean:
	rm -f reduction

