all: 2dconv 2dconv_threads 2dconv_vec1 2dconv_vec2 2dconv_vec2
#all: 2dconv
2dconv: 2dconv.cpp ppma_io.a
	gcc -O3 $^ -o $@ -lm -lrt

# modify as necessary
2dconv_threads: 2dconv_threads.cpp ppma_io.a
#	gcc -O3 $^ -o $@ -lm -lrt
	g++ -g $< -o $@ -lm -lrt -std=c++11 -lpthread
# modify as necessary
2dconv_vec1: 2dconv_threads.cpp ppma_io.a
	g++ -O3 -mavx2 $^ -o 2dconv_vec1 -lm -lrt  -std=c++11 -lpthread

# modify as necessary
2dconv_vec2: 2dconv_vec2.cpp  ppma_io.a
	g++ -O3 -mavx2 $^ -o $@ -lm -lrt -std=c++11 -lpthread

ppma_io.a: ppma_io.o 
	ar rs $@ $<

clean:
	rm -f ppma_io.a ppma_io.o 2dconv 2dconv_threads 2dconv_vec1 2dconv_vec2

