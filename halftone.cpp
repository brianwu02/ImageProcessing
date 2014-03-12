/**
 * Image Processing
 * Brian Wu
 * Halftone
 * Usage ./haltone in m gamma out
 */
#include "IP.h"
using namespace std;

void halftone(imageP, int, float, imageP);

int main(int argc, char** argv) {
    int m;
    double gamma;
    imageP I1, I2;

    cout << "argv[1] infile: " << argv[1] << endl;
    cout << "argv[2] m:      " << argv[2] << endl;
    cout << "argv[3] gamma:  " << argv[3] << endl;
    cout << "argv[4] outfile " << argv[4] << endl;

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;

    m = atoi(argv[2]);
    gamma = atof(argv[3]);

    halftone(I1, m, gamma, I2);
    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);
    
    return 1;
}

void halftone(imageP I1, int m, float gamma, imageP I2) {
    
    int i, total, new_total, scale;
    unsigned char *in, *out;
    unsigned char quant_lut[256], gamma_corrected_lut[256];

    // found at https://engineering.purdue.edu/~bouman/ece637/notes/pdf/Halftoning.pdf
    int clusterDotMatrix[8][8] = {
        {62, 57, 48, 36, 37, 49, 58, 63,},
        {56, 47, 35, 21, 22, 38, 50, 59,},
        {46, 34, 20, 10, 11, 23, 39, 51,},
        {33, 19,  9,  3,  0,  4, 12, 24,},
        {32, 18,  8,  2,  1,  5, 13, 25,},
        {45, 31, 17,  7,  6, 14, 26, 40,},
        {55, 44, 30, 16, 15, 27, 41, 52,},
        {61, 54, 43, 29, 28, 42, 53, 60}
    };

    int clusterDot[3][3] = {
        {6, 8, 4,},
        {1, 0, 3,},
        {5, 2, 7 }
    };

    int cluster[2][2] = {
        {1, 2},
        {3, 0}
    };

    total = I1->width * I1->height;

    I2->width = m * I1->width;
    I2->height = m * I1->height;

    new_total = (m * I1->width) * (m * I2->height);
    I2->image = (unsigned char *) malloc(new_total);

    //cout << (int) new_total << endl;

    out = I2->image;
    in = I1->image;

    if (I2->image == NULL) {
        cerr << "Not enough memory\n";
        exit(1);
    }

    // create gamma correction lookup table
    for (i=0; i<256; i++) {
        gamma_corrected_lut[i] = (int) (pow((double) i / 255.0, (1.0 / gamma)) * 255.0);
    }

    // gamma correct the input Image
    for (i=0; i<total; i++) {
        in[i] = gamma_corrected_lut[in[i]];
    }

    // define scale & create quantization lookup table 
    // where scale is broken up in to m grayscale values
    int n = pow(m, 2);
    scale = 256 / n;
    for (i=0; i<256; i++) {
        quant_lut[i] = (int) (scale * (i / scale)) / scale;
    }

    // visit all input pixels and apply quantization to m levels
    for (i=0; i<total; i++) {
        in[i] = quant_lut[in[i]];
    }

    int w = I1->width;
    int h = I1->height;
    int nw = I2->width;
    int nh = I2->height;
    
    // loop over the "large" pixels
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            // this loop here happens height * width times, representing the "large" pixel
            for (int j=0; j<m; j++) {
                for (int i=0; i<m; i++) {
                    
                    // THIS TOOK WAY TOO DAMN LONG TO FIGURE OUT, BUT DAMN IT FELT GOOD!
                    out[(m*y*nh) + (j*nw) + i + (m*x)] = ((in[y*w+x] > clusterDot[i][j]) ? 255 : 0);

                    // the Henry Xue Formula right here.
                    //out[(i+(m*j*m) + m*(x+m*y*w))] = ((in[y*w+x] > clusterDot[i][j]) ? 255 : 0);
                }
            }
        }
    }
}
