// Image Procesing
// Brian Wu
// Unordered Dithering
#include "IP.h"
using namespace std;

void unordered_dither(imageP, int, float, imageP, imageP);
int clip_values(int);

int main(int argc, char** argv) {
    int	n;
    double gamma;
    imageP	I1, I2, tmp_img;
    // read input image (I1) and reserve space for output (I2)
    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;

    // read n and gamma from STDIN
    n = atoi(argv[2]);
    gamma = atof(argv[3]);

    // threshold image and save result in file
    unordered_dither(I1, n, gamma, I2, tmp_img);
    IP_saveImage(I2, argv[4]);

    // free up image structures/memory
    IP_freeImage(I1);
    IP_freeImage(I2);
    IP_freeImage(tmp_img);
    cout << "done" << endl;

	return 1;
}

// Usage: ./unordered_dither in n gamma out
void unordered_dither(imageP I1, int n, float gamma, imageP I2, imageP tmp_img) {
    int	 i, total, scale;
    uchar	*in, *out, *tmp_out, lut[256];
    uchar gamma_corrected_lut[256];

    // total number of pixels in image
    total = I1->width * I1->height;

    // init I2 dimensions and buffer
    I2->width  = I1->width;
    I2->height = I1->height;
    tmp_img->width = I1->width;
    tmp_img->height = I1->height;

    tmp_img->image = (uchar *) malloc(total);
    I2->image  = (uchar *) malloc(total);

    if(I2->image == NULL) {
        cerr << "Insufficient memory\n";
        exit(1);
    }
    if(tmp_img->image == NULL) {
        cerr << "Insufficient memory\n";
    }

    for(i = 0; i < 256; i++) {
    gamma_corrected_lut[i] = (int) (pow((double) i / 255.0 , (1.0 / gamma)) * 255.0);
    }
    tmp_out = tmp_img->image; // tmp output image buffer after gamma correction
    out = I2->image;    // output image buffer
    in  = I1->image;    // input  image buffer

    // this should produce gamma corrected image from look up table
    for(i=0; i<total; i++) tmp_out[i] = gamma_corrected_lut[ in[i] ];

    // create bias
    int bias = ((MXGRAY / n) * 0.5);
    // there may be a bug here
    //cout << "bias: " << bias << endl;

    srand(time(0));
    // apply random dither to Image
    for(i = 0; i < total; i++ ) {
        int randomized_bias = rand() % bias;
        //cout << randomized_bias << endl;
        // on even, add. bitwise faster than modulo.
        if((i & 1) == 0) {
            tmp_out[i] = clip_values(tmp_out[i] + randomized_bias);
        }
        // on odd, subtract
        else {
            tmp_out[i] = clip_values(tmp_out[i] - randomized_bias);
        }
    }

    scale = 256 / n;
    // init lookup table for quantization
    for(i=0; i<256 ; i++) {
        lut[i] = scale * (int) (i/scale);
    }
        // visit all input pixels and apply lut to threshold
        for(i=0; i<total; i++) out[i] = lut[tmp_out[i]];
}

int clip_values(int a) {
    // if a is greater than 255, clip at 255;
    // if a is lower than 255; clip at 0;
    // else return the same value;
    if (a >= 255) {
        return 255;
    }
    else if(a <= 0) {
        return 0;
    }
    else {
        return a;
    }

}
