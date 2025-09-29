##
## EPITECH PROJECT, 2025
## my_pgp 
## File description:
## Makefile
##

PYTHON_SRC = src/main.py
BIN_DIR = ./
TARGET = my_pgp
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(PYTHON_SRC)
	@mkdir -p $(BIN_DIR)
	@echo '#!/bin/python3'> $(TARGET)
	@echo 'from src.parser import parser' >> $(TARGET)
	@tail -n +5  $(PYTHON_SRC) >> $(TARGET)
	@chmod +x $(TARGET)

clean:
	rm -rf $(TARGET)

fclean:
	make clean
	rm -rf src/*/*__
	rm -rf src/*__

re:
	make fclean
	make
