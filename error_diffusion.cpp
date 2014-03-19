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
    threshold = 256 / 2;
    
    // create circular buffer. this one here is only 2 'widths' long.

    int h = I1->height;
    int w = I1->width;

    // mtd=0; manually copy row 0 to the circular buffer. Floyd-Steinberg Algorithm
    if (mtd == 0) {
        short buf[1][w+2];

        // pad the buffer
        buf[0][0] = 0;
        buf[0][(w+2) -1] = 0;
        buf[1][0] = 0;
        buf[1][(w+2) -1] = 0;

        for (int i = 0; i < w; i++) {
            buf[0][i+1] = in[i];
        }
        
        for (int y=0; y<h; y++) {
            // manually copy row 1 in to the circular buffer.
            if ((y % 2) == 0) {
                // if y is even, copy to buf[1]
                for (int i = 0; i < w; i++) {
                    buf[1][i+1] = in[y*w+i];
                }
            } else {
                // if y is odd, copy to buf[0]
                for (int i = 0; i < w; i++) {
                    buf[0][i+1] = in[y*w+i];
                }
            }
            
            int p = 1;
            for (int x=0; x<w; x++) {
                //*out = (buf[0][p] < threshold) ? 0 : 255;
                *out = (buf[0][p] < threshold) ? 0 : 255;
                //*out = (*in1 < threshold) ? 0 : 255;
                //cout << (int) buf[0][p] << endl;
                short e = (buf[0][p] - *out);
                //cout << (int) e << endl;

                buf[0][p+1] += (e*7/16.0); // error to E 
                buf[1][p-1] += (e*3/16.0); // error to SW
                buf[1][p] += (e*5/16.0);   // error to S
                buf[1][p+1] += (e*1/16.0); // error to SE
                
                p++;
                out++;
            }
        }
    } else {
        short buf[2][w+4];

        // pad the buffer, 2 deep.
        buf[0][0] = 0;
        buf[0][1] = 0;
        buf[0][(w+4) -1] = 0;
        buf[0][(w+4) -2] = 0;

        buf[1][0] = 0;
        buf[1][1] = 0;
        buf[1][(w+4) -1] = 0;
        buf[1][(w+4) -2] = 0;

        buf[2][0] = 0;
        buf[2][1] = 0;
        buf[2][(w+4) -1] = 0;
        buf[2][(w+4) -2] = 0;

        // mtd=1; for Jarvis-Judice-Ninke Error diffusion algorithm, need buffers.
        for (int i = 0; i < w; i++) {
            buf[0][i+2] = in[i];
            buf[1][i+2] = in[i+w];
        }
        // circular buffer logic.
        for (int y=0; y<h; y++) {
            if ((y % 3) == 0) {
                for (int i = 0; i < w; i++) {
                    buf[2][i+2] = in[y*w+i];
                }
            }
            if ((y % 3) == 1) {
                for (int i = 0; i < w; i++) {
                   buf[0][i+2] = in[y*w+i];
                   cout << buf[0][i+2] << endl;
                }
            }
            if ((y % 3) == 2) {
                for (int i = 0; i < w; i++) {
                    buf[1][i+2] = in[y*w+i];
                }
            }
            int p = 2;
            for (int x=0; x<w; x++) {
                *out = (buf[0][p] < threshold) ? 0 : 255;
                //cout << (int) buf[0][p] << endl;
                short e = (buf[0][p] - *out);
                cout << (int) e << endl;

                buf[0][p+1] += (e*7/48.0);
                buf[0][p+2] += (e*5/48.0);
                buf[1][p-2] += (e*3/48.0);
                buf[1][p-1] += (e*5/48.0);
                buf[1][p] += (e*7/48.0);
                buf[1][p+1] += (e*5/48.0);
                buf[1][p+2] += (e*3/48.0);

                buf[2][p-2] += (e*1/48.0);
                buf[2][p-1] += (e*3/48.0);
                buf[2][p] += (e*5/48.0);
                buf[2][p+1] += (e*3/48.0);
                buf[2][p+2] += (e*1/48.0);

                p++;
                out++;
            }
        }
    }
}





/*
void copyRowToCircularBuffer(int y, int width, unsigned char *inArray, short *buf) {
    // copy the row to circlar buffer, yes i should be using custom data structure :/
    
    
    int row = (y * width); // keep track of the row we are in for inArray
    short *buffer = buf; // size is width * 2
    unsigned char *in = inArray; // this is pointer to input array

    // pad the buffer with 0's
    buf[0] = 1;
    buf[width-1] = 1;
    buf[width] = 1;
    buf[(width*2)-1] = 1;
    
    for (int i=1; i<width+1; i++) {
        if ((y % 2) == 0) {
            // copy to first portion of buffer
            int head = i;
            buffer[head] = in[row + i];
            } else {
            // copy to the second portion of buffer
            int head = i + width;
            buffer[head] = in[row + i];
            }
    }
    //cout << (int) in[200] << endl;
    //cout << buffer << endl;
    //cout << buffer[0] << endl;
}
*/
