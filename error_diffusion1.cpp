/**
 * Image Processing
 * Brian Wu
 * Error Diffusion
 * Usage: error_diffusion in mtd serpentine gamma out
 */
#include "IP.h"
#include <typeinfo>
using namespace std;

void error_diffusion(imageP, int, int, float, imageP);
//void copyRowToCircularBuffer(int, int, unsigned char *inArray, short *buf);

int main(int argc, char** argv) {
    int mtd, serpentine;
    float gamma;
    imageP I1, I2;

    cout << "input: " << argv[1] << endl;
    cout << "mtd: " << argv[2] << endl;
    cout << "serpentine: " << argv[3] << endl;
    cout << "gamma: " << argv[4] << endl;
    cout << "outfile " << argv[5] << endl;

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;

    mtd = atoi(argv[2]);
    serpentine = atoi(argv[3]);
    gamma = atof(argv[4]);


    error_diffusion(I1, mtd, serpentine, gamma, I2);

    IP_saveImage(I2, argv[5]);

    IP_freeImage(I1);
    IP_freeImage(I2);

    cout << "done!" << endl;

    return 1;
}

void error_diffusion(imageP I1, int mtd, int serpentine, float gamma, imageP I2) {
    int i, total, threshold;
    unsigned char *in;
    unsigned char *out;
    unsigned char gammaCorrectionLUT[256];
    unsigned char thresholdingLUT[256];

    total = I1->width * I1->height;
    I2->width = I1->width;
    I2->height = I1->height;

    I2->image = (unsigned char *) malloc(total);

    out = I2->image;
    in = I1->image;

    if (I2->image == NULL) {
        cerr << "Not enough memory\n";
        exit(1);
    }

    // create gamma correction lookup table
    for (i=0; i<256; i++) {
        gammaCorrectionLUT[i] = (int) (pow((double) i / 255.0, (1.0 / gamma)) * 255.0);
    }

    // gamma correct the input Image
    for (i=0; i<total; i++) {
        in[i] = gammaCorrectionLUT[in[i]];
    }

    // create thresholding scale
    threshold = 255 / 2;

    int h = I1->height;
    int w = I1->width;


    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
        }
    }


    
}



