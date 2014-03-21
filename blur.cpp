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
    I2->height = I2->height;

    I2->image = (unsigned char *) malloc(total);

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
        // copy to buffer here since this represents the row
        for (int x=0; x<w; i++) {
            bufx[x+2] = in[y*w+x];
        }

        for (int x=2; x<w-2; x++) {
            // for each row in the buffer, average the image and store in tmp_out.



            out[x] = (in[x-2] + in[x-1] + in[x] + in[x+1] + in[x+2]) / 5;
            sum += (in[x+3] - in[x-2]);
        }
    }


    // evaluate by column
    for (int j=0; i<h; j++) {
        for (int y=2; y<h-2; y++) {
            // do stuff here
        }
    }





    // first, scan the image horizontally and store output in temp buffer.





}
