#This is a Makefile 
CC=g++                  #the compiler name
CCFLAGS=-std=c++2a      #flags passed to compiler
TARGET=findcomp        #executable file
OBJECT= *.o             #binary file(s) 
SOURCE= ConnectedComponent.cpp  PGMimageProcessor.cpp	Driver.cpp         #cc++ file(s)
SOURCE_WITH_UNIT_TEST= ConnectedComponent.cpp  PGMimageProcessor.cpp	Tester.cpp         #cc++ file(s)


#building rule with no unit test
default:
	$(CC)	$(SOURCE)	$(CCFLAGS) -o	$(TARGET)
	

#building rule with  unit test
test:
	$(CC)	$(SOURCE_WITH_UNIT_TEST)	$(CCFLAGS)	-o	$(TARGET)


#execution rule 
run:
	./findcomp

#clean rule     
clean:
	@rm	-f	*.o 
	@rm	-f	findcomp
	@rm	-f	*.pgm
