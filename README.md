## Image Processing
*please don't kill me for deeply nested for loops and neglecting to factor out methods*

To execute scripts: 
    ```javascript
    node scriptrunner.js
    ```

####convolve.cpp

Convolve input image *in* with *kernel* and store result in *out*. Convolution kernel is stored
in file *kernel*. 

*kernel* is a 2-D array of ASCII numbers. first line of this file consists of width & height.

1. Read kernel ASCII values from file *in*.

2. Pad the input image using pixel replication.

3. Apply the Kernel filter to the input image. 

4. profit.

usage: __convolve__: *in* *kernel* *out*

__in__: [FILE] input file. PGM Format.

__kernel__: [FILE] input kernel. File consisting of ASCII numbers.

__out__: [FILE] output file. PGM Format.



####median.cpp

Apply median filter to *in* over a neighborhood of size *sz* * *sz*. Input values are sorted
and the median is averaged with *avg_nbrs* pixels below and *avg_nbrs* pixels above the sorted list.
result is stored in *out*. If *avg_nbrs* = 0, then output is the median. If *avg_nbrs* = sz^2 / 2,
then the output should be idential to *blur.cpp* pad image using pixel replication.

1. pad the input image using pixel replication technique.

2. create circular buffer that conforms to kernel size.

3. using the circular buffer, apply median technique where the *sz* * *sz* kernel is sorted
and the median value is taken. 

usage: __median__ *in* *sz* *avg_nbrs* *out*

__in__: [FILE] input file. PGM format.

__sz__: [INT] Median filter kernel size of *sz* * *sz*. Odd.

__avg_nmbrs__: [INT] integer value representing the pixels to the left and right of the current
pixel that will be averaged with the median of median kernel. Cannot be larger than *sz*.

__out__: [FILE] output file. PGM format.




####sharpen.cpp

Sharpen an image by subtracting a blurred version from it's original value and the scaled
difference back to input image.

usage: __sharpen__ *in* *sz* *fctr* *out*

__in__: [FILE] input image. PGM file.

__sz__: [INT] filter of dimension sz * sz.

__fctr__: [INT] A multiplier that will be applied to the difference between blurred
and original image.

__out__: [FILE] output image.


####blur.cpp

usage: __blur__ *in* *xsz* *ysz* *out*

__in__: infile.

__xsz__: number of columns used in box filter

__ysz__: number of rows used in box filter.

__out__: outfile.

Reads an input image in and blurs it with a box filter, kernel using unweighted averaging.
Kernel filter has dimensions xsz * ysz where xsz is are rows and ysz are columns. xsz and
ysz must be odd.

1. blur the rows, store in temporary buffer.

2. then pass do a pass on the temporary buffer and blur the columns.

3. store the result in output image.



####error_diffusion.cpp

usage: __error_diffusion__ *infile* *mtd* *serpentine* *gamma* *outfile*

__*mtd*__: 0; Use Floyd Steinberg Error Diffusion Algorithm.

__*mtd*__: 1; Use Jarvis-Judice-Ninke Error Diffusion Algorithm.

__*gamma*__: use 1.0 for no gamma correction.

__*serpentine*__: 1; Use serpentine scanning method, where even rows are processed left to right while 
odd rows are processed right to left.

__*serpentine*__: 0; scan left to right.

1. Gamma correct the input image.

2. Create circuluar buffer. Pad the circular buffer with 0's simulating a 'border' for the pixels. 
Padding is necessary for error distribution to function properly when the output kernel is on an edge pixel
without padding, error would be distributed to a location not allocated in memory. 

3. Apply error correctly according to algorithm selected. 

####halftone.cpp

usage: __halftone__ *infile* *m* *gamma* *outfile*

*m*: select *m* * *m* cluster matrix where *m* <= 10

*gamma*: use 1.0 for no gamma correction.


1. Gamma correct the input image.

2. quantize the input image to n levels. Each pixel should now be represented by an m*m cluster matrix.

3. Compare each input pixel to a cluster dot matrix. If the quantized pixel value
is greater than value found in cluster dot matrix, turn pixel value to 255, otherwise turn to 0.

Explanation of 4 deep for loops so I dont forget:
The first 2 for loops will loop over the "big pixel" and the next 2 for loops will loop over the "small pixels".
For each big pixel iteration, compare the input pixel m*m times against each entry in the cluster matrix.
If the value of the quantized input pixel is larger than the value in the cluster matrix, then turn on the
output pixel. 

Here is where the magic happens:

```C++
for (int y=0; y<h; y++){
    for (int x=0; x<w; x++) {
        for (int j=0; j<m; j++) {
            for (int i=0; i<m; i++){
                out[(m*y*nh) + (j*nw) + i + (m*x)] = ((in[y*w+x] > clusterDot[i][j])] 255 : 0);

            }
        }
    }
}
```

*(m * y * nh) + (j * nw) + i + (m * x)* maps a 2d array to a 1d array. where each input pixel is now represented
by an m * m cluster dot matrix.

#### ordered_dithering.cpp

usage: unordered_dither *infile* *gamma* *n* *outfile* where n is quantization levels.

#### unordered_dithering.cpp


## Images before processing
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


