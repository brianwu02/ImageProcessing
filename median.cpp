/**
 * Image Processing
 * Brian Wu
 * median filter
 * Usage: median in sz avg_nbrs out
 */
#include "IP.h"
#include <algorithm>
#include <iostream>

using namespace std;

void median(imageP, imageP, int, int, imageP);
void padImage(imageP, int, imageP);
void copyToBuffer(imageP, int, int, unsigned char*);

int main(int argc, char** argv) {
    
    int sz, avg_nbrs;
    imageP I1, I2, paddedImg;
   
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

    if (sz != 3) {
        cerr << "sz only working for 3, as requested. exiting." << endl;
        exit(1);
    }

    if (avg_nbrs > sz) {
        cerr << "average number cannot be larger than sz, at least i dont think it can" << endl;
        exit(1);
    }

    I1 = IP_readImage(argv[1]);

    I2 = NEWIMAGE;
    paddedImg = NEWIMAGE;

    padImage(I1, sz, paddedImg);
    median(I1, paddedImg, sz, avg_nbrs, I2);

    //IP_saveImage(paddedImg, argv[4]);
    IP_saveImage(I2, argv[4]);
    IP_freeImage(I1);
    IP_freeImage(I2);
    IP_freeImage(paddedImg);
    return 0;

}

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

void median(imageP I1, imageP paddedImg, int sz, int avg_nbrs, imageP I2) {
    
    int i, total, paddedTotal;
    unsigned char *in, *out, *paddedIn, *buf;
    

    total = I1->width * I1->height;
    paddedTotal = paddedImg->height * paddedImg->width;

    I2->height = I1->height;
    I2->width = I1->width;

    I2->image = (unsigned char *) malloc(total);

    in = I1->image;
    out = I2->image;
    paddedIn = paddedImg->image;

    if (I2->image == NULL) {
        cerr << "not enough memory\n";
        exit(1);
    }

    // number of extra columns required.
    int m = (sz - 1) / 2; 
    // number of extra rows required. 
    int n = (sz - 1) / 2;

    int w = I1->width;
    int h = I1->height;
    int paddedWidth = paddedImg->width;
    int paddedHeight = paddedImg->height;

    // number of buffer rows required. a 3x3 kernel requires 3 rows, 5x5 requires 5 rows.
    int bufRowsRequired = m + n + 1;

    // allocate memory for an array that will hold (m + n + 1) row buffer.
    unsigned char *arrayOfPointers[bufRowsRequired];

    // allocate memory for the (m+n+1) row of buffers.
    buf = (unsigned char *) malloc(paddedWidth * bufRowsRequired);

    // assign pointers to each 'row' in buffer. If there are 3 rows required for the kernel image,
    // there will be 3 pointers in arrayOfPointers pointing to each portion of the buffer.
    for (int i=0; i<bufRowsRequired; i++) {
        arrayOfPointers[i] = &buf[i*paddedWidth];
    }

    // need to copy bufRowsRequired - 1 rows to the buffer.
    for (int y=0; i<(bufRowsRequired-1); y++) {
        copyToBuffer(paddedImg, y, bufRowsRequired, buf);
    }

    int kernel_size = (sz * sz);
    static const size_t v_size = kernel_size;
    

    // try to get this working for 3 * 3 kernel 
    unsigned char *r0, *r1, *r2;
    unsigned char k[kernel_size];
    for (int y=0; y<h; y++) {
        // need to copy the last row required in to the buffer. should be row = bufRowsRequired
        copyToBuffer(paddedImg, y + (bufRowsRequired-1), bufRowsRequired, buf);
        r0 = arrayOfPointers[y % 3] + m;
        r1 = arrayOfPointers[(y+1) % 3] + m;
        r2 = arrayOfPointers[(y+2) % 3] + m;
        for (int x=0; x<w; x++) {
            

            k[0] = r0[-1];
            k[1] = r0[0];
            k[2] = r0[1];
            k[3] = r1[-1];
            k[4] = r1[0];
            k[5] = r1[1];
            k[6] = r2[-1];
            k[7] = r2[0];
            k[8] = r2[1];


            std::sort(k, k + kernel_size);
            // because im really lazy right now.
            if (avg_nbrs == 0) {
                out[y*w+x] = k[4];
            } else if (avg_nbrs == 1) {
                out[y*w+x] = (k[3] + k[4] + k[5]) / 3;
            } else if (avg_nbrs == 2) {
                out[y*w+x] = (k[2] + k[3] + k[4] + k[5] + k[6]) / 5;
            } else if (avg_nbrs == 3) {
                out[y*w+x] = (k[1] + k[2] + k[3] + k[4] + k[5] + k[6] + k[7]) / 7;
            } else if (avg_nbrs == 4) {
                out[y*w+x] = (k[0] + k[1] + k[2] + k[3] + k[4] + k[5] + k[6] + k[7] + k[8]) / 9;
            }

            r0++;
            r1++;
            r2++;

        }
    }
    free(buf);
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

    



    


        // optimizations that can be done:
        // 1. pre-sort the array once before each inner loop. then for each consequent inner loop,
        // remove the first element of the sorted index and add the next element. this way, we are
        // not doing as many element copies and std::sort would take less time.
        
        //cout << "medianIndex: " << medianIndex << endl;

        /* 
         * this method is wrong because it scans only horizontally. worked for blur & sharpen
         * but will not work for median.
         *
        for (int x=0; x<w; x++) {
            // copy values that are needed to the Kernel Buffer
            for (int i=0; i<kernel_size; i++) {
                kernelBuffer[i] = buf[i];
            }
            // sort the kernel Buffer
            std::sort(kernelBuffer, kernelBuffer + kernel_size);

            if (avg_nbrs == 0) {
                // if avg_nbrs is 0, then take the median value.
                out[y*w+x] = kernelBuffer[medianIndex];
                //cout << "value: " << kernelBuffer[medianIndex] << endl;
            } else {
                // else, take the average of the pixels above and below pixel.
                int startIdx = medianIndex - avg_nbrs;
                int endIdx = medianIndex + avg_nbrs;
                int sum = 0;
                int avg = 0;

                for (int k = startIdx; k <= endIdx; k++) {
                    sum += kernelBuffer[k];
                }
                avg = sum / (avg_nbrs + 1);
                cout << "avg is: " << avg << endl;
                out[y*w+x] = avg;
            }
        }*/
    


int clip(int a) {
    if (a >= 255) {
        return 255;
    } else if (a <= 0) {
        return 0;
    } else {
        return a;
    }
}
