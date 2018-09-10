CC = g++ 
CFLAGS = -Wall -c -g -I /Users/clairegoldstein/eclipse-workspace/CS410/modeltoworld/eigen-eigen-b9cd8366d4e8
LFLAGS = -Wall 
OBJS = main.o Transforms.o

all: modeltoworld

modeltoworld: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o modeltoworld

# compiling 
main.o: main.cpp Transforms.h 
	$(CC) main.cpp $(CFLAGS)  

Transforms.o: Transforms.cpp  Transforms.h  
	$(CC) Transforms.cpp $(CFLAGS)  
	
clean: 
	-rm *.o modeltoworld
	