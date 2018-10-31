README.txt
------------

CS410 Assignment 3:
---------------------

	This is the starting point for a full ray-tracing program. This project reads 3D camera specifications and one or more 3D objects defined in a driver file along with light source specifications and material properties of the objects. Thus rendering a colorful scene. This project only has the illumination model that has the ability to render polygons , spheres, ambient, diffuse and specular reflection and shadows.


How To Run:
------------

To compile:
   	make

To clean:
	make clean

To run:
    	./raytracer <Driver File>.txt  <New File Name>.ppm

For example:
    	./raytracer driver00.txt driver00.ppm



File list:
------------

|-- Transforms.h & Transforms.cpp		Construction of Rotation, Scale, Translate matrix 
|-- objFile.h & objFile.cpp 			Getters and Setting for the .obj file, Makes a list of Face Objects that correspond to the Faces of the Obj File 
|-- CameraModel.h & CameraModel.cpp		Sets up camera Model and has all main functions for Raytracing including Run(), Ray Cast ,and Color Pixel
|-- AmbientLight.h & AmbientLight.cpp		Holds information about Ambient Light red green and blue	
|-- LightSource.h & LightSource.cpp		Holds information about Light position and red green and blue values 
|-- point.h & point.cpp				Holds the  X Y Z numbers for a point in space and contains the ability to become a vector
|-- Face.h & Face.cpp				Holds 3 points A B and C that make up one face of the Object. Also calculates the normal of that face
|-- Materials.h & Materials.cpp 		Reads the MTL file and holds the Ka , Kd, and Ks lighting coefficients  
|-- Ray.h & Ray.cpp				Holds a Point and a Direction
|-- ColorTriple.h & ColorTriple.cpp		Converts the 0-1 range to 0 - 255 Range for the RBG image
|-- PPMFile.h & PPMFile.cpp			Writes out the 2D Vector of ColorTriple’s to the PPM format
|-- Sphere & Sphere.h				Sphere Lays out Lighting and position for the sphere objects 
|-- main.cpp					Reads in Argument line and
|-- eigen-eigen-b9cd8366d4e8			Directory that holds the linear algebra library. 
|-- Makefile					MakeFile
|-- README.txt					This File



