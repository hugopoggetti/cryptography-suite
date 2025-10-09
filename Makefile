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
LIB_SRC_DIR := src/aes/aes_src
LIB_OBJ_DIR := $(LIB_SRC_DIR)/obj
LIB_SRC := $(wildcard $(LIB_SRC_DIR)/*.c)
LIB_OBJ := $(patsubst $(LIB_SRC_DIR)/%.c,$(LIB_OBJ_DIR)/%.o,$(LIB_SRC))
CC=clang
LIB = ./lib/libcipher.so
LIB_DIR = lib
CFLAGS += -g3 -Wall -Wextra -Wconversion -Wshadow\
		  -Wpointer-arith -Wcast-align -Wuninitialized -Wpedantic

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(PYTHON_SRC) $(LIB)
	@echo '#!/bin/python3'> $(TARGET)
	@echo 'from src.parser import parser' >> $(TARGET)
	@echo 'from src.cipher_manager import cipher_manager' >> $(TARGET)
	@tail -n +5  $(MAIN_SRC) >> $(TARGET)
	@chmod +x $(TARGET)

lib:$(LIB)
$(LIB): $(LIB_OBJ) | libdir
	$(CC) -shared $(CFLAGS) -o $@ $^
$(LIB_OBJ_DIR)/%.o: $(LIB_SRC_DIR)/%.c | $(LIB_OBJ_DIR)
	$(CC) -fPIC -c $(CFLAGS) $< -o $@
$(LIB_OBJ_DIR):
	mkdir -p $(LIB_OBJ_DIR)

libdir:
	mkdir -p $(LIB_DIR)

tests_run:
	make -s
	find test -type d -exec touch {}/__init__.py \;
	python -m unittest discover -s test -p "*_test.py"

clean:
	rm -rf $(TARGET)
	rm -rf $(LIB)
	rm -rf $(LIB_OBJ_DIR)
	rm -rf $(LIB_DIR)

fclean:
	make clean
	find . -type d -name "__pycache__" -exec rm -r {} +

re:
	make fclean
	make
