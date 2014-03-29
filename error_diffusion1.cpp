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

    int h = I1->height;
    int w = I1->width;

    // create buffer.
    unsigned char *buf;
    buf = (unsigned char *) malloc(2 * (w + 2)); // rows + 2 pads for each row.

    // pad with 0's
    buf[0] = 0;
    buf[w] = 0;
    buf[w+1] = 0;
    buf[2*(w+2)-1] = 0;

    int bufRowsRequired = 2;

    // create pointers to buffer.
    unsigned char *in1, *in2;

    // create array of pointers
    unsigned char *arrayOfPointers[bufRowsRequired];

    for(int i=0; i<bufRowsRequired; i++) {
        // store pointers in array.
        arrayOfPointers[i] = &buf[i*(w+2)];
    }

    // mtd = 0 -> Floyd Steinberg error Diffusion
    // mtd = 1 -> Jarvis Jundice error Diffusion
    
    threshold = 255 / 2;
    copyToBufferPadded(I1, 0, 2, buf);

    for (int y=0; y<h; y++) {
        copyToBufferPadded(I1, (y+1), 2, buf);
            in2 = arrayOfPointers[(y+1) % 2] + 1;
            in1 = arrayOfPointers[y % 2] + 1;
            if (serpentine == 1 and (y % 2) == 1) {
                for (int i=0; i<w; i++) {
                    in1++;
                    in2++;
                    out++;
                }
            }

        for (int x=0; x<w; x++) {
            if (serpentine == 0 or (serpentine == 1 and (y % 2) == 0)) {
                *out = (*in1 < threshold) ? 0 : 255;
                short e = *in1 - *out;

                in1[1] += (e*7/16.0);
                in2[-1] += (e*3/16.0);
                in2[0] += (e*5/16.0);
                in2[1] += (e*1/16.0);
                
                in1++;
                in2++;
                out++;

            } else if (serpentine == 1 and (y % 2) == 1) {
                *out = (*in1 < threshold) ? 0 : 255;
                short e = *in - *out;
                
                in1[1] += (e*7/16.0);
                in2[-1] += (e*3/16.0);
                in2[0] += (e*5/16.0);
                in2[1] += (e*1/16.0);

                in1--;
                in2--;
                out--;
                
            }
                
        }
    }


}



