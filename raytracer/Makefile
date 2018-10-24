CC = g++ 
CFLAGS = -Wall -c -O3 -I ./eigen-eigen-b9cd8366d4e8
LFLAGS = -Wall 

OBJS = main.o Transforms.o objFile.o CameraModel.o AmbientLight.o LightSource.o point.o Face.o Materials.o Ray.o ColorTriple.o PPMFile.o Sphere.o

HFILES = Transforms.h objFile.h CameraModel.h  AmbientLight.h LightSource.h point.h Face.h Materials.h Ray.h ColorTriple.h PPMFile.h Sphere.h

CfILES = Transforms.cpp objFile.cpp CameraModel.cpp  AmbientLight.cpp LightSource.cpp point.cpp Face.cpp Materials.cpp Ray.cpp ColorTriple.cpp PPMFile.cpp Sphere.cpp



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

point.o: point.cpp  point.h  
	$(CC) point.cpp $(CFLAGS)  
	
Face.o: Face.cpp  Face.h  
	$(CC) Face.cpp $(CFLAGS)  

Materials.o: Materials.cpp  Materials.h  
	$(CC) Materials.cpp $(CFLAGS) 

Ray.o: Ray.cpp  Ray.h  
	$(CC) Ray.cpp $(CFLAGS) 
	
ColorTriple.o: ColorTriple.cpp  ColorTriple.h  
	$(CC) ColorTriple.cpp $(CFLAGS) 

PPMFile.o: PPMFile.cpp  PPMFile.h  
	$(CC) PPMFile.cpp $(CFLAGS) 

Sphere.o: Sphere.cpp  Sphere.h  
	$(CC) Sphere.cpp $(CFLAGS) 

clean: 
	-rm *.o raytracer

package: 
	tar -cvf Goldstein-Claire-P2.tar main.cpp $(HFILES) $(CFILES)  Makefile README.md eigen-eigen-b9cd8366d4e8


