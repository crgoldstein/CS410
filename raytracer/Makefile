CC = g++ 
CFLAGS = -Wall -c -g -I ./eigen-eigen-b9cd8366d4e8
LFLAGS = -Wall 
OBJS = main.o Transforms.o objFile.o CameraModel.o AmbientLight.o LightSource.o
HFILES = Transforms.h objFile.h CameraModel.h  AmbientLight.h LightSource.h
CfILES = Transforms.cpp objFile.cpp CameraModel.cpp  AmbientLight.cpp LightSource.cpp



all: raytracer

raytracer: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o raytracer

# compiling 
main.o: main.cpp $(HFILES) 
	$(CC) main.cpp $(CFLAGS)  

Transforms.o: Transforms.cpp  Transforms.h  
	$(CC) Transforms.cpp $(CFLAGS)  

objFile.o: objFile.cpp  objFile.h  
	$(CC) objFile.cpp $(CFLAGS) 
	
CameraModel.o: CameraModel.cpp  CameraModel.h  
	$(CC) CameraModel.cpp $(CFLAGS)  	 

AmbientLight.o: AmbientLight.cpp  AmbientLight.h  
	$(CC) AmbientLight.cpp $(CFLAGS)  	

LightSource.o: LightSource.cpp  LightSource.h  
	$(CC) LightSource.cpp $(CFLAGS)  	

clean: 
	-rm *.o raytracer

package: 
	tar -cvf Goldstein-Claire-P2.tar main.cpp $(HFILES) $(CFILES)  Makefile README.md eigen-eigen-b9cd8366d4e8


