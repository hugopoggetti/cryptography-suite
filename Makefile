##
## EPITECH PROJECT, 2025
## my_pgp
## File description:
## Makefile
##

PYTHON_SRC = $(wildcard src/**/*.py src/*.py)
MAIN_SRC = src/main.py
TARGET = my_pgp

# Shared Lib for aes
LIB_SRC_DIR := src/aes
LIB_OBJ_DIR := $(LIB_SRC_DIR)/obj
LIB_SRC := $(wildcard $(LIB_SRC_DIR)/*.c)
LIB_OBJ := $(patsubst $(LIB_SRC_DIR)/%.c,$(LIB_OBJ_DIR)/%.o,$(LIB_SRC))
LIB = ./lib/libcipher.so
LIB_DIR = lib
CFLAGS += -Wall -Wextra -Wconversion -Wshadow\
		  -Wpointer-arith -Wcast-align -Wuninitialized -Wpedantic

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(PYTHON_SRC) $(LIB)
	@echo '#!/bin/python3'> $(TARGET)
	@echo 'from src.parser import parser' >> $(TARGET)
	@echo 'from src.manager import manager' >> $(TARGET)
	@tail -n +5  $(MAIN_SRC) >> $(TARGET)
	@chmod +x $(TARGET)

lib:$(LIB)
$(LIB): $(LIB_OBJ) | libdir
	gcc -shared $(CFLAGS) -o $@ $^
$(LIB_OBJ_DIR)/%.o: $(LIB_SRC_DIR)/%.c | $(LIB_OBJ_DIR)
	gcc -fPIC -c $(CFLAGS) $< -o $@
$(LIB_OBJ_DIR):
	mkdir -p $(LIB_OBJ_DIR)

libdir:
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(TARGET)
	rm -rf $(LIB)
	rm -rf $(LIB_OBJ)
	rm -rf $(LIB_DIR)

fclean:
	make clean
	rm -rf src/*/*__
	rm -rf src/*__

re:
	make fclean
	make
