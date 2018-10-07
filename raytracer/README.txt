README
======

Assignment 1:
	Polygonal models exist for lots and lots of objects. To make a coherent scene, however, you need to be able to read and write models to disk, along with applying manipulations to them. For example, translating, rotating, and scaling them. In this assignment you will take existing polygonal models (in .OBJ format) and apply some 3D transformations to them. In particular, you will be using Axis-Angle Rotation specifications to rotate the model about a given axis, followed by scaling it uniformly along three axes, followed by a translation along three axes. A 'driver' (scene file) - read as an argument by your program - will contain pairs of 3D transformations and object model names to be transformed.


This package includes the following files.

|-- Transforms.h
|-- Transforms.cpp
|-- objFile.h
|-- objFile.cpp
|-- main.cpp
|-- eigen-eigen-b9cd8366d4e8
|-- Makefile
|-- README.txt

Transforms.h & Transforms.cpp: 
	construction of Rotation, Scale , Translate matrix 

objFile.h & objFile.cpp :
	Getters and Setting for the .obj file
	also writes a new file 

eigen-eigen-b9cd8366d4e8 :
	Directory that holds the linear algebra library. 


To compile:
   make clean
   make

To run:
    ./modletoworld <driver file>

For example;
    ./modletoworld driver00.txt

