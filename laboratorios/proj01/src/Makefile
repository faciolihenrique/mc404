##########################################################
# Description: Template to build the makefile for
#   "trab01".
#
# Author: Edson Borin - edson@ic.unicamp.br
#
# 1) You may add more files to your project changing the
#    OBJ_FILES list.
#
# 2) You may remove or add new rules to compile your .c files
#    (see as an example rules main.o and error.o)
#
# 3) You may not change the ias-as rule (do not add
#    extra libraries!)
#
##########################################################

# List of object files that must be linked together to
# build the ias-as executable
OBJ_FILES=main.o error.o hash.o memorymap.o analyze.o applicators.o assembler.o

# Default rule
all: ias-as

# -- Rules for making each one of the .o files --
analyze.o: analyze.c analyze.h hash.h error.h
	gcc -std=c99 -c -g analyze.c -o analyze.o

# -- applicators.o depends on applicators.c applicators.h hash.h error.h memorymap.h and analyze.h
applicators.o: applicators.c applicators.h hash.h error.h memorymap.h analyze.h
	gcc -std=c99 -c -g applicators.c -o applicators.o

# -- assembler.o depends on assembler.c assembler.h hash.h error.h memorymap.h and analyze.h
assembler.o: assembler.c assembler.h hash.h error.h memorymap.h analyze.h
	gcc -std=c99 -c -g assembler.c -o assembler.o

# -- error.o depends on error.c and on error.h
error.o: error.c error.h
	gcc -c -g error.c -o error.o

# -- hash.o depends on hash.c and on hash.h
hash.o: hash.c hash.h
	gcc -std=c99 -c -g hash.c -o hash.o

# -- main.o depends on main.c , assembler.h and on hash.h
main.o: main.c assembler.h hash.h
	gcc -std=c99 -c -g main.c -o main.o

# -- memorymap depends on memorymap.c and on memorymap.h
memorymap.o: memorymap.c memorymap.h
	gcc -std=c99 -c -g memorymap.c -o memorymap.o

# -- Clean rule. It removes the ias-as file and any .o file on the directory --
clean:
	rm -f ias-as *.o

##########################################################
# Do not change this rule
##########################################################

# -- Rule to make the executable ias-as
ias-as: $(OBJ_FILES)
	gcc -std=c99 -g $(OBJ_FILES) -o ias-as
