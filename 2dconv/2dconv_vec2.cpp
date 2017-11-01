
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "ppma_io.h"
#include "ppma_io.c"
#include "Timer.h"
#include <iostream>
#include <thread>

using namespace std;

struct ppm {
  int xsize;   
  int ysize;
  int rgb_max;
  int *r;
  int *g;
  int *b;
};

void trip(const char *message) {
  int err = errno;
  fprintf(stderr, "Error: %s (%d: %s)\n", message, err, strerror(err));
}

static int min(int a, int b) {
  if(a < b) 
    return a; 
  else 
    return b;
}

static int max(int a, int b) {
  if(a > b) 
    return a; 
  else 
    return b;
}

static int lin(int y, int x, int size) {
  return y * size + x;
}

int alloc_img(struct ppm *p) {
  p->r = (int *) malloc(p->xsize * p->ysize * sizeof(int));
  p->g = (int *) malloc(p->xsize * p->ysize * sizeof(int));
  p->b = (int *) malloc(p->xsize * p->ysize * sizeof(int));

  if(!p->r  || !p->g || !p->b) {
    fprintf(stderr, "Failed to allocate memory for image\n");
    return 0;
  }

  return 1;
}
int parallel(int a, int b, int n, int *cm, struct ppm *img, struct ppm *out)
{
  out->ysize = img->ysize;
  out->xsize = img->xsize;
 // if(a == 0 || b == img->ysize){
       // if (a == 0) m =a;
       // if (b == img->ysize) m =b;
/*	for(y = 0; y < img->ysize ;y + (img->ysize-2)){
	for(int x = 0; x < (img->xsize); x++) {

      		int accum_r = 0;
      		int accum_g = 0;
     		int accum_b = 0;

      		for(int i = 0; i < n*n; i++) {
       			 int r = i / n - n / 2;
        		 int c = i % n - n / 2;
			 if(m + r < 0) continue;
			 if(m + r >= img->ysize) continue;
		         accum_r += img->r[lin(m + r, x + c, img->xsize)] * cm[i];
			 accum_g += img->g[lin(m + r, x + c, img->xsize)] * cm[i];
			 accum_b += img->b[lin(m + r, x + c, img->xsize)] * cm[i];

      						}
      out->r[lin(m, x, img->xsize)] = min(max(accum_r, 0), 255);
      out->g[lin(m, x, img->xsize)] = min(max(accum_g, 0), 255); 
      out->b[lin(m, x, img->xsize)] = min(max(accum_b, 0), 255); 
    							}}i*/

		
		
  
  
  for(int y = a; y < b; y++) {
    for(int x = 1; x < (img->xsize-1); x++) {

      int accum_r = 0;
      int accum_g = 0;
      int accum_b = 0;

      for(int i = 0; i < n*n; i++) {
	int r = i / n - n / 2;
	int c = i % n - n / 2;
	
	// essentially values beyond the image borders are zero
	//if(y + r < 0) continue;
	//if(x + c < 0) continue;

	//if(y + r >= img->ysize) continue;
	//if(x + c >= img->xsize) continue;

       // cout << "cm = " << cm[i] << "i =" << i << endl; 	
	accum_r += img->r[lin(y + r, x + c, img->xsize)] * cm[i];
	accum_g += img->g[lin(y + r, x + c, img->xsize)] * cm[i];
	accum_b += img->b[lin(y + r, x + c, img->xsize)] * cm[i];

      }
      out->r[lin(y, x, img->xsize)] = min(max(accum_r, 0), 255);
      out->g[lin(y, x, img->xsize)] = min(max(accum_g, 0), 255); 
      out->b[lin(y, x, img->xsize)] = min(max(accum_b, 0), 255); 
    }
  }
     
/*      for(int y = 0; y < (img->ysize); y++) {
      for(int x = 0;x < img->xsize; x+(img->xsize-2)){ 
	
                int accum_r = 0;
                int accum_g = 0;
                int accum_b = 0;

                for(int i = 0; i < n*n; i++) {
                         int r = i / n - n / 2;
                         int c = i % n - n / 2;
                         if(x + c < 0) continue;
                         if(x + c >= img->xsize) continue;
                         accum_r += img->r[lin(y + r, x + c, img->xsize)] * cm[i];
                         accum_g += img->g[lin(y + r, x + c, img->xsize)] * cm[i];
                         accum_b += img->b[lin(y + r, x + c, img->xsize)] * cm[i];

                                                }
      out->r[lin(y, x, img->xsize)] = min(max(accum_r, 0), 255);
      out->g[lin(y, x, img->xsize)] = min(max(accum_g, 0), 255);
      out->b[lin(y, x, img->xsize)] = min(max(accum_b, 0), 255);
                                                        }}*/

                }




