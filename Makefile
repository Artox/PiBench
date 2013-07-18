CFLAGS=-std=c99 -O

all: stream

stream:
	libtool --mode=compile gcc $(CFLAGS) -ITimer -c stream.c
	libtool --mode=link gcc -o stream stream.o Timer/libTimer.la -lexplain

clean:
	rm -rfv .libs *.{l,}{o,a} stream
