// =====================================================================
// Image Procesing
// Brian Wu
// Ordered Dithering
// =====================================================================
/* 1. Quantize input image to n-levels [0...n^2]
 * 2. Create dither matrix that gives (n^2) + 1 matrices
 *  D2 = 0 2  1-d => [0 2 3 1]
 *       3 1
 *  D3 = 6 8 4  1-d => [6 8 4 1 0 3 5 2 7]
 *       1 0 3
 *       5 2 7
 */
#include "IP.h"
using namespace std;

void ordered_dither(imageP, int, float, imageP, imageP);
int clip_values(int);
bool is_pow_of_2(int);

int main(int argc, char** argv)
{
	int	n;
    double gamma;
	imageP	I1, I2, tmp_img;
	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;
    tmp_img = NEWIMAGE;

	// read n and gamma from STDIN
	n = atoi(argv[2]);
    // check if n is a power of 2
    if (n > 3) {
        if (not(is_pow_of_2(n))) {
            cerr << n << " is not a power of 2. Exiting." << endl;
            exit(1);
        }
    }

    gamma = atof(argv[3]);
    
	// threshold image and save result in file
	ordered_dither(I1, n, gamma, I2, tmp_img);
	IP_saveImage(I2, argv[4]);

	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);
    IP_freeImage(tmp_img);
 
	return 1;
}

// Usage: ./ordered_dither in m gamma out
void ordered_dither(imageP I1, int n, float gamma, imageP I2, imageP tmp_img)
{
	int	 i, total, scale, new_total;
	uchar	*in, *out, *tmp_out, lut[256];
    uchar gamma_corrected_lut[256];
    
    // initialize the dither matrices.
    int dither2[4], dither3[9];
    dither3[0] = 6;
    dither3[1] = 8;
    dither3[2] = 4;
    dither3[3] = 1;
    dither3[4] = 0;
    dither3[5] = 3;
    dither3[6] = 5;
    dither3[7] = 2;
    dither3[8] = 7;

    dither2[0] = 0;
    dither2[1] = 2;
    dither2[2] = 3;
    dither2[3] = 1;

	// total number of pixels in image
	total = I1->width * I1->height;

    // new total after increasing by n
    new_total = (n * I1->width) * (n * I1->height);

	// init I2 dimensions and buffer
	I2->width  = n * (I1->width);
	I2->height = n * (I1->height);
    tmp_img->width = I1->width;
    tmp_img->height = I1->height;

    tmp_img->image = (uchar *) malloc(total);
	I2->image  = (uchar *) malloc(new_total);

	if(I2->image == NULL) {
		cerr << "Insufficient memory\n";
		exit(1);
	}
    if(tmp_img->image == NULL) {
        cerr << "Insufficient memory\n";
        exit(1);
    }

    for(i = 0; i < 256; i++) {
    gamma_corrected_lut[i] = (int) (pow((double) i / 255.0 , (1.0 / gamma)) * 255.0);
    }
    tmp_out = tmp_img->image; // tmp output image buffer after gamma correction
    out = I2->image;    // output image buffer
    in  = I1->image;    // input  image buffer
    
    // this should produce gamma corrected image from look up table
    for(i=0; i<total; i++) tmp_out[i] = gamma_corrected_lut[ in[i] ];

    scale = 256 / n;
	// init lookup table for quantization
	for(i=0; i < 256; i++) {
		lut[i] = scale * (int) (i/scale);
        cout << ((scale * (int) (i/scale)) / scale) << endl;
}
	// visit all input pixels and apply lut to threshold
	for(i=0; i<total; i++) out[i] = lut[tmp_out[i]];
}


bool is_pow_of_2(int n) {
    // used to check if input is a power of 2.
    return (not(n == 0) and not(n & (n - 1)));
}

int clip_values(int a){
    // if a is greater than 255, clip at 255; if a is lower than 255; clip at 0;
    // else return the same value;
    if (a >= 255) {
        return 255;
    } else if (a <= 0) {
        return 0;
    } else {
        return a;
    }
}


