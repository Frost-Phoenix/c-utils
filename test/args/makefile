CSTD = c11
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CSTD = gnu11
endif

CC := gcc
CFLAGS := -std=$(CSTD) -Wall -Wextra # -Werror
LIBS   = -lraylib
DEBUG_FLAGS := -fsanitize=address,undefined

BIN_DIR := ./bin

TARGET := main

.PHONY: all debug clean

all: $(BIN_DIR)
	gcc main.c ../../args/args.c -o $(BIN_DIR)/$(TARGET) -I ../../args/ $(CFLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(BIN_DIR)/$(TARGET)

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/$(TARGET)
	rm -rf bin
