 
// ================================================================
// IPutil.cpp - Read/Save PGM files.
//
// Copyright (C) 2014 by George Wolberg
//
// Written by: George Wolberg, 2014
// ================================================================

#include "IP.h"

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// IP_readImage:
//
// Read image from file. The image is in PGM format.
//
imageP
IP_readImage(char *file) 
{

	imageP	 I;
	int	 w, h, maxGray;
   	char  	 buf[1024];
	uchar	*out;

	// open binary file for reading
	ifstream inFile (file, ios::binary);
	
	// error checking
	if(!inFile) {
		cerr << "readImage: Can't open " << file << endl;
		exit(1);
	}

   	// verify that the image is in PGM format. 
   	inFile.getline(buf, 3);
   	if(strncmp(buf,"P5",2) && strncmp(buf,"P6",2)){
      		cerr << "The file " << file << " is not in PGM format" << endl;
      		inFile.close();
      		exit(1);
   	}

	// read width, height, and maximum gray value
	inFile >> w >> h >> maxGray;

	// skip over linefeed and carriage return
	inFile.getline(buf, 2);

	// allocate image and read file
	I = IP_allocImage(w, h, sizeof(uchar));
	out = I->image;
	inFile.read((char *) out, w*h);

	return (imageP) I;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// IP_saveImage:
//
// Save image I to file in PGM format.
//
void 
IP_saveImage(imageP I, char *file)
{

	uchar	*out;

	// open binary file for writing
	ofstream outFile(file, ios::binary);

	// error checking
	if (!outFile) {
		cerr << "IP_savePGM: Can't open " << file << endl;
		exit(1);
	}

	// save PGM header
	outFile <<"P5" << endl;
	outFile <<I->width<< " " << I->height << endl;
	outFile << "255" << endl;

	// save image data
	out = I->image;
	outFile.write((char *) out, I->width*I->height);
	outFile.close();

}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// IP_allocImage:
//
// Allocate space for an image of width w and height h.
// Each pixel in the image has size s (in bytes).
// Return image structure pointer. 
//
imageP
IP_allocImage(int w, int h, int s)
{
	uchar	*p;
	imageP	 I;

	// allocate memory
	I = (imageP ) malloc(sizeof(imageS));
	p = (uchar *) malloc(w * h * s);
	if(p == NULL) {
		cerr << "IP_allocImage: Insufficient memory\n";
		return ((imageP) NULL);
	}

	// init structure
	I->width  = w;
	I->height = h;
	I->image  = p;

	return(I);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// IP_freeImage:
//
// Free space of image I.
//
void
IP_freeImage(imageP I)
{
	free((char *) I->image);
	free((char *) I);
}
