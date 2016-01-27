LIB_NAME=libtyra.a

INC_DIR=inc
SRC_DIR=src
OBJ_DIR=obj
LIB_DIR=lib

_OBJ = world.o system.o entitymanager.o componentmanager.o systemmanager.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

#fdiagnostics requirec gcc 4.9+
CC_FLAGS=-fdiagnostics-color=always -std=c++11 -Wall -pedantic -DNDEBUG

CC=$(CXX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CC) $(CC_FLAGS) -I $(INC_DIR) -c $< -o $@

all: $(OBJ)
	ar rcs $(LIB_DIR)/$(LIB_NAME) $^

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIB_DIR)/$(LIB_NAME)
