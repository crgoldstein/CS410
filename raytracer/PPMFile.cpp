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

PPMFile::PPMFile(string FileName){
	filename =FileName;
}
void PPMFile::write(vector<vector<ColorTriple> > FileColor){
	cout<<" write this to file these are just Red values  "<<endl;
	 for(int x =0; x<FileColor.size(); x++){
		    	for(int y=0; y<FileColor[0].size(); y++){
		    		cout<<FileColor[x][y].getRed()<<" ";
		    	}
		    	cout<<endl;
		}



	  ofstream file(filename);
	  if (file.is_open())
	  {
		  file << "P3\n"
			   << FileColor[0].size() << " "<< FileColor.size() << " 255\n";

	    for(int x =0; x<FileColor.size(); x++){
	    	for(int y=0; y<FileColor[0].size(); y++){
	    			file<<FileColor[x][y].getRed()<<" "<< FileColor[x][y].getGreen()<<" "<< FileColor[x][y].getBlue() <<" ";
	    		}
	    			file<<"\n";
	    	}
	    file.close();
	  }


}

PPMFile::~PPMFile() {
	// TODO Auto-generated destructor stub
}

