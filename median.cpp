/**
 * Image Processing
 * Brian Wu
 * median filter
 * Usage: sharpen in sz avg_nbrs out
 */
#include "IP.h"
using namespace std;

void median(imageP, int, int, imageP);

int main(int argc, char** argv) {
    
    int sz, avg_nbrs;
    imageP I1, I2;

    cout << "in      : " << argv[1] << endl;
    cout << "sz      : " << argv[2] << endl;
    cout << "avg_nbrs: " << argv[3] << endl;
    cout << "out     : " << argv[4] << endl;
    
    I1 = IP_readImage(argv[1]);
    sz = atoi(argv[2]);
    avg_nbrs = atoi(argv[3]);

    I2 = NEWIMAGE;

    median(I1, sz, avg_nbrs, I2);

    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);

}

void median(imageP I1, int sz, int avg_nbrs, imageP I2) {
}
