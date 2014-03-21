/**
 * Image Processing
 * Brian Wu
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

    int bufx_size = (w + s*2);
    int bufy_size = (h + t*2);
    
    short bufx[(w + s*2)]; // s*2 is padding required.
    short bufy[(h + t*2)]; // t*2 padding required.
    
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "w: " << w << endl;
    cout << "h: " << h << endl;

    // evaluate by row
    for (int y=0; y<h; y++) {
        // copy to row to buffer for X.
        for (int x=0; x<bufx_size; x++) {
            // pad the buffer with neighboring pixels.
            if (x < s) {
                // if x is a pad pixel to the left portion of the buffer.
                bufx[x] = in[y*w+(x+s)];
            } else if (x >= w) {
                // if x is a pad pixel to the right portion of buffer.
                //cout << x << endl;
                bufx[x] = in[y*w+(x-s)];
            } else {
                bufx[x] = in[y*w+x];
            }
        }

        // dynamically calcuate sum for rows.
        int sum = 0;
        for (int i=0; i<(s*2 + 1); i++) {
            sum += bufx[i];
        }
        for (int x=0; x<w; x++) {
            // for each row in the buffer, average the image and store in tmp_out.
            tmp[y*w+x] = sum / (s*2+1);
            sum += (bufx[x+(s*2+1)] - bufx[x]);
        }
    }

    // evaluate by column
    for (int x=0; x<w; x++) {
        //copy column to buffer Y.
        for (int y=0; y<bufy_size; y++) {
            //cout << y << endl;
            if (y < t) {
                //cout << "y<t " << y << endl;
                bufy[y] = tmp[(y+t)*w+x];
            } else if (y >= h) {
                bufy[y] = tmp[(y-(t*2)) * w+x];
            } else {
                //cout << "in else : " << y << endl;
                bufy[y] = tmp[y*w+x];
            }
        }

        // dynamically calculate sum for columns.
        int sum = 0;
        for (int i=0; i<(t*2 + 1); i++) {
            sum += bufy[i];
        }

        for (int y=0; y<h; y++) {
            // for each column in buffer, average the image and store in out 
            out[y*w+x] = sum / (t*2+1);
            sum += (bufy[y+(t*2+1)] - bufy[y]);
        }
    }
}
