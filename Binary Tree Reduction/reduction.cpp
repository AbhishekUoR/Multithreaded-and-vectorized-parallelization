#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Timer.h"
#include <thread>         
#include <iostream>

using namespace std;


	int adder(int begin, int end, int &result, int *num){
		 result = 0;	
		 int d = 0;
      			//cout << "d " << d[id] << endl;
  		 for( int i = begin ; i <= end ; i++  )
    			{
      			d = d + num[i];
     			}
    		result = d; }			


int * gen_number(int N) {
  int *num;

  num = (int *) malloc(sizeof(int) * N);

  for(int i = 1; i <= N; i++) {
    num[i] = i % 2;
    //cout  << "num = " << num[i] << endl;
  }

  fprintf(stderr, "Generated %d numbers\n", N);
  return num;
}

int * read_number_file(char *f, int &N) {
  FILE *x;
  char *line = NULL;
  size_t len;
  ssize_t read;
  int *num;

  fprintf(stderr, "Reading %s\n", f);

  x = fopen(f, "r");
  if(x == NULL) {
    fprintf(stderr, "Can't read file %s\n", f);
    return NULL;
  }

  if(getline(&line, &len, x) == -1) {
    fprintf(stderr, "Couldn't read length of array\n");
    return NULL;
  }
  
  /* first line of file contains length of array */
  N = atoi(line);
  if(N <= 0) {
    fprintf(stderr, "Invalid length of array\n");
    return NULL;
  }

  
  num = (int *) malloc(sizeof(int) * N);

  /* rest of file contains one number per line */
  for(int i = 0; i < N; i++) {
    if(getline(&line, &len, x) == -1) {
      fprintf(stderr, "Couldn't read line %d of array\n", i);
      return NULL;
    }
  
    num[i] = atoi(line);
  }

  fclose(x);

  fprintf(stderr, "Read %d numbers from %s\n", N, f);

  return num;
}

void usage(char *argv[]) {
  fprintf(stderr, "Usage: %s [-t THREADS] [-n NUMBERS | -f FILE]", argv[0]);
  fprintf(stderr, "\nAdd the first NUMBERS integers or the numbers in FILE using THREADS threads.\n");

}

int parse_args(int argc, char *argv[], int &threads, int &N, char **f) {
  int opt;

  threads = 1;
  *f = NULL;
  N = 0;

  /* see man 3 getopt for details */

  const char *optspec = "t:n:f:";
  while((opt = getopt(argc, argv, optspec)) != -1) {
    switch(opt) {
    case 't':
      threads = atoi(optarg);
      break;
    case 'n':
      N = atoi(optarg);
      break;
    case 'f':
      *f = optarg;
      break;
    case '?':
    default:
      return 0;
    }
  }

  if(threads <= 0 || threads >= N) {
    fprintf(stderr, "ERROR: Threads must be greater than equal to zero and also greater than numbers\n");
    return 0;
  }

  if(N == 0 && *f == NULL) {
    fprintf(stderr, "ERROR: You must specify numbers using either -n or -f\n");
    return 0;
  }

  if(N < 0) {
    fprintf(stderr, "ERROR: -n must be positive\n");
    return 0;
  }


  if(N > 0 && *f != NULL) {
    fprintf(stderr, "ERROR: You must specify numbers using either -n or -f, can't use both.\n");
    return 0;
  }

  return 1;
}

int main(int argc, char *argv[]) {
  int n, threads;
  char *f;
  int *num;
  ggc::Timer t("sum");
  int sum = 0;
  if(!parse_args(argc, argv, threads, n, &f)) {
    usage(argv);
    exit(1);
  }
  
  if(n == 0) {
    num = read_number_file(f, n);
    if(!num) exit(1);
  } else {
    num = gen_number(n);
  }
  thread t1[threads];
  int s[threads] ;
  for (int j = 0 ;j < threads ;j++){
	s[j] = 0;
			  }
  int pre_sum = 0;
  int a = 1, b = (n/threads);
  
  t.start();
 	for (int i = 0; i < threads; i++) {
         
	  	
   	 //cout << "a = " << a << " b= " << b << endl;
 	 	t1[i] = thread(adder, a, b, ref(s[i]), num);
 	 	a = b + 1;
		if (i == (threads - 1))
			b = n;
		else  
  			b = b + (n/threads) ;					

  						}
 	for (int i = 0; i < threads; ++i) {
		t1[i].join();
        	pre_sum += s[i];
 //	cout << "pre_sum=" << pre_sum[i] << endl; 
				    }
  
  t.stop();

  printf("Total time: %llu ms\n", t.duration_ms());
  printf("Sum of %d numbers is %d\n", n, pre_sum);
}

