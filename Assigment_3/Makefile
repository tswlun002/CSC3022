#This is a Makefile 
CC=g++                  #the compiler name
CCFLAGS=-std=c++2a      #flags passed to compiler
TARGET=findcomp        #executable file
OBJECT= *.o             #binary file(s) 
SOURCE= *.cpp           #cc++ file(s)

#linking rules
$(TARGET): $(OBJECT)
	$(CC)	$(OBJECT)	-o	$(TARGET)	$(CCFLAGS)

#building rule
$(OBJECT): $(SOURCE)
	$(CC)	-c	$(SOURCE)	$(CCFLAGS)

#execution rule 
run:
	./findcomp

#clean rule     
clean:
	@rm	-f	*.o 
	@rm	-f	extractor
