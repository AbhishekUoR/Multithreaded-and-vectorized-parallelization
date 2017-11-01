# Using

The convolution matrices are *.txt files.

Compile 2dconv as:
    make

Uncompress the sample PPM files:
    
    tar jxf sample-images.tar.bz2

Run 2dconv as:

    ./2dconv matrix.txt in.ppm out.ppm

Where in.ppm and out.ppm are the input and output filenames
respectively.

You can convert any file to the ppm expected by 2dconv as:

    jpegtopnm in.jpg | pnmtoplainpnm > in.ppm

These tools are provided by the netpbm tools.

You can use the diff tool to compare the output of 2dconv to your
tool.


# Acknowledgments

The file 800px-TajPaintedGeometry.ppm was derived from a public domain
file obtained from Wikipedia.

The file buggy-2048x2048.ppm was derived from a public domain file
obtained from the Project Apollo Archives.

The file modis_wonderglobe_lrg.ppm was derived from a public domain
file obtained from NASA.

The convolution matrices were obtained from the Wikipedia article on
"Kernels" (as was the Vd-Orig.ppm file), as well as from the GIMP User
Manual.

The PPMA_IO library is Copyright (C) John Burkardt and is used under
the conditions of the LGPL. It is available at:
<https://people.sc.fsu.edu/~jburkardt/c_src/ppma_io/ppma_io.html>
