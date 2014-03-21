/** 
 * Image Processing
 * Brian Wu
 * Usage sharpen in sz fctr out
 */
#include "IP.h"

using namespace std;

void blur(imageP, imageP, int, int, imageP);


int main(int argc, char** argv) {

    int sz, fctr;
    imageP I1, I2, tmp_img;


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




void blur(imageP P1, imageP tmp_img, int xsz, int ysz, imageP I2) {
}
