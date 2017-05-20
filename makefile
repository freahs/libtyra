LIB_NAME=libtyra.a

INC_DIR=inc
SRC_DIR=src
OBJ_DIR=obj
LIB_DIR=lib
BUILD_DIR = ./build

CXX_FLAGS = -fdiagnostics-color=always -std=c++11 -O3 -Wfatal-errors -Wall -Wextra -pedantic -Wconversion -Wshadow


CPP = $(wildcard src/*.cpp)
OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(LIB_NAME)
	cd test && $(MAKE)

$(LIB_NAME) : $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/$(LIB_NAME) : $(OBJ)
	@mkdir -p $(@D)
	llvm-ar rcs $(LIB_DIR)/$(LIB_NAME) $^

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -MMD -c $< -o $@


.PHONY : clean

clean:
	-rm -fr $(LIB_DIR)/$(LIB_NAME) $(OBJ) $(DEP)
	cd test && $(MAKE) clean
