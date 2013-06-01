CFLAGS=-std=c99 -g

all: stream

stream:
	libtool --mode=compile gcc $(CFLAGS) -ITimer -c stream.c
	libtool --mode=link gcc -o stream stream.o Timer/libTimer.la

clean:
	rm -rfv .libs *.{l,}{o,a} stream
