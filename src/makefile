#Makefile for source codes

CC = gcc

INC_DIR = inc
SRC_DIR = src

SRCS = $(SRC_DIR)/utils.c
OBJECTIVES += $(SRC_DIR)/sources.o 

sources: $(SRCS) 
	@echo "Building target: $@"
	$(CC) -I"$(INC_DIR)" -c $< -o $(SRC_DIR)/$@.o
	@echo "done."