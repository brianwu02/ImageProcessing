/**
 * Image Processing
 * Brian Wu
 * Convolve
 * Usage: convolve in kernel out
 */
#include "IP.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <sstream>

using namespace std;

void convolve(imageP, imageP, kernelP, imageP);
std::string readKernelFile(char*);
kernelP getKernel(std::string);
int cfa(char);

int main(int argc, char** argv) {
    std::string kernelString;
    std::string str;
    imageP I1, I2, paddedImg;
    kernelP k;

    // read kernel file and convert to std::string
    //kernelString = readKernelFile(argv[1]);

    // parse kernel string and return an kernelP data structure.
    //k = getKernel(kernelString);

    /*for (int i = 0; i<kernelString.length(); i++) {
        cout << kernelString[i];
    }*/

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    paddedImg = NEWIMAGE;
    k = NEWKERNEL;

    // create a dummy kernel structure of w=3, h=3.
    
    k->height = 3;
    k->width = 3;
    int ksize = k->height * k->width;
    k->kernel = (float *) malloc(4 * ksize); // stupid. have to multiply by 4 bytes. man why does c++ suck.
    float *kimg = k->kernel;
    
    // hard code some sample values
    
    // weighted average
    kimg[0] = 1;
    kimg[1] = 2;
    kimg[2] = 1;
    kimg[3] = 2;
    kimg[4] = 4;
    kimg[5] = 2;
    kimg[6] = 1;
    kimg[7] = 2;
    kimg[8] = 1;
    
    /*kimg[0] = 0;
    kimg[1] = -1;
    kimg[2] = 0;
    kimg[3] =  -1;
    kimg[4] = 5;
    kimg[5] = -1;
    kimg[6] = 0;
    kimg[7] = -1;
    kimg[8] = 0;
    */
    
    /*
    kimg[0] = -1.0;
    kimg[1] = -1.0;
    kimg[2] = -1.0;
    kimg[3] = -1.0;
    kimg[4] = 8.0;
    kimg[5] = -1.0;
    kimg[6] = -1.0;
    kimg[7] = -1.0;
    kimg[8] = -1.0;
    */

    /*
    kimg[0] = 1;
    kimg[1] = 1;
    kimg[2] = 1;
    kimg[3] = 1;
    kimg[4] = 1;
    kimg[5] = 1;
    kimg[6] = 1;
    kimg[7] = 1;
    kimg[8] = 1;
    */
    /*
    kimg[0] = -10;
    kimg[1] = -10;
    kimg[2] = -10;
    kimg[3] = 0;
    kimg[4] = 0;
    kimg[5] = 0;
    kimg[6] = 10;
    kimg[7] = 10;
    kimg[8] = 10;
    */

    /*
    kimg[0] = -10;
    kimg[1] = 0;
    kimg[2] = 10;
    kimg[3] = -10;
    kimg[4] = 0;
    kimg[5] = 10;
    kimg[6] = -10;
    kimg[7] = 0;
    kimg[8] = 10;
    */
    




    // fix the size.
    int sz = 3;
    padImage(I1, sz, paddedImg);

    convolve(I1, paddedImg, k, I2);
    IP_saveImage(I2, argv[3]);



    return 1;
}

