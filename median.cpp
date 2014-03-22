/**
 * Image Processing
 * Brian Wu
 * median filter
 * Usage: sharpen in sz avg_nbrs out
 */
#include "IP.h"
#include <algorithm>

static const size_t v_size = 10;

using namespace std;

void median(imageP, int, int, imageP);

int main(int argc, char** argv) {
    
    int sz, avg_nbrs;
    imageP I1, I2;
    int array[10] = {10,9,1,3,21,59,2,7,9,4};

    std::sort(array,array+10);

    for (int i=0; i<10; i++) {
        cout << array[i] << endl;
    }

    cout << "in      : " << argv[1] << endl;
    cout << "sz      : " << argv[2] << endl;
    cout << "avg_nbrs: " << argv[3] << endl;
    cout << "out     : " << argv[4] << endl;
    
    sz = atoi(argv[2]);
    avg_nbrs = atoi(argv[3]);
    
    if ((sz & 1) == 0) {
        cerr << "sz is must be an odd number." << endl;
        exit(1);
    }

    I1 = IP_readImage(argv[1]);

    I2 = NEWIMAGE;

    median(I1, sz, avg_nbrs, I2);

    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);

}

void median(imageP I1, int sz, int avg_nbrs, imageP I2) {
    
    int i, total;
    unsigned char *in, *out;

    total = I1->width * I1->height;

    I2->height = I1->height;
    I2->width = I1->width;

    I2->image = (unsigned char *) malloc(total);

    in = I1->image;
    out = I2->image;

    if (I2->image == NULL) {
        cerr << "not enough memory\n";
        exit(1);
    }

    int w = I1->width;
    int h = I1->height;

    // create buffer to that will represent the kernel buffer
    // for simplicity sake, we will assume sz = 3;
    int pad_size = (sz * 2);
    int buf_size = (w + pad_size);
    short buf[buf_size];
    

    for (int y=0; y<h; y++) {
        // copy the current row in to the buffer
        for (int x=0; x<buf_size; x++) {
            if (x <= sz) {
                // x is a pad index on the left so we must pad using pixel replication.
            } else if (x >= w) {
                // x is a pad index on the right.
            } else {
                // x is not a pad pixel.
            }
        }

        for (int x=0; x<w; x++) {



        }
    }
}

int clip(int a) {
    if (a >= 255) {
        return 255;
    } else if (a <= 0) {
        return 0;
    } else {
        return a;
    }
}
