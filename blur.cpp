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


    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;

    blur(I1, tmp_img, xsz, ysz, I2);

    cout << "done blurring" << endl;

    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);

    cout << "done" << endl;
    return 1;
}

void blur(imageP I1, imageP tmp_img, int xsz, int ysz, imageP I2) {

    int i, total, sum;
    unsigned char *in, *out, *tmp;

    total = I1->width * I1->height;

    tmp_img->height = I1->height;
    tmp_img->width = I1->width;
    
    I2->width = I1->width;
    I2->height = I1->height;

    I2->image = (unsigned char *) malloc(total);
    tmp_img->image = (unsigned char *) malloc(total);

    out = I2->image;
    in = I1->image;
    tmp = tmp_img->image;

    if (I2->image == NULL) {
        cerr << "not enough mem\n";
        exit(1);
    }
    int w = I1->width;
    int h = I1->height;
    
    int s = (xsz - 1) / 2;
    int t = (ysz - 1) / 2;

    // fixed example for 5x5 kernel so 2 pad on left and right
    short bufx[w+4];
    short bufy[w+4];

    bufx[0] = 0;
    bufx[1] = 0;
    bufx[(w+3)] = 0;
    bufx[(w+2)] = 0;
 
    bufy[0] = 0;
    bufy[1] = 0;
    bufy[(w+3)] = 0;
    bufy[(w+2)] = 0;

    cout << s << " " << t << endl;

    // evaluate by ror
    for (int y=0; y<h; y++) {
        cout << "copying to buffer" << endl;
        // copy to buffer here since this represents the row
        for (int x=0; x<w; x++) {
            bufx[x+2] = in[y*w+x];
        }

        sum = bufx[0] + bufx[1] + bufx[2] + bufx[3] + bufx[4];
        for (int x=2; x<w-2; x++) {
            // for each row in the buffer, average the image and store in tmp_out.
            //
            tmp[y*w+x] = sum / 5;
            sum += (bufx[x+3] - bufx[x-2]);
        }
    }


    // evaluate by column
    for (int x=0; x<w; x++) {
        //copy column to buffer.
        for (int y=0; y<h; y++) {
            bufy[y+2] = tmp[y*w+x];
        }

        sum = bufy[0] + bufy[1] + bufy[2] + bufy[3] + bufy[4];
        for (int y=2; y<h-2; y++) {
            // for each column in buffer, average the image and store in out 
            out[y*w+x] = sum / 5;
            sum += (bufy[y+3] - bufy[y-2]);
        }
    }





    // first, scan the image horizontally and store output in temp buffer.





}
