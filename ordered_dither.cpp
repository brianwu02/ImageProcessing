/*
 * Image Procesing
 * Ordered Dithering 
 * Brian Wu
 * 1. Quantize input image to n-levels [0...n^2]
 * 2. Create dither matrix that gives (n^2) + 1 matrices
 *  D2 =  0  2  1-d => [0 2 3 1]
 *        3  1
 *
 *  D3 =  6  8  4  1-d => [6 8 4 1 0 3 5 2 7]
 *        1  0  3
 *        5  2  7
 *
 *        0  8  2  10
 *  D4 =  12 4  14 6
 *        3  11 1  9
 *        15 7  13 5
 */
#include "IP.h"
using namespace std;

void ordered_dither(imageP, int, float, imageP, imageP, int);
int clip_values(int);
bool is_pow_of_2(int);
void create_dither_matrix(int);

int main(int argc, char** argv) {
    int n, m;
    double gamma;
    imageP	I1, I2, tmp_img;
    // read input image (I1) and reserve space for output (I2)
    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;
    
    // read m and gamma from STDIN
    m = atoi(argv[2]);
    n = pow(m, 2);

    // check if n is a power of 2
    if (n != 9) {
        if (not(is_pow_of_2(n))) {
            cerr << n << " is not a power of 2. Exiting." << endl;
            exit(1);
        }
    }
    gamma = atof(argv[3]);
    
    // threshold image and save result in file
    ordered_dither(I1, n, gamma, I2, tmp_img, m);
    IP_saveImage(I2, argv[4]);
    
    // free up image structures/memory
    IP_freeImage(I1);
    IP_freeImage(I2);
    IP_freeImage(tmp_img);
	return 1;
}

// Usage: ./ordered_dither in m gamma out
void ordered_dither(imageP I1, int n, float gamma, imageP I2, imageP tmp_img, int m) {
    
    int i, scale, total;
    uchar *in, *out, *tmp_out, lut[256];
    uchar gamma_corrected_lut[256];

    // initialize the dither matrices. I wish there were a cleaner way :/
    int dither2[2][2], dither3[3][3], dither4[4][4];

    //dither4 used to test correctness
    dither4[0][0] = 8; dither4[0][1] = 8; dither4[0][2] = 2; dither4[0][3] = 10;
    dither4[1][0] = 12; dither4[1][1] = 4; dither4[1][2] = 14; dither4[1][3] = 6;
    dither4[2][0] = 3; dither4[2][1] = 11; dither4[2][2] = 1; dither4[2][3] = 9;
    dither4[3][0] = 15; dither4[3][1] = 7; dither4[3][2] = 13; dither4[3][3] = 5;
    

    dither2[0][0] = 0; dither2[0][1] = 2;
    dither2[1][0] = 3; dither2[1][1] = 1;

    dither3[0][0] = 6; dither3[0][1] = 8; dither3[0][2] = 4;
    dither3[1][0] = 1; dither3[1][1] = 0; dither3[1][2] = 3;
    dither3[2][0] = 5; dither3[2][1] = 2; dither3[2][2] = 7;

    // create m * m dither matrix;
    int dither_matrix[m][m];

    // total num of pixels = length * width
    total = I1->width * I1->height;

    // initialize I2 dimensions & buffers
    I2->width  = I1->width;
    I2->height = I1->height;

    tmp_img->width = I1->width;
    tmp_img->height = I1->height;

    tmp_img->image = (uchar *) malloc(total);
    I2->image  = (uchar *) malloc(total);
    
    if (I2->image == NULL) {
        cerr << "Insufficient memory\n";
        exit(1);
    }
    if (tmp_img->image == NULL) {
        cerr << "Insufficient memory\n";
        exit(1);
    }

    for (i = 0; i < 256; i++) {
    gamma_corrected_lut[i] = (int) (pow((double) i / 255.0 , (1.0 / gamma)) * 255.0);
    }
    tmp_out = tmp_img->image; // tmp output image buffer after gamma correction
    out = I2->image;    // output image buffer
    in  = I1->image;    // input  image buffer
    
    // this should produce gamma corrected image from look up table.
    // and store the image in tmp_out;
    for (i=0; i<total; i++) tmp_out[i] = gamma_corrected_lut[ in[i] ];

    scale = 256 / (n);
    //cout << scale << endl;
    // init lookup table for quantization
    for (i=0; i < 256; i++) {
        //lut[i] = scale * (int) (i/scale);
        lut[i] = (int) (scale * (i/scale)) / scale;
        cout << i << ":" << ((int) (scale * (i/scale)) / scale ) << endl;
    }
    // visit all input pixels and apply quantization to n levels via lookup table
    for (i=0; i<total; i++) {
        out[i] = lut[tmp_out[i]];
        //cout << (int) lut[tmp_out[i]] << endl;
    }
    int h = I2->height;
    int w = I2->width;
    cout << "n is: " << n << endl;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++ ) {
            int i = x % m;
            int j = y % m;
            //cout << "i: " << i << "j: " << j << endl;

            cout << "in pixel is: " << (int) (out[y*w+x]) << " ;dither is: " << (int) (dither4[i][j]) << endl;

            /*if (out[y*w+x] > dither2[i][j]) {
                out[y*w+x] = 255;
            } else {
                out[y*w+x] = 0;
            }*/

            out[y*w+x] = ((out[y*w+x] > dither4[i][j]) ? 255 : 0);
        }
    }

}

void create_dither_matrix(int m) {

}


bool is_pow_of_2(int n) {
    // returns true if n is a power of 2.
    return (not(n == 0) and not(n & (n - 1)));
}

int clip_values(int pixel_val) {
    // if a is greater than 255, clip at 255; if a is lower than 255; clip at 0;
    // else return the same value;
    if (pixel_val >= 255) {
        return 255;
    } else if (pixel_val <= 0) {
        return 0;
    } else {
        return pixel_val;
    }
}


