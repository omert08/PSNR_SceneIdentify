# carIdentify
This programs  gets two random car images and identify them whether image is belong to same car or not. If so you can do also size comparison between two same cars.

It has also simple user interface designed within QT. It uses PSNR and MMSIM values over images to get if images are belong to same scene or not. 

Identifying same two cars accuracy is %83 over 74 pictures in pairs folder. 

Size comparison accuracy is around %60. It could be improved by detecting contours and making comparison with contour sizes. 

## Build Instructions.

Requirements : 

OpenCV 3.2.0 is recommended but it should work with 3.x 
QT 5.6 at least. 

If you have required libs, to build code you should follow commands below:

```sh
$ qmake -makefile
$ make
$ ./carDetect
```
