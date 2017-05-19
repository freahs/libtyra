
INC_DIR=../inc
BIN_DIR=../bin
LIB_DIR=../lib

CXX = clang++
CXX_FLAGS = -fdiagnostics-color=always -std=c++11 -O3 -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow

BUILD_DIR = ./build

CPP = $(wildcard *_test.cpp)
BIN = $(CPP:%.cpp=$(BIN_DIR)/%)
DEP = $(OBJ:%.o=%.d)

all: $(BIN)

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) $^ -c -o $@ 

$(BIN_DIR)/% : main.o $(BUILD_DIR)/%.o
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -L $(LIB_DIR) $^ -ltyra -o $@

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -MMD -c $< -o $@


.PHONY : clean

clean:
	-rm $(BIN) $(DEP)

print-%  : ; @echo $* = $($*)
