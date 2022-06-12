#This is a Makefile 
CC=g++                  #the compiler name
CCFLAGS=-std=c++2a      #flags passed to compiler
TARGET= extractor        #executable file
OBJECT= *.o             #binary file(s) 
SOURCE= *.cpp           #cc++ file(s)

#linking rules
$(TARGET): $(OBJECT)
	$(CC)	$(OBJECT)	-o	$(TARGET)	$(CCFLAGS)

#building rule
$(OBJECT): $(SOURCE)
	$(CC)	-c	$(SOURCE)	$(CCFLAGS)
	#cp	/home/lunga/Desktop/CSC/CSC3022F/2022/examples/larger_image.pgm /home/lunga/Desktop/CSC/CSC3022F/2022/Assigment_2

#execution rule 
run:
	./file.exe

#clean rule     
clean:
	@rm	-f	*.o 
	@rm	-f	*.exe
	#@rm	-f	*.pgm
	#@rm	-f	*.png
	@rm	-r	GENERATED_VIDEOS