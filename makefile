TARGET=main
CPP_SRC=$(wildcard ./test/*.cpp ./*.cpp ./src/*.cpp)

.PHONY:default
default:
	g++ -std=c++11 -g ${CPP_SRC} -o ${TARGET}  -I./test -I./src

.PHONY:clean
clean:
	rm -rf ${TARGET}