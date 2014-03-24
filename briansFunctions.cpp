/**
 * Image Processing
 * Brian Wu
 * A bunch of functions that may be used in the future
 */
#include "IP.h"

using namespace std;

void padImage(imageP, int, imageP);
void copyToBuffer(imageP, int, int, unsigned char*);

void padImage(imageP I1, int sz, imageP paddedImg) {
    /* PIXEL REPLICATION PADDING
     * takes I1 as input image, I1 and applies pixel replication technique
     * to paddedImg using kernel size sz * sz.
     *   Pixel Replcation Example:
     *                             leftIdx         rightIdx
     *   AA|ABCDEFGH|HH                    x x x x
     *   AA|ABCDEFGH|HH        region0  |  region1  |  region2   y
     *   --------------        -------------------------------  topIdx
     *   AA|ABCDEFGH|HH        region3  |           |  region5   y
     *   II|IJKLMNOP|PP        region3  |  region4  |  region5   y
     *   QQ|QRSTUVWX|XX        region3  |  orig img |  region5   y
     *   YY|YZabcdef|ff        region3  |           |  region5   y
     *   gg|ghijklmn|nn        -------------------------------  botIdx
     *   oo|opqrstuv|vv        region6  | region 7  | region 8   y
     *   --------------
     *   oo|opqrstuv|vv       
     *   oo|opqrstuv|vv
     *   
     *   region0 = x <  leftIdx  and y <  topIdx
     *   region1 = x >= leftIdx  and x <  rightIdx and y <  topIdx 
     *   region2 = x >= rightIdx and y <  topIdx
     *   region3 = x <  leftIdx  and y >= topIdx   and y <  botIdx
     *   region4 = x >= leftIdx  and x <  rightIdx and y >= topIdx and y < botIdx
     *   region5 = x >= rightIdx and y >= topIdx   and y <  botIdx
     *   region6 = x <  leftIdx  and y >= botIdx
     *   region7 = x >= leftIdx  and x <  rightIdx and y >= botIdx
     *   region8 = x >= rightIdx and y >= botIdx
     *
     */

    int n = (sz - 1) / 2;
    int m = (sz - 1) / 2;
    unsigned char *in, *paddedOut;

    int total = I1->width * I1->height;
    int w = I1->width;
    int h = I1->height;

    paddedImg->width = (w + 2*m);
    paddedImg->height = (h + 2*n);

    int paddedTotal = paddedImg->height * paddedImg->width;
    paddedImg->image = (unsigned char*) malloc(paddedTotal);
    paddedOut = paddedImg->image;
    in = I1->image;

    int paddedHeight = paddedImg->height;
    int paddedWidth = paddedImg->width;

    // vertical indices that represent padding columns
    int leftIdx = n;
    int rightIdx = w + n;

    // horizontal indices that represent padding rows
    int topIdx = m;
    int botIdx = h + m;


    for (int y=0; y < paddedHeight; y++) {
        for (int x=0; x < paddedWidth; x++) {

            // this condition comes first since it will occur most frequent.
            // dont need the branch predictor working so hard.
            if (x >= leftIdx and x < rightIdx and y >= topIdx and y < botIdx) {
                // we are in region 4.
                paddedOut[y*paddedWidth+x] = in[(y-n) * w + (x-m)];

            } else if (x < leftIdx and y < topIdx) {
                // we are in region 0.
                // assign padded pixel as upper left original pixel value.
                paddedOut[y*paddedWidth+x] = in[0]; 

            } else if (x >= leftIdx and x < rightIdx and y < topIdx) {
                // we are in region 1.
                // assign pixel values to be top row of original image.
                paddedOut[y*paddedWidth+x] = in[(x-m)]; 
                
            } else if (x >= rightIdx and y < topIdx) {
                // we are in region 2.
                // assign padded pixels as upper right original pixel value.
                paddedOut[y*paddedWidth+x] = in[w-1];

            } else if (x < leftIdx and y >= topIdx and y < botIdx) {
                // we are in region 3.
                // assigned padded pixel as left most pixel of current row.
                paddedOut[y*paddedWidth+x] = in[(y - n) * w];

            } else if (x >= rightIdx and y >= topIdx and y < botIdx) {
                // we are in region 5
                // assign padded pixel as right most pixel of current row
                paddedOut[y*paddedWidth+x] = in[(y - n) * w + (w-1) ];

            } else if (x < leftIdx and y >= botIdx) {
                // we are in region 6
                // assign padded pixel as bottom left original pixel value.
                paddedOut[y*paddedWidth+x] = in[w*(h-1)];
            
            } else if (x >= leftIdx and x < rightIdx and y >= botIdx) {
                // we are in region 7
                // assign padded pixel to be bottom-most row of original input img.
                paddedOut[y*paddedWidth+x] = in[(h-1) * w + (x-m)];
            
            } else if (x >= rightIdx and y >= botIdx) {
                // we are in region 8
                // assign padded pixel as bottom right original pixel value.
                paddedOut[y*paddedWidth+x] = in[w*h-1];
            
            } else {
                // this should never happen since this will only occur if we have
                // not handled a certain x,y coordinate.
                cout << "unhandled condition, something bad" << endl;
                cout << "x is: " << x << " y is: " << y << endl;
            }
        }
    }
}


void copyToBuffer(imageP I1, int row, int bufRowsRequired, unsigned char *buffer) {
    int height = I1->height;
    int width = I1->width;
    unsigned char *in, *ptr;
    in = I1->image;

    int bufStartIndex = (row % bufRowsRequired) * width;

    ptr = &buffer[bufStartIndex];
    for (int x=0; x<width; x++) {
        ptr[0] = in[row*width+x];
        ptr++;
    }
}
