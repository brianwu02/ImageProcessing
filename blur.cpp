/**
 * Image Processing
 * Brian Error
 * Blur
 * Usage: blur in xsz ysz out
 */
#include "IP.h"

using namespace std;

void blur(imageP, imageP, int, int, imageP);

int main(int argc, char** argv) {
    int xsz, ysz;
    imageP I1, I2, tmp_img;

    I1 = IP_readImage(argv[1]);

    xsz = atoi(argv[2]);
    ysz = atoi(argv[3]);

    
    // bitwise operator to check if xsz & ysz are odd.
    if  (((xsz & 1 ) == 0) or ((ysz & 1) == 0)) {
        // xsz or ysz are even.
        cout << "xsz: " << xsz << endl;
        cout << "ysz: " << ysz << endl;
        cerr << "either xsz or ysz is not odd" << endl;
        exit(1);
    }

    I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;

    blur(I1, tmp_img, xsz, ysz, I2);

    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);

    cout << "done" << endl;
    return 1;
}

void blur(imageP I1, imageP tmp_img, int xsz, int ysz, imageP I2) {

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
    
    // first, scan the image horizontally and store output in temp buffer.
    



}
