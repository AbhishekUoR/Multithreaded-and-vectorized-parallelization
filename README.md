# Multithreaded-and-vectorized-parallelization
Binary Tree Reduction using C++ threads

Binary Tree Reduction
The program gives option to the user to either supply file containing numbers or number of elements you want and program generates random number and sums those number using tree reduction technique using c++ threads.

For 2d Convolution
The convolution matrix can be in 3x3 or 5x5 sizes. The
image can be upto 4096x4096x24bpp (i.e. 3x8 bits per pixel).
The program accepts a PPM image and produce an output in the PPM format. One advantage of PPM is that
the file is a text format, so you can see its internals. One disadvantage is that the files are quite large.
I have enclosed a reference program 2dconv.cpp that performs this task. See README-2dconv.txt for information
on how to run this program.
The goal was to speedup 2dconv.cpp program using autovectorization and multiple threads (C++ threads).