void convolve(imageP I1, imageP paddedImg, kernelP k, imageP I2) {
    /* I1 => original Image
     * paddedImg => the pixel replicated Image
     * k => the kernel 
     * I2 => outfile
     *
     */
    int kw = k->width;
    int kh = k->height;
    int kt = k->width * k->height;

    int height = I1->height;
    int width = I1->width;
    int total = I1->width * I1->height;

    I2->height = I1->height;
    I2->width = I1->width;
    I2->image = (unsigned char *) malloc(total);

    unsigned char *in, *out, *paddedIn;
    out = I2->image;
    paddedIn = paddedImg->image;
    int paddedWidth = paddedImg->width;
    int paddedHeight = paddedImg->height;
    
    float *buf;
    float *kernelP = k->kernel;

    // do a lot of hard coded values because im tired and I just want it to work for 3*3 kernel....
    int bufRowsRequired = 3;

    // initialize buffer for kernel
    buf = (float *) malloc(paddedWidth * bufRowsRequired * 4);

    // allocate memory for an array that will hold all the pointers to circlar buffer
    float *arrayOfPointers[bufRowsRequired];

    // store points in array of pointers
    for (int i=0; i<bufRowsRequired; i++) {
        arrayOfPointers[i] = &buf[i*paddedWidth];
    }

    // initialize and store the pointers to buffer in arrayOfPointers
    for (int y=0; y<bufRowsRequired-1; y++) {
        floatCopyToBuffer(paddedImg, y, bufRowsRequired, buf);
    }
    float *r0, *r1, *r2;

    // kernelP is pointer to kernel
    int kr[9]; // temp to hold calculations

    //cout << (int) kernelP[0] << endl;

    for (int y=0; y<height; y++) {
        // copy next row to buffer
        floatCopyToBuffer(paddedImg, y+(bufRowsRequired-1), bufRowsRequired, buf);
        r0 = arrayOfPointers[y % 3] + 1;
        r1 = arrayOfPointers[(y+1) % 3] + 1;
        r2 = arrayOfPointers[(y+2) % 3] + 1;
        
        unsigned char sum;
        for (int x=0; x<width; x++) {


            kr[0] = r0[-1] * kernelP[0];
            kr[1] = r0[0] * kernelP[1];
            kr[2] = r0[1] * kernelP[2];
            kr[3] = r1[-1] * kernelP[3];
            kr[4] = r1[0] * kernelP[4];
            kr[5] = r1[1] * kernelP[5];
            kr[6] = r2[-1] * kernelP[6];
            kr[7] = r2[0] * kernelP[7];
            kr[8] = r2[1] * kernelP[8];

            //cout << (int) r1[0] << " * " << (float) kernelP[4] << " = " << r1[0] * kernelP[4] << endl;
            //cout << (int) r1[1] << " * " << (float) kernelP[5] << endl;
            
            sum = (kr[0] + kr[1] + kr[2] + kr[3] + kr[4] + kr[5] + kr[6] + kr[7] + kr[8]) / 16;
            out[y*width+x] = sum;
            r0++;
            r1++;
            r2++;

        }
    }









}

kernelP allocateKernel(int w, int h, int s) {
    float *p;
    kernelP k;

    k = (kernelP) malloc(sizeof(kernelS));
    p = (float *) malloc(w * h * s);
    if (p == NULL) {
        cerr << "allocateKernel error, Insufficient memory" << endl;
        return ((kernelP) NULL);
    }

    k->width = w;
    k->height = h;
    k->kernel = p;

    return k;

}

kernelP getKernel(std::string str) {
    kernelP k;
    int w, h;
    unsigned char *out;

    // this is dumb way of but I guess it'll work for now
    w = cfa(str[0]);
    h = cfa(str[2]);

    cout << w << endl;

    cout << h << " " << w << endl;
    //cout << str[0] << "" << str[2] << endl;


    /*if ((w != 3) and (h != 3)) {
        cerr << "im doing parsing the stupid way so h and w must be 3" << endl;
        exit(1);
    }*/

    //cout << "width is: " << str[0] << endl;
    //cout << "height is: " << str[2] << endl;

    



    //k = allocateKernel(w, h, sizeof(unsigned char));
    //out = k->kernel;
    //return (kernelP) k;
    return 0;
}



std:: string readKernelFile(char *file) {
    std::string filename = file;
    std::string str;
    std::ifstream t(filename);

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

    return str;

}



int cfa(char str) {
    // dumb way to parse. convert ASCII char to INT.

    if (str == 48) { return 0; }
    else if (str == 49) { return 1; }
    else if (str == 50) { return 2; }
    else if (str == 51) { return 3; } 
    else if (str == 52) { return 4; }
    else if (str == 53) { return 5; }
    else if (str == 54) { return 6; }
    else if (str == 55) { return 7; }
    else if (str == 56) { return 8; }
    else if (str == 57) { return 9; }


    
    
    else {
        cerr << "error parsing" << endl;
        return str;
    }
}


