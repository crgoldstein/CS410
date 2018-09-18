CC = g++ 
CFLAGS = -Wall -c -g -I ./eigen-eigen-b9cd8366d4e8
LFLAGS = -Wall 
OBJS = main.o Transforms.o objFile.o

all: modeltoworld

modeltoworld: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o modeltoworld

# compiling 
main.o: main.cpp Transforms.h objFile.h
	$(CC) main.cpp $(CFLAGS)  

Transforms.o: Transforms.cpp  Transforms.h  
	$(CC) Transforms.cpp $(CFLAGS)  

objFile.o: objFile.cpp  objFile.h  
	$(CC) objFile.cpp $(CFLAGS)  
	
clean: 
	-rm *.o modeltoworld
	