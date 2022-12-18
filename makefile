CPP_SRC=$(wildcard test/*.cpp)

.PHONY:default
default:
	g++ -std=c++11 -g ${CPP_SRC} -o main -I./src -I./test