int convolve(int threads,int n, int *cm, struct ppm *img, struct ppm *out) {

  out->xsize = img->xsize;
  out->ysize = img->ysize;
  int a , b;
  if(!alloc_img(out)) return 0;
  //cout << "ysize=" << img->ysize << endl;
  //cout << "threads = " << threads << endl;
  a = 1;
  thread t1[threads];
  
  b = img->ysize/threads;
  //cout << " a =" << a << " b= " << b << endl;


  ggc::Timer t("parallel");
  t.start();
        for(int y = 0; y < img->ysize ;y++){
        for(int x = 0; x < (img->xsize); x++) {

                int accum_r = 0;
                int accum_g = 0;
                int accum_b = 0;

                for(int i = 0; i < n*n; i++) {
                         int r = i / n - n / 2;
                         int c = i % n - n / 2;
                        // if(y + r < 0) continue;
                        // if(y + r >= img->ysize) continue;
                         accum_r += img->r[lin(y + r, x + c, img->xsize)] * cm[i];
                         accum_g += img->g[lin(y + r, x + c, img->xsize)] * cm[i];
                         accum_b += img->b[lin(y + r, x + c, img->xsize)] * cm[i];

                                                }
      out->r[lin(y, x, img->xsize)] = min(max(accum_r, 0), 255);
      out->g[lin(y, x, img->xsize)] = min(max(accum_g, 0), 255); 
      out->b[lin(y, x, img->xsize)] = min(max(accum_b, 0), 255); 
                                                        }  
        	y += img->ysize - 2;}


  for(int y = 0; y < (img->ysize); y++) {
      for(int x = 0;x < img->xsize; x++){ 
                int accum_r = 0;
                int accum_g = 0;
                int accum_b = 0;

                for(int i = 0; i < n*n; i++) {
                         int r = i / n - n / 2;
                         int c = i % n - n / 2;
                 //        if(x + c < 0) continue;
                //         if(x + c >= img->xsize) continue;
                         accum_r += img->r[lin(y + r, x + c, img->xsize)] * cm[i];
                         accum_g += img->g[lin(y + r, x + c, img->xsize)] * cm[i];
                         accum_b += img->b[lin(y + r, x + c, img->xsize)] * cm[i];

                                                }
      out->r[lin(y, x, img->xsize)] = min(max(accum_r, 0), 255);
      out->g[lin(y, x, img->xsize)] = min(max(accum_g, 0), 255);
      out->b[lin(y, x, img->xsize)] = min(max(accum_b, 0), 255);
        	x += img->xsize - 2;}}



	for (int i = 0; i < threads; i++) {
    		t1[i] = thread ( parallel, a, b, n, cm, img, out );

  		//cout << " A =" << a << " B= " << b << endl;
                a = b ;
		if(i < (threads - 2))
			
	   		b = b + (img->ysize/threads) ;
		else 
	 	
			b = img->ysize - 1;
                                           }
        for (int i = 0; i < threads; ++i) {
                t1[i].join();             }
                                          
        t.stop();
  	printf("Time: %llu ns\n", t.duration());
	return 1;
									}



int read_ppm(const char *f, struct ppm *p) {
  FILE *fh;

  fh = fopen(f, "r");
  if(!f) {
    trip("Error: could not open input file");
    return 0;
  }

  ppma_read_header(fh, &p->xsize, &p->ysize, &p->rgb_max);

  if(p->rgb_max > 255) {
    fprintf(stderr, "No support for more than 8 bits per pixel\n");
    return 0;
  }

  if(!alloc_img(p)) return 0;

  ppma_read_data(fh, p->xsize, p->ysize, p->r, p->g, p->b);

  fprintf(stderr, "Read image: %dx%d (rgb_max: %d)\n", p->xsize, p->ysize, p->rgb_max);

  return 1;
}

int write_ppm(char *f, struct ppm *p) {
  if(ppma_write(f, p->xsize, p->ysize, p->r, p->g, p->b)) {
    return 0;
  }

  return 1;
}

int read_convolution_matrix(const char *f, int *n, int **matrix) {
  // read a convolution matrix from file f into nxn array matrix

  FILE *fh;

  fh = fopen(f, "r");

  if(fh == NULL) {
    trip("Error: could not open convolution matrix file");
    return 0;
  }

  /* convolution matrix is a square matrix of size n where n is odd */
  if(fscanf(fh, "%d", n) != 1) {
    fprintf(stderr, "Failed to read matrix size\n");
    return 0;
  }

  if(*n % 2 == 0) {
    fprintf(stderr, "Can only handle square convolution matrix\n");
    return 0;
  }
  
  fprintf(stderr, "Reading %d x %d convolution matrix\n", *n, *n);

  *matrix = (int *) malloc((*n) * (*n) * sizeof(float));
  
  int *mm = *matrix;

  if(!mm) {
    fprintf(stderr, "Failed allocation\n");
    return 0;
  }

  for(int i = 0; i < (*n) * (*n); i++) {
    if(fscanf(fh, "%d", &mm[i]) != 1) {
      fprintf(stderr, "Failed to read matrix element %d\n", i);
    
      return 0;
    }
  }

  fprintf(stderr, "Done.\n");

  return 1;
}

int main(int argc, char *argv[]) {
  if(argc != 5) {
    fprintf(stderr, "Usage: %s convolution_matrix input_ppm output_ppm\n", argv[0]);
    exit(1);
  }

  int n, *cm;
  struct ppm img, out;

  if(!read_convolution_matrix(argv[1], &n, &cm)) {
    exit(1);
  }  
  //cout << "n = " << n << " cm =" << *cm << endl;  
  if(!read_ppm(argv[2], &img)) {
    exit(1);
  }

  /* do any transformations to img here, if necessary */
  int threads = atoi(argv[4]);
  ggc::Timer t("parallel");

  //t.start();
  if(!convolve(threads,n, cm, &img, &out)) {
    exit(1);
  }
 // t.stop();


  /* do any transformations to out here, if necessary */

  if(!write_ppm(argv[3], &out)) {
    exit(1);
  }

  fprintf(stderr, "Done writing file!\n");
}
