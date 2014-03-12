
Files not included in repo: IP.h, IPutil.cpp, makefile.

unordered_dither *infile* *gammaRatio* *n* *outfile* where n is quantization levels.
ordered dither

halftone:

1. quantize the input image to n levels. Each pixel should now be represented by an m*m cluster matrix.

2. Compare each input pixel to a cluster dot matrix. If the quantized pixel value
is greater than value found in cluster dot matrix, turn pixel value to 255, otherwise turn to 0.

Explanation of 4 deep for loops so I dont forget:
The first 2 for loops will loop over the "big pixel" and the next 2 for loops will loop over the "small pixels".
For each big pixel iteration, compare the input pixel m*m times against each entry in the cluster matrix.
If the value of the quantized input pixel is larger than the value in the cluster matrix, then turn on the
output pixel. 

*(m * y * nh) + (j * nw) + i + (m * x)* maps a 2d array to a 1d array. where each input pixel is now represented
by an m * m cluster dot matrix.

## Default Images before processing
##### mad256.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/mad256.png)
##### mad256.png after ordered dithering m=8 and gamma ratio 1.0
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/odithered8_mad256.png)
##### maddot.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/maddot.png)
##### mandrill256.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/mandrill256.png)
##### ramp.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/ramp.png)
##### star.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/star.png)
##### text.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/master/images/text.png)
##### empire.png
![alt tag](https://raw.github.com/brianwu02/ImageProcessing/mastear/images/empire.png)


