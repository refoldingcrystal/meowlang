CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

INCLUDE_DIRS = -I./include

SRC_DIR = ./src

BIN_DIR = ./bin
OBJ_DIR = ./obj

TARGET = $(BIN_DIR)/meow

SRCS = $(wildcard $(SRC_DIR)/*.cc)

OBJS = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean rebuild

all: $(TARGET)
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(CXXFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

rebuild: clean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@
