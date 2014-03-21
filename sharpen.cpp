/** 
 * Image Processing
 * Brian Wu
 * Usage sharpen in sz fctr out
 */
#include "IP.h"

using namespace std;

void blur(imageP, imageP, int, int, imageP);
void sharpen(imageP, int, int, imageP);

int main(int argc, char** argv) {

    int sz, fctr;
    imageP I1, I2, tmp_img;
    
    cout << "in   : " << argv[1] << endl;
    cout << "sz   : " << argv[2] << endl;
    cout << "fctr : " << argv[3] << endl;
    cout << "out  : " << argv[4] << endl;


    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;

    if ((sz & 1) == 0) {
        cout << "sz: " << sz << "is not odd" << endl;
        exit(1);
    }

    sz = atoi(argv[2]);
    fctr = atoi(argv[3]);

    blur(I1, tmp_img, sz, sz, I2);

    IP_saveImage(I2, argv[4]);
    
    IP_freeImage(I1);
    IP_freeImage(I2);
    IP_freeImage(tmp_img);


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
    
    for (int y=0; y<h; y++) {
        for (int x=0; x<bufx_size; x++) {
            if (x < s) {
                bufx[x] = in[y*w+(x+s)];
            } else if (x >= w) {
                bufx[x] = in[y*w+(x-s)];
            } else {
                bufx[x] = in[y*w+x];
            }
        }

        int sum = 0;
        for (int i=0; i<(s*2 + 1); i++) {
            sum += bufx[i];
        }
        for (int x=0; x<w; x++) {
            tmp[y*w+x] = sum / (s*2+1);
            sum += (bufx[x+(s*2+1)] - bufx[x]);
        }
    }

    for (int x=0; x<w; x++) {
        for (int y=0; y<bufy_size; y++) {
            if (y < t) {
                bufy[y] = tmp[(y+t)*w+x];
            } else if (y >= h) {
                bufy[y] = tmp[(y-(t*2)) * w+x];
            } else {
                bufy[y] = tmp[y*w+x];
            }
        }

        int sum = 0;
        for (int i=0; i<(t*2 + 1); i++) {
            sum += bufy[i];
        }

        for (int y=0; y<h; y++) {
            out[y*w+x] = sum / (t*2+1);
            sum += (bufy[y+(t*2+1)] - bufy[y]);
        }
    }

}
