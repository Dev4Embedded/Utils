#Makefile for example apk

CC = gcc

EXAMPLE_DIR = example

EXAMPLES = $(EXAMPLE_DIR)/example.c
OBJECTIVES += $(EXAMPLE_DIR)/examples.o

examples: $(EXAMPLES)
	@echo "Building target: $@"
	$(CC) -I"$(INC_DIR)" -c $< -o $(EXAMPLE_DIR)/$@.o
	@echo "done."