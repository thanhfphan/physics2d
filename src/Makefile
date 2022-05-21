CC = g++ 
LANG_STD= -std=c++11
COMPILER_FLAGS = -Wall
SRC_FILES = *.cpp
INCLUDE_PATH = -I/opt/homebrew/include
LINKER_FLAGS = -L/opt/homebrew/lib -lSDL2 
OBJ_NAME = main.out

build:
	${CC} $(LANG_STD) $(COMPILER_FLAGS) $(SRC_FILES) $(INCLUDE_PATH) $(LINKER_FLAGS) -o $(OBJ_NAME)
debug:
	${CC} -g $(LANG_STD) $(COMPILER_FLAGS) $(SRC_FILES) $(INCLUDE_PATH) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)