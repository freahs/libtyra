
INC_DIR=../inc
BIN_DIR=./bin
LIB_DIR=../lib
BUILD_DIR=../build/test

CXX_FLAGS = -fdiagnostics-color=always -std=c++14 -O3 -Wfatal-errors -Wall -Wextra -pedantic -Wconversion -Wshadow -pthread

CPP = $(wildcard *_test.cpp)
BIN = $(CPP:%.cpp=$(BIN_DIR)/%)
DEP = $(CPP:%.cpp=$(BUILD_DIR)/%.d)

all: $(BIN)

$(BIN_DIR)/% : $(BUILD_DIR)/main.o $(BUILD_DIR)/%.o
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -L $(LIB_DIR) $^ -ltyra -o $@

-include $(DEP)

$(BUILD_DIR)/main.o: main.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $^ -c -o $@ 

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -MMD -c $< -o $@

.PHONY : clean

clean:
	-rm -fr $(BIN) $(DEP)

print-%  : ; @echo $* = $($*)
