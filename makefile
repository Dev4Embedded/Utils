###########################################################
# autor: 	Stanislaw Pietrzak							  #
# email: 	integralzerox@gmail.com						  #
# gitHub:	https://github.com/Dev4Embedded/			  #
###########################################################

CC = gcc
OUTPUT_NAME = "Utils_Example"
OUTPUT_PATH = ./Release/
RM := rm -rf

#include makefile for example application
-include example/makefile
#include makefile for source code
-include src/makefile

all: test

test: sources examples
	@echo 'Building target: $@'
	$(CC) $(OBJECTIVES) -o $(OUTPUT_PATH)$(OUTPUT_NAME)
	@echo 'done.'
	
clean:
	@echo 'Clening $(OUTPUT_NAME) executable file'
	$(RM) $(OUTPUT_PATH)$(OUTPUT_NAME) 
	@echo 'Cleaning objectives'
	$(RM) $(OBJECTIVES)
	@echo 'done.'