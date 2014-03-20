/**
 * Image Processing
 * Brian Error
 * Blur
 * Usage: blur in xsz ysz out
 */
#include "IP.h"

using namespace std;

void blur(imageP, int, int, imageP);

int main(int argc, char** argv) {
    int xsz, ysz;
    imageP I1, I2;

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;

    xsz = atoi(argv[2]);
    ysz = atoi(argv[3]);

    blur(I1, xsz, ysz, I2);

    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);

    cout << "done" << endl;
    return 1
}

void blur(imageP I1, int xsz, int ysz, imageP I2) {

    int i, total;
    unsigned char *in, *out;

    total = I1->width * I1->height;
    
    I2->width = I1->width;
    I2->height = I2->height;

    I2->image = (unsigned char *) malloc(total);

    out = I2->image;
    in = I1->image;

    if (I2->image == NULL) {
        cerr << "not enough mem\n";
        exit(1);
    }


}
