all: stream

stream:
	libtool --mode=compile gcc -std=c99 -ITimer -c stream.c
	libtool --mode=link gcc -o stream stream.o Timer/libTimer.la

clean:
	rm -rfv .libs *.{l,}{o,a} stream
