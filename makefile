
# build/main.o: src/main.cpp
# 	clang++ -c src/main.cpp -o build/main.o

# build/lib/Debug.o: src/lib/Debug.cpp
# 	clang++ -c src/lib/Debug.cpp -o build/lib/Debug.o


# run:build/main.o build/lib/Debug.o
# 	clang++ build/main.o build/lib/Debug.o -o my_program
# 	cd build && sudo ./main.o	
SRC_DIR := src
CPP_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES := $(patsubst %.cpp,%.obj,$(CPP_FILES))
FLAGS := -c -Isrc/include -DDEBUG -g -std=c++17
CC := clang++

build/SimpleWebServer:$(OBJ_FILES)
	clang++ $(OBJ_FILES) -o build/SimpleWebServer

run:build/SimpleWebServer
	cd build && sudo ./SimpleWebServer


%.obj: %.cpp
	$(CC) $(FLAGS) $< -o $@

clean:
	find . -type f  -name '*.obj' -delete
	rm build/SimpleWebServer