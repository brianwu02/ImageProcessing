/**
 * Image Processing
 * Brian Wu
 * Error Diffusion
 * Usage: error_diffusion in mtd serpentine gamma out
 */
#include "IP.h"
using namespace std;

void error_diffusion(imageP, int, int, double, imageP);

int main(argc, char** argv) {
    int mtd, serpentine;
    double gamma;
    imageP I1, I2;

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
