##
## EPITECH PROJECT, 2025
## my_pgp 
## File description:
## Makefile
##

PYTHON_SRC = $(wildcard src/**/*.py src/*.py)
MAIN_SRC = src/main.py
TARGET = my_pgp
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(PYTHON_SRC)
	@echo '#!/bin/python3'> $(TARGET)
	@echo 'from src.parser import parser' >> $(TARGET)
	@echo 'from src.manager import manager' >> $(TARGET)
	@tail -n +5  $(MAIN_SRC) >> $(TARGET)
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
