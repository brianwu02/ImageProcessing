
/* ======================================================================
 * IP.h - Image processing header file.
 * Copyright (C) 2012 by George Wolberg
 *
 * Written by: George Wolberg, 2012
 * ======================================================================
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>

#define MaxGray		255
#define MXGRAY		256
#define NEWIMAGE	((imageP) malloc(sizeof(imageS)))
#define NEWKERNEL   ((kernelP) malloc(sizeof(kernelS)))

/* useful macros */
#define ABS(A)		((A) >= 0 ? (A) : -(A))
#define SGN(A)		((A) > 0 ? 1 : ((A) < 0 ? -1 : 0 ))
#define ROUND(A)	((A) >= 0 ? (int)((A)+.5) : -(int)(.5-(A)))
#define FLOOR(A)	((A) >= 0 ? (int) (A) : (int) (A)-1)
#define CEILING(A)	((A)==FLOOR(A) ? FLOOR(A) : SGN(A)+FLOOR(A))
#define MAX(A,B)	((A) > (B) ? (A) : (B))
#define MIN(A,B)	((A) < (B) ? (A) : (B))
#define SWAP(A,B)	{ double temp=(A); (A)  = (B);	(B)  = temp; }
#define SWAP_INT(A,B)	{ (A) ^= (B);	   (B) ^= (A);	(A) ^= (B);  }
#define CLAMP(A,L,H)	((A)<=(L) ? (L) : (A)<=(H) ? (A) : (H))

typedef unsigned char	uchar;

typedef struct {	/* image data structure	 */
	int width;	/* image width  (# cols) */
	int height;	/* image height (# rows) */
	uchar *image;	/* pointer to image data */
} imageS, *imageP;

typedef struct {
    int width;
    int height;
    float *kernel;
} kernelS, *kernelP;

extern imageP	IP_readImage	(char *);
extern void	IP_saveImage	(imageP, char*);
extern imageP	IP_allocImage	(int, int, int);
extern void	IP_freeImage	(imageP);
extern void padImage(imageP, int, imageP);
extern void copyToBuffer(imageP, int, int, unsigned char*);
extern void copyToBufferPadded(imageP, int, int, unsigned char*);
extern void floatCopyToBuffer(imageP, int, int, float*);
extern int clip(int);
extern float fclip(float);
