/*
 * PPMFile.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: clairegoldstein
 */

#include "PPMFile.h"

PPMFile::PPMFile() {
	// TODO Auto-generated constructor stub

}

PPMFile::PPMFile(const string FileName){
	filename =FileName;
}
void PPMFile::write( vector<vector<ColorTriple> >  &FileColor){

cout<<"Write to a File"<<endl;
	  ofstream file(filename);

	  if (file.is_open())
	  {
		  file << "P3\n"
			   << FileColor[0].size() << " "<< FileColor.size() << " 255\n";

	    for(int y =0; y<FileColor.size(); y++){
	    	for(int x=0; x<FileColor[0].size(); x++){
	    			file<<FileColor[x][y].toString();
	    		}
	    			file<<"\n";
	    	}
	    file.close();
	  }


}

PPMFile::~PPMFile() {
	// TODO Auto-generated destructor stub
}

