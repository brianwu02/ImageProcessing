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
    kernelString = readKernelFile(argv[1]);

    // parse kernel string and return an kernelP data structure.
    //k = getKernel(kernelString);

    /*for (int i = 0; i<kernelString.length(); i++) {
        cout << kernelString[i];
    }*/

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    paddedImg = NEWIMAGE;

    // create a dummy kernel structure of w=3, h=3.
    k->height = 3;
    k->width = 3;
    k->kernel = (float *) malloc(k->width * k->height);
    int ksize = k->height * k->width;
    float *kimg = k->kernel;
    
    // hard code some sample values
    kimg[0] = .11;
    kimg[1] = .11;
    kimg[2] = .11;
    kimg[3] = .11;
    kimg[4] = .11;
    kimg[5] = .11;
    kimg[6] = .11;
    kimg[7] = .11;
    kimg[8] = .11;


    // fix the size.
    int sz = 3;
    padImage(I1, sz, paddedImg);

    convolve(I1, paddedImg, k, I2);



    return 1;
}

void convolve(imageP I1, kernelP k, imageP I2) {
    int kw = k->width;
    int kh = k->height;
    int total = I1->width * I1->height;

    I2->height = I1->height;




}

kernelP allocateKernel(int w, int h, int s) {
    unsigned char *p;
    kernelP k;

    k = (kernelP) malloc(sizeof(kernelS));
    p = (unsigned char *) malloc(w * h * s);
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


