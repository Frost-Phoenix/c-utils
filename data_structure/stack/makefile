SRC_DIR := ./src
INCLUDE_DIR := ./include
BIN_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

TEST_SRC_DIR := ./test
TEST_BIN_DIR := ./test/bin
TEST_SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_BIN_DIR)/%.o, $(TEST_SRC_FILES))

CSTD = c99

CC := gcc
CFLAGS := -std=$(CSTD) -Wall -Wextra -Werror -Wpedantic
LIBS := 
TEST_LIBS := -lcriterion
DEBUG_FLAGS := -fsanitize=address,undefined
RELEASE_FLAGS := -O2

TARGET := stack
TEST_TARGET := test_stack

.PHONY: all test debug release clean

all: $(BIN_DIR)/$(TARGET)

# Build rule
$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $^ -o $@ $(LIBS)

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

test: $(TEST_BIN_DIR)/$(TEST_TARGET)
	$(TEST_BIN_DIR)/$(TEST_TARGET)

$(TEST_BIN_DIR)/$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES) | $(TEST_BIN_DIR)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $^ -o $@ $(TEST_LIBS)

$(TEST_BIN_DIR)/%.o: $(TEST_SRC_DIR)/%.c | $(TEST_BIN_DIR)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(BIN_DIR)/$(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: clean $(BIN_DIR)/$(TARGET)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(TEST_BIN_DIR)
