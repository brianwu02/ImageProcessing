## Image Processing


Files not included in repo: IP.h, IPutil.cpp, makefile.

ordered dither


####error_diffusion.cpp

usage: error_diffusion *infile* *mtd* *serpentine* *gamma* *outfile*

mtd = 0; Use Floyd Steinberg Error Diffusion Algorithm, 

mtd = 1; Use Jarvis-Judice-Ninke Error Diffusion Algorithm.

serpentine = 1; Use serpentine scanning method, where even rows are processed left to right while 
odd rows are processed right to left.

serpentine = 0; scan left to right.

1. Gamma correct the input image.

2. 

####halftone.cpp

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


