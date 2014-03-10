/**
 * Image Processing
 * Brian Wu
 * Halftone
 * Usage ./haltone in m gamma out
 */

#include "IP.h"
using namespace std;

void halftone(imageP, int, float, imageP);

int main(int argc, char** argv) {
    int m;
    double gamma;
    imageP I1, I2;

    I1 = IP_readImage(argv[1]);
    I2 = NEWIMAGE;

    m = atoi(argv[2]);
    gamma = atof(argv[3]);

    halftone(I1, m, gamma, I2);
    IP_saveImage(I2, argv[4]);

    IP_freeImage(I1);
    IP_freeImage(I2);
    
    cout << "done" << endl;

    return 1;


}